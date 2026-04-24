#ifndef ASTEROIDSPAWNSYSTEM_H
#define ASTEROIDSPAWNSYSTEM_H

#include <random>

#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>

#include "../../Ecs/Filter/Filter.h"
#include "../../Ecs/Filter/FilterBuilder.h"
#include "../../Ecs/Systems/ISystem.h"

#include "../Components/AsteroidComponent.h"
#include "../Components/AsteroidSpawnRequestEvent.h"
#include "../Components/AsteroidSpawnSettingsComponent.h"
#include "../Components/CircleColliderComponent.h"
#include "../Components/CircleShapeComponent.h"
#include "../Components/CollisionComponent.h"
#include "../Components/GameStateComponent.h"
#include "../Components/MovementComponent.h"
#include "../Components/PauseStateComponent.h"
#include "../Components/PositionComponent.h"

class AsteroidSpawnSystem final : public ISystem
{
    // Компоненты астероида
    ComponentStorage<PositionComponent>& _positions;
    ComponentStorage<MovementComponent>& _movements;
    ComponentStorage<CircleColliderComponent>& _circleColliders;
    ComponentStorage<CircleShapeComponent>& _circleShapes;
    ComponentStorage<CollisionComponent>& _collisions;
    ComponentStorage<AsteroidComponent>& _asteroids;
    ComponentStorage<AsteroidSpawnSettingsComponent>& _spawnSettings;
    ComponentStorage<AsteroidSpawnRequestEvent>& _spawnRequests;
    ComponentStorage<GameStateComponent>& _gameStates;
    ComponentStorage<PauseStateComponent>& _pauseStates;

    Filter _gameStateEntities;

    std::mt19937 _random;
    sf::Clock _clock;

    float _screenWidth;
    float _spawnTimerMs = 0.0f;
    float _currentSpawnPeriodMs;

    // Нужно считывать из конфига
    float _minSpawnPeriodMs;
    float _maxSpawnPeriodMs;

    float _minRadius;
    float _maxRadius;

    float _minSpeed;
    float _maxSpeed;

    float _minDirectionX;
    float _maxDirectionX;
    float _minDirectionY;
    float _maxDirectionY;

    int _minPointCount;
    int _maxPointCount;

    void CreateSpawnSettings();
    void UpdateSpawnSettings();
    void HandleSpawnRequests();
    void ClearSpawnRequests();
    bool IsGameOver();
    void SpawnAsteroid();

public:
    AsteroidSpawnSystem(World& world, const float screenWidth)
        : ISystem(world),
          _positions(world.GetStorage<PositionComponent>()),
          _movements(world.GetStorage<MovementComponent>()),
          _circleColliders(world.GetStorage<CircleColliderComponent>()),
          _circleShapes(world.GetStorage<CircleShapeComponent>()),
          _collisions(world.GetStorage<CollisionComponent>()),
          _asteroids(world.GetStorage<AsteroidComponent>()),
          _spawnSettings(world.GetStorage<AsteroidSpawnSettingsComponent>()),
          _spawnRequests(world.GetStorage<AsteroidSpawnRequestEvent>()),
          _gameStates(world.GetStorage<GameStateComponent>()),
          _pauseStates(world.GetStorage<PauseStateComponent>()),
          _gameStateEntities(FilterBuilder(world)
              .With<GameStateComponent>()
              .Build()),
          _random(std::random_device{}()),
          _screenWidth(screenWidth)
    {
    }

    void OnInit() override;
    void OnUpdate() override;
};

#endif //ASTEROIDSPAWNSYSTEM_H
