#ifndef OUTOFSCREENCLEANUPSYSTEM_H
#define OUTOFSCREENCLEANUPSYSTEM_H

#include "../../Ecs/Filter/Filter.h"
#include "../../Ecs/Filter/FilterBuilder.h"
#include "../../Ecs/Systems/ISystem.h"

#include "../Components/AsteroidComponent.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/BulletComponent.h"
#include "../Components/CircleColliderComponent.h"
#include "../Components/PositionComponent.h"
#include "../Components/UfoComponent.h"

class OutOfScreenCleanupSystem final : public ISystem
{
    ComponentStorage<PositionComponent>& _positions;
    ComponentStorage<CircleColliderComponent>& _circleColliders;
    ComponentStorage<BoxColliderComponent>& _boxColliders;

    Filter _asteroidEntities;
    Filter _bulletEntities;
    Filter _ufoEntities;

    float _screenWidth;
    float _screenHeight;

    bool IsOutsideScreen(int entity) const;

public:
    OutOfScreenCleanupSystem(World& world)
        : ISystem(world),
          _positions(world.GetStorage<PositionComponent>()),
          _circleColliders(world.GetStorage<CircleColliderComponent>()),
          _boxColliders(world.GetStorage<BoxColliderComponent>()),
          _asteroidEntities(FilterBuilder(world)
              .With<AsteroidComponent>()
              .With<PositionComponent>()
              .Build()),
          _bulletEntities(FilterBuilder(world)
              .With<BulletComponent>()
              .With<PositionComponent>()
              .Build()),
          _ufoEntities(FilterBuilder(world)
              .With<UfoComponent>()
              .With<PositionComponent>()
              .Build())
    {
    }

    void OnInit() override;
    void OnUpdate() override;
};

#endif //OUTOFSCREENCLEANUPSYSTEM_H
