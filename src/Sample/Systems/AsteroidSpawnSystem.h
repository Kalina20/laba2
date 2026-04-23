#ifndef ASTEROIDSPAWNSYSTEM_H
#define ASTEROIDSPAWNSYSTEM_H

#include "../../Ecs/Filter/FilterBuilder.h"
#include "../../Ecs/Systems/ISystem.h"

#include "../Components/AsteroidComponent.h"
#include "../Components/AsteroidSpawnSettingsComponent.h"
#include "../Components/CircleColliderComponent.h"
#include "../Components/CircleShapeComponent.h"
#include "../Components/CollisionComponent.h"
#include "../Components/MovementComponent.h"
#include "../Components/PlayerComponent.h"
#include "../Components/SpawnAsteroidEvent.h"
#include "../Components/TransformComponent.h"
#include "../Services/GameConfig.h"
#include "../Services/RandomService.h"
#include "../Services/TimeService.h"

class AsteroidSpawnSystem final : public ISystem
{
    TimeService& _timeService;
    RandomService& _randomService;
    GameConfig _config;
    float _windowWidth;

    int _nextSpawnAtMs = 0;

    ComponentStorage<TransformComponent>& _transformComponents;
    ComponentStorage<MovementComponent>& _movementComponents;
    ComponentStorage<CollisionComponent>& _collisionComponents;
    ComponentStorage<CircleColliderComponent>& _circleColliderComponents;
    ComponentStorage<CircleShapeComponent>& _circleShapeComponents;
    ComponentStorage<AsteroidComponent>& _asteroidComponents;
    ComponentStorage<PlayerComponent>& _playerComponents;
    ComponentStorage<AsteroidSpawnSettingsComponent>& _spawnSettingsComponents;
    ComponentStorage<SpawnAsteroidEvent>& _spawnAsteroidEvents;

    Filter _players;
    Filter _spawnSettings;
    Filter _manualSpawnEvents;

    int NextSpawnDelayMs();
    void SpawnAsteroid();

public:
    AsteroidSpawnSystem(
        World& world,
        TimeService& timeService,
        RandomService& randomService,
        const GameConfig& config,
        const float windowWidth)
        : ISystem(world),
          _timeService(timeService),
          _randomService(randomService),
          _config(config),
          _windowWidth(windowWidth),
          _transformComponents(world.GetStorage<TransformComponent>()),
          _movementComponents(world.GetStorage<MovementComponent>()),
          _collisionComponents(world.GetStorage<CollisionComponent>()),
          _circleColliderComponents(world.GetStorage<CircleColliderComponent>()),
          _circleShapeComponents(world.GetStorage<CircleShapeComponent>()),
          _asteroidComponents(world.GetStorage<AsteroidComponent>()),
          _playerComponents(world.GetStorage<PlayerComponent>()),
          _spawnSettingsComponents(world.GetStorage<AsteroidSpawnSettingsComponent>()),
          _spawnAsteroidEvents(world.GetStorage<SpawnAsteroidEvent>()),
          _players(FilterBuilder(world)
              .With<PlayerComponent>()
              .Build()),
          _spawnSettings(FilterBuilder(world)
              .With<AsteroidSpawnSettingsComponent>()
              .Build()),
          _manualSpawnEvents(FilterBuilder(world)
              .With<SpawnAsteroidEvent>()
              .Build())
    {
    }

    void OnInit() override;
    void OnUpdate(float deltaTimeSeconds) override;
};

#endif //ASTEROIDSPAWNSYSTEM_H
