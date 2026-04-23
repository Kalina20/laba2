#ifndef COLLISIONRESOLVESYSTEM_H
#define COLLISIONRESOLVESYSTEM_H

#include "../../Ecs/Filter/FilterBuilder.h"
#include "../../Ecs/Systems/ISystem.h"

#include "../Components/AddScoreEvent.h"
#include "../Components/AsteroidComponent.h"
#include "../Components/BulletComponent.h"
#include "../Components/CollisionComponent.h"
#include "../Components/GameOverEvent.h"
#include "../Components/PlayerComponent.h"

class CollisionResolveSystem final : public ISystem
{
    ComponentStorage<CollisionComponent>& _collisionComponents;
    ComponentStorage<BulletComponent>& _bulletComponents;
    ComponentStorage<AsteroidComponent>& _asteroidComponents;
    ComponentStorage<PlayerComponent>& _playerComponents;
    ComponentStorage<AddScoreEvent>& _addScoreEventComponents;
    ComponentStorage<GameOverEvent>& _gameOverEventComponents;

    Filter _bullets;
    Filter _players;

public:
    explicit CollisionResolveSystem(World& world)
        : ISystem(world),
          _collisionComponents(world.GetStorage<CollisionComponent>()),
          _bulletComponents(world.GetStorage<BulletComponent>()),
          _asteroidComponents(world.GetStorage<AsteroidComponent>()),
          _playerComponents(world.GetStorage<PlayerComponent>()),
          _addScoreEventComponents(world.GetStorage<AddScoreEvent>()),
          _gameOverEventComponents(world.GetStorage<GameOverEvent>()),
          _bullets(FilterBuilder(world)
              .With<BulletComponent>()
              .With<CollisionComponent>()
              .Build()),
          _players(FilterBuilder(world)
              .With<PlayerComponent>()
              .With<CollisionComponent>()
              .Build())
    {
    }

    void OnInit() override {}
    void OnUpdate(float deltaTimeSeconds) override;
};

#endif //COLLISIONRESOLVESYSTEM_H
