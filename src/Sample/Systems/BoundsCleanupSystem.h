#ifndef BOUNDSCLEANUPSYSTEM_H
#define BOUNDSCLEANUPSYSTEM_H

#include "../../Ecs/Filter/FilterBuilder.h"
#include "../../Ecs/Systems/ISystem.h"

#include "../Components/AsteroidComponent.h"
#include "../Components/BulletComponent.h"
#include "../Components/CircleColliderComponent.h"
#include "../Components/TransformComponent.h"

class BoundsCleanupSystem final : public ISystem
{
    float _windowWidth;
    float _windowHeight;

    ComponentStorage<TransformComponent>& _transformComponents;
    ComponentStorage<CircleColliderComponent>& _circleColliderComponents;

    Filter _bullets;
    Filter _asteroids;

public:
    BoundsCleanupSystem(World& world, const float windowWidth, const float windowHeight)
        : ISystem(world),
          _windowWidth(windowWidth),
          _windowHeight(windowHeight),
          _transformComponents(world.GetStorage<TransformComponent>()),
          _circleColliderComponents(world.GetStorage<CircleColliderComponent>()),
          _bullets(FilterBuilder(world)
              .With<BulletComponent>()
              .With<TransformComponent>()
              .Build()),
          _asteroids(FilterBuilder(world)
              .With<AsteroidComponent>()
              .With<TransformComponent>()
              .Build())
    {
    }

    void OnInit() override {}
    void OnUpdate(float deltaTimeSeconds) override;
};

#endif //BOUNDSCLEANUPSYSTEM_H
