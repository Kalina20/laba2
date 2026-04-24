#ifndef RESTARTSYSTEM_H
#define RESTARTSYSTEM_H

#include <vector>

#include "../../Ecs/Filter/Filter.h"
#include "../../Ecs/Filter/FilterBuilder.h"
#include "../../Ecs/Systems/ISystem.h"

#include "../Components/AsteroidComponent.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/BulletComponent.h"
#include "../Components/CircleShapeComponent.h"
#include "../Components/CollisionComponent.h"
#include "../Components/CooldownBoostComponent.h"
#include "../Components/CooldownBoostEvent.h"
#include "../Components/GameOverEvent.h"
#include "../Components/GameStateComponent.h"
#include "../Components/MovementComponent.h"
#include "../Components/PlayerComponent.h"
#include "../Components/PositionComponent.h"
#include "../Components/RestartInputEvent.h"
#include "../Components/ScoreIncreaseEvent.h"
#include "../Components/ShooterComponent.h"
#include "../Components/UfoComponent.h"
#include "../Components/UfoSpawnRequestEvent.h"

class RestartSystem final : public ISystem
{
    ComponentStorage<PositionComponent>& _positions;
    ComponentStorage<MovementComponent>& _movements;
    ComponentStorage<PlayerComponent>& _players;
    ComponentStorage<ShooterComponent>& _shooters;
    ComponentStorage<BoxColliderComponent>& _boxColliders;
    ComponentStorage<CircleShapeComponent>& _circleShapes;
    ComponentStorage<CollisionComponent>& _collisions;
    ComponentStorage<GameStateComponent>& _gameStates;

    Filter _restartInputEvents;
    Filter _asteroids;
    Filter _bullets;
    Filter _ufos;
    Filter _playersFilter;
    Filter _scoreIncreaseEvents;
    Filter _cooldownBoostEvents;
    Filter _cooldownBoosts;
    Filter _ufoSpawnRequests;
    Filter _gameOverEvents;
    Filter _gameStatesFilter;

    float _playerSpeed;
    float _shootCooldown;
    float _windowWidth;
    float _windowHeight;

    void CreateGameState();
    void CreatePlayer();
    void ResetGameState();

public:
    RestartSystem(World& world)
        : ISystem(world),
          _positions(world.GetStorage<PositionComponent>()),
          _movements(world.GetStorage<MovementComponent>()),
          _players(world.GetStorage<PlayerComponent>()),
          _shooters(world.GetStorage<ShooterComponent>()),
          _boxColliders(world.GetStorage<BoxColliderComponent>()),
          _circleShapes(world.GetStorage<CircleShapeComponent>()),
          _collisions(world.GetStorage<CollisionComponent>()),
          _gameStates(world.GetStorage<GameStateComponent>()),
          _restartInputEvents(FilterBuilder(world)
              .With<RestartInputEvent>()
              .Build()),
          _asteroids(FilterBuilder(world)
              .With<AsteroidComponent>()
              .Build()),
          _bullets(FilterBuilder(world)
              .With<BulletComponent>()
              .Build()),
          _ufos(FilterBuilder(world)
              .With<UfoComponent>()
              .Build()),
          _playersFilter(FilterBuilder(world)
              .With<PlayerComponent>()
              .Build()),
          _scoreIncreaseEvents(FilterBuilder(world)
              .With<ScoreIncreaseEvent>()
              .Build()),
          _cooldownBoostEvents(FilterBuilder(world)
              .With<CooldownBoostEvent>()
              .Build()),
          _cooldownBoosts(FilterBuilder(world)
              .With<CooldownBoostComponent>()
              .Build()),
          _ufoSpawnRequests(FilterBuilder(world)
              .With<UfoSpawnRequestEvent>()
              .Build()),
          _gameOverEvents(FilterBuilder(world)
              .With<GameOverEvent>()
              .Build()),
          _gameStatesFilter(FilterBuilder(world)
              .With<GameStateComponent>()
              .Build())
    {
    }

    void OnInit() override;
    void OnUpdate() override;
};

#endif //RESTARTSYSTEM_H
