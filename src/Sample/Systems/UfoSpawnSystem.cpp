#include "UfoSpawnSystem.h"

#include <vector>

#include <SFML/System/Time.hpp>

#include "../../Config/Config.h"

void UfoSpawnSystem::CreateSpawnSettings()
{
    for (const int entity : _spawnSettings.Entities())
        return;

    const int settingsEntity = world.CreateEntity();
    _spawnSettings.Add(settingsEntity, UfoSpawnSettingsComponent(_minSpawnPeriodMs, _maxSpawnPeriodMs));
}

void UfoSpawnSystem::UpdateSpawnSettings()
{
    for (const int entity : _spawnSettings.Entities())
    {
        auto& settings = _spawnSettings.Get(entity);
        if (settings.MinSpawnPeriodMs < 1.0f)
            settings.MinSpawnPeriodMs = 1.0f;
        if (settings.MaxSpawnPeriodMs < settings.MinSpawnPeriodMs)
            settings.MaxSpawnPeriodMs = settings.MinSpawnPeriodMs;

        _minSpawnPeriodMs = settings.MinSpawnPeriodMs;
        _maxSpawnPeriodMs = settings.MaxSpawnPeriodMs;
        return;
    }
}

void UfoSpawnSystem::HandleSpawnRequests()
{
    std::vector<int> requestEntities;
    for (const int entity : _spawnRequests.Entities())
        requestEntities.push_back(entity);

    for (const int entity : requestEntities)
    {
        SpawnUfo();
        world.RemoveEntity(entity);
    }
}

void UfoSpawnSystem::ClearSpawnRequests()
{
    std::vector<int> requestEntities;
    for (const int entity : _spawnRequests.Entities())
        requestEntities.push_back(entity);

    for (const int entity : requestEntities)
        world.RemoveEntity(entity);
}

bool UfoSpawnSystem::IsGameOver()
{
    for (const int entity : _gameStateEntities)
    {
        if (_gameStates.Get(entity).IsGameOver)
            return true;
    }
    return false;
}

void UfoSpawnSystem::SpawnUfo()
{
    const bool spawnOnLeft = std::uniform_int_distribution<int>(0, 1)(_random) == 0;
    const float directionX = spawnOnLeft ? 1.0f : -1.0f;
    const float x = spawnOnLeft ? -_width / 2.0f : _screenWidth + _width / 2.0f;
    const float y = std::uniform_real_distribution<float>(_minY, _maxY)(_random);

    const int ufoEntity = world.CreateEntity();
    _positions.Add(ufoEntity, PositionComponent(x, y));
    _movements.Add(ufoEntity, MovementComponent(_speed, directionX, 0.0f));
    _boxColliders.Add(ufoEntity, BoxColliderComponent(_width, _height));
    _rectangleShapes.Add(ufoEntity, RectangleShapeComponent(_width, _height, sf::Color::Cyan));
    _collisions.Add(ufoEntity, CollisionComponent());
    _ufos.Add(ufoEntity, UfoComponent(_speed));
}

void UfoSpawnSystem::OnInit()
{
    Config config("config.txt");

    _minSpawnPeriodMs = config.getFloat("ufo_min_spawn_period");
    _maxSpawnPeriodMs = config.getFloat("ufo_max_spawn_period");
    if (_minSpawnPeriodMs < 1.0f)
        _minSpawnPeriodMs = 1.0f;
    if (_maxSpawnPeriodMs < _minSpawnPeriodMs)
        _maxSpawnPeriodMs = _minSpawnPeriodMs;

    _speed = config.getFloat("ufo_speed");
    _width = config.getFloat("ufo_width");
    _height = config.getFloat("ufo_height");
    _minY = config.getFloat("ufo_min_y");
    _maxY = config.getFloat("ufo_max_y");

    _clock.restart();
    _spawnTimerMs = 0.0f;
    _currentSpawnPeriodMs = std::uniform_real_distribution<float>(_minSpawnPeriodMs, _maxSpawnPeriodMs)(_random);
    CreateSpawnSettings();
}

void UfoSpawnSystem::OnUpdate()
{
    if (PauseState::IsPaused(_pauseStates))
    {
        _clock.restart();
        return;
    }


    UpdateSpawnSettings();

    if (IsGameOver())
    {
        ClearSpawnRequests();
        return;
    }

    HandleSpawnRequests();

    _spawnTimerMs += static_cast<float>(_clock.restart().asMilliseconds());
    if (_spawnTimerMs < _currentSpawnPeriodMs)
        return;

    _spawnTimerMs = 0.0f;
    _currentSpawnPeriodMs = std::uniform_real_distribution<float>(_minSpawnPeriodMs, _maxSpawnPeriodMs)(_random);
    SpawnUfo();
}
