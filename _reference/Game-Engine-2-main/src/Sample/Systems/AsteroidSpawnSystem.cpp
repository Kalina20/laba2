#include "AsteroidSpawnSystem.h"

#include "../../Config/Config.h"

#include <SFML/System/Time.hpp>
#include <vector>



void AsteroidSpawnSystem::CreateSpawnSettings()
{
    for (const int entity : _spawnSettings.Entities())
        return;

    const int settingsEntity = world.CreateEntity();
    _spawnSettings.Add(settingsEntity, AsteroidSpawnSettingsComponent(_minSpawnPeriodMs, _maxSpawnPeriodMs));
}

void AsteroidSpawnSystem::UpdateSpawnSettings()
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

void AsteroidSpawnSystem::HandleSpawnRequests()
{
    std::vector<int> requestEntities;
    for (const int entity : _spawnRequests.Entities())
        requestEntities.push_back(entity);

    for (const int entity : requestEntities)
    {
        SpawnAsteroid();
        world.RemoveEntity(entity);
    }
}

void AsteroidSpawnSystem::ClearSpawnRequests()
{
    std::vector<int> requestEntities;
    for (const int entity : _spawnRequests.Entities())
        requestEntities.push_back(entity);

    for (const int entity : requestEntities)
        world.RemoveEntity(entity);
}

bool AsteroidSpawnSystem::IsGameOver()
{
    for (const int entity : _gameStateEntities)
    {
        if (_gameStates.Get(entity).IsGameOver)
            return true;
    }

    return false;
}

void AsteroidSpawnSystem::SpawnAsteroid()
{
    const float radius = std::uniform_real_distribution<float>(_minRadius, _maxRadius)(_random);
    const float speed = std::uniform_real_distribution<float>(_minSpeed, _maxSpeed)(_random);
    const int pointCount = std::uniform_int_distribution<int>(_minPointCount, _maxPointCount)(_random);
    const float x = std::uniform_real_distribution<float>(radius, _screenWidth - radius)(_random);
    const float y = -radius + 1; // Чтобы спавнился за экраном
    const sf::Vector2f direction(
        std::uniform_real_distribution<float>(_minDirectionX, _maxDirectionX)(_random),
        std::uniform_real_distribution<float>(_minDirectionY, _maxDirectionY)(_random));

    const int asteroidEntity = world.CreateEntity();
    _positions.Add(asteroidEntity, PositionComponent(x, y));
    _movements.Add(asteroidEntity, MovementComponent(speed, direction));
    _circleColliders.Add(asteroidEntity, CircleColliderComponent(radius));
    _circleShapes.Add(asteroidEntity, CircleShapeComponent(radius, pointCount, sf::Color(120, 120, 120)));
    _collisions.Add(asteroidEntity, CollisionComponent());
    _asteroids.Add(asteroidEntity, AsteroidComponent());
}

void AsteroidSpawnSystem::OnInit()
{
    Config config("config.txt");

    _minSpawnPeriodMs = config.getFloat("min_spawn_period");
    _maxSpawnPeriodMs = config.getFloat("max_spawn_period");
    if (_minSpawnPeriodMs < 1.0f)
        _minSpawnPeriodMs = 1.0f;
    if (_maxSpawnPeriodMs < _minSpawnPeriodMs)
        _maxSpawnPeriodMs = _minSpawnPeriodMs;

    _minRadius = config.getFloat("min_radius");
    _maxRadius = config.getFloat("max_radius");
    _minSpeed = config.getFloat("min_speed");
    _maxSpeed = config.getFloat("max_speed");
    _minDirectionX = config.getFloat("min_directionX");
    _maxDirectionX = config.getFloat("max_directionX");
    _minDirectionY = config.getFloat("min_directionY");
    _maxDirectionY = config.getFloat("max_directionY");
    _minPointCount = config.getInt("min_point_count");
    _maxPointCount = config.getInt("max_point_count");

    _clock.restart();
    _spawnTimerMs = 0.0f;
    _currentSpawnPeriodMs = std::uniform_real_distribution<float>(_minSpawnPeriodMs, _maxSpawnPeriodMs)(_random);
    CreateSpawnSettings();
}

void AsteroidSpawnSystem::OnUpdate()
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
    SpawnAsteroid();
}
