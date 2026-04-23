#ifndef GAMEOVERSYSTEM_H
#define GAMEOVERSYSTEM_H

#include "../../Ecs/Filter/FilterBuilder.h"
#include "../../Ecs/Systems/ISystem.h"

#include "../Components/BoxColliderComponent.h"
#include "../Components/AsteroidSpawnSettingsComponent.h"
#include "../Components/CircleShapeComponent.h"
#include "../Components/CollisionComponent.h"
#include "../Components/GameOverEvent.h"
#include "../Components/MovementComponent.h"
#include "../Components/PlayerComponent.h"
#include "../Components/ShooterComponent.h"
#include "../Components/TransformComponent.h"
#include "../Services/InputService.h"

class GameOverSystem final : public ISystem
{
    InputService& _inputService;
    float _windowWidth;
    float _windowHeight;
    float _playerSpeed;
    int _shootCooldownMs;
    int _asteroidSpawnMinMs;
    int _asteroidSpawnMaxMs;

    bool _isGameOver = false;

    ComponentStorage<TransformComponent>& _transformComponents;
    ComponentStorage<BoxColliderComponent>& _boxColliderComponents;
    ComponentStorage<CollisionComponent>& _collisionComponents;
    ComponentStorage<CircleShapeComponent>& _circleShapeComponents;
    ComponentStorage<AsteroidSpawnSettingsComponent>& _spawnSettingsComponents;
    ComponentStorage<GameOverEvent>& _gameOverEventComponents;
    ComponentStorage<PlayerComponent>& _playerComponents;
    ComponentStorage<MovementComponent>& _movementComponents;
    ComponentStorage<ShooterComponent>& _shooterComponents;

    Filter _gameOverEvents;
    Filter _players;
    Filter _movables;

    void CreatePlayer();
    void RestartGame();
    void ApplyGameOverState();

public:
    GameOverSystem(
        World& world,
        InputService& inputService,
        const float windowWidth,
        const float windowHeight,
        const float playerSpeed,
        const int shootCooldownMs,
        const int asteroidSpawnMinMs,
        const int asteroidSpawnMaxMs)
        : ISystem(world),
          _inputService(inputService),
          _windowWidth(windowWidth),
          _windowHeight(windowHeight),
          _playerSpeed(playerSpeed),
          _shootCooldownMs(shootCooldownMs),
          _asteroidSpawnMinMs(asteroidSpawnMinMs),
          _asteroidSpawnMaxMs(asteroidSpawnMaxMs),
          _transformComponents(world.GetStorage<TransformComponent>()),
          _boxColliderComponents(world.GetStorage<BoxColliderComponent>()),
          _collisionComponents(world.GetStorage<CollisionComponent>()),
          _circleShapeComponents(world.GetStorage<CircleShapeComponent>()),
          _spawnSettingsComponents(world.GetStorage<AsteroidSpawnSettingsComponent>()),
          _gameOverEventComponents(world.GetStorage<GameOverEvent>()),
          _playerComponents(world.GetStorage<PlayerComponent>()),
          _movementComponents(world.GetStorage<MovementComponent>()),
          _shooterComponents(world.GetStorage<ShooterComponent>()),
          _gameOverEvents(FilterBuilder(world)
              .With<GameOverEvent>()
              .Build()),
          _players(FilterBuilder(world)
              .With<PlayerComponent>()
              .Build()),
          _movables(FilterBuilder(world)
              .With<MovementComponent>()
              .Build())
    {
    }

    bool IsGameOver() const
    {
        return _isGameOver;
    }

    void OnInit() override {}
    void OnUpdate(float deltaTimeSeconds) override;
};

#endif //GAMEOVERSYSTEM_H
