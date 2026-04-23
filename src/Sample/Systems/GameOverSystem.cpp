#include "GameOverSystem.h"

#include <vector>

void GameOverSystem::CreatePlayer()
{
    const int player = world.CreateEntity();

    _transformComponents.Add(player, TransformComponent{sf::Vector2f(_windowWidth * 0.5f, _windowHeight - 60.0f)});
    _movementComponents.Add(player, MovementComponent{sf::Vector2f(0.0f, 0.0f), _playerSpeed});
    _boxColliderComponents.Add(player, BoxColliderComponent{sf::Vector2f(56.0f, 56.0f), sf::Vector2f(-28.0f, -28.0f)});
    _collisionComponents.Add(player, CollisionComponent{});
    _circleShapeComponents.Add(player, CircleShapeComponent{sf::CircleShape{}, 28.0f, 3, sf::Color::Cyan});
    _shooterComponents.Add(player, ShooterComponent{true, _shootCooldownMs, -1000000});
    _playerComponents.Add(player, PlayerComponent{0, true});
}

void GameOverSystem::RestartGame()
{
    const std::vector<int> aliveEntities = world.GetAliveEntities();
    for (const int entity : aliveEntities)
    {
        if (world.IsEntityAlive(entity))
        {
            world.RemoveEntity(entity);
        }
    }

    CreatePlayer();
    const int spawnSettings = world.CreateEntity();
    _spawnSettingsComponents.Add(spawnSettings, AsteroidSpawnSettingsComponent{_asteroidSpawnMinMs, _asteroidSpawnMaxMs});
    _isGameOver = false;
}

void GameOverSystem::ApplyGameOverState()
{
    for (const int entity : _movables)
    {
        auto& movement = _movementComponents.Get(entity);
        movement.Direction = sf::Vector2f(0.0f, 0.0f);
    }

    for (const int player : _players)
    {
        if (_playerComponents.Has(player))
        {
            _playerComponents.Get(player).IsAlive = false;
        }

        if (_movementComponents.Has(player))
        {
            _movementComponents.Get(player).Direction = sf::Vector2f(0.0f, 0.0f);
        }

        if (_shooterComponents.Has(player))
        {
            _shooterComponents.Get(player).CanShoot = false;
        }
    }
}

void GameOverSystem::OnUpdate(const float deltaTimeSeconds)
{
    (void)deltaTimeSeconds;

    if (_isGameOver && _inputService.IsAnyKeyPressed())
    {
        RestartGame();
        return;
    }

    std::vector<int> eventsToRemove;
    bool hasGameOverEvent = false;

    for (const int eventEntity : _gameOverEvents)
    {
        hasGameOverEvent = true;
        eventsToRemove.push_back(eventEntity);
    }

    if (hasGameOverEvent)
    {
        _isGameOver = true;
        ApplyGameOverState();
    }

    for (const int eventEntity : eventsToRemove)
    {
        if (world.IsEntityAlive(eventEntity))
        {
            world.RemoveEntity(eventEntity);
        }
    }
}
