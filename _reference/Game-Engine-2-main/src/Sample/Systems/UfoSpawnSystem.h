#ifndef UFOSPAWNSYSTEM_H
#define UFOSPAWNSYSTEM_H

#include <random>

#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Clock.hpp>

#include "../../Ecs/Filter/Filter.h"
#include "../../Ecs/Filter/FilterBuilder.h"
#include "../../Ecs/Systems/ISystem.h"

#include "../Components/BoxColliderComponent.h"
#include "../Components/CollisionComponent.h"
#include "../Components/GameStateComponent.h"
#include "../Components/MovementComponent.h"
#include "../Components/PauseStateComponent.h"
#include "../Components/PositionComponent.h"
#include "../Components/RectangleShapeComponent.h"
#include "../Components/UfoComponent.h"
#include "../Components/UfoSpawnRequestEvent.h"
#include "../Components/UfoSpawnSettingsComponent.h"

class UfoSpawnSystem final : public ISystem
{
    ComponentStorage<PositionComponent>& _positions;
    ComponentStorage<MovementComponent>& _movements;
    ComponentStorage<BoxColliderComponent>& _boxColliders;
    ComponentStorage<RectangleShapeComponent>& _rectangleShapes;
    ComponentStorage<CollisionComponent>& _collisions;
    ComponentStorage<UfoComponent>& _ufos;
    ComponentStorage<UfoSpawnSettingsComponent>& _spawnSettings;
    ComponentStorage<UfoSpawnRequestEvent>& _spawnRequests;
    ComponentStorage<GameStateComponent>& _gameStates;
    ComponentStorage<PauseStateComponent>& _pauseStates;

    Filter _gameStateEntities;

    std::mt19937 _random;
    sf::Clock _clock;

    float _screenWidth;
    float _spawnTimerMs = 0.0f;
    float _currentSpawnPeriodMs = 0.0f;

    float _minSpawnPeriodMs = 0.0f;
    float _maxSpawnPeriodMs = 0.0f;
    float _speed = 0.0f;
    float _width = 0.0f;
    float _height = 0.0f;
    float _minY = 0.0f;
    float _maxY = 0.0f;

    void CreateSpawnSettings();
    void UpdateSpawnSettings();
    void HandleSpawnRequests();
    void ClearSpawnRequests();
    bool IsGameOver();
    void SpawnUfo();

public:
    UfoSpawnSystem(World& world, const float screenWidth)
        : ISystem(world),
          _positions(world.GetStorage<PositionComponent>()),
          _movements(world.GetStorage<MovementComponent>()),
          _boxColliders(world.GetStorage<BoxColliderComponent>()),
          _rectangleShapes(world.GetStorage<RectangleShapeComponent>()),
          _collisions(world.GetStorage<CollisionComponent>()),
          _ufos(world.GetStorage<UfoComponent>()),
          _spawnSettings(world.GetStorage<UfoSpawnSettingsComponent>()),
          _spawnRequests(world.GetStorage<UfoSpawnRequestEvent>()),
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

#endif //UFOSPAWNSYSTEM_H
