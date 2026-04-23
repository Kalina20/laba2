#ifndef SHOOTSYSTEM_H
#define SHOOTSYSTEM_H

#include "../../Ecs/Filter/FilterBuilder.h"
#include "../../Ecs/Systems/ISystem.h"

#include "../Components/BoxColliderComponent.h"
#include "../Components/BulletComponent.h"
#include "../Components/CollisionComponent.h"
#include "../Components/MovementComponent.h"
#include "../Components/RectangleShapeComponent.h"
#include "../Components/ShootInputEvent.h"
#include "../Components/ShooterComponent.h"
#include "../Components/TransformComponent.h"
#include "../Services/TimeService.h"

class ShootSystem final : public ISystem
{
    TimeService& _timeService;
    float _bulletSpeed;

    ComponentStorage<ShootInputEvent>& _shootEventComponents;
    ComponentStorage<ShooterComponent>& _shooterComponents;
    ComponentStorage<TransformComponent>& _transformComponents;
    ComponentStorage<MovementComponent>& _movementComponents;
    ComponentStorage<CollisionComponent>& _collisionComponents;
    ComponentStorage<BoxColliderComponent>& _boxColliderComponents;
    ComponentStorage<RectangleShapeComponent>& _rectangleShapeComponents;
    ComponentStorage<BulletComponent>& _bulletComponents;

    Filter _shootEvents;

    void SpawnBullet(int shooterEntity);

public:
    ShootSystem(World& world, TimeService& timeService, const float bulletSpeed)
        : ISystem(world),
          _timeService(timeService),
          _bulletSpeed(bulletSpeed),
          _shootEventComponents(world.GetStorage<ShootInputEvent>()),
          _shooterComponents(world.GetStorage<ShooterComponent>()),
          _transformComponents(world.GetStorage<TransformComponent>()),
          _movementComponents(world.GetStorage<MovementComponent>()),
          _collisionComponents(world.GetStorage<CollisionComponent>()),
          _boxColliderComponents(world.GetStorage<BoxColliderComponent>()),
          _rectangleShapeComponents(world.GetStorage<RectangleShapeComponent>()),
          _bulletComponents(world.GetStorage<BulletComponent>()),
          _shootEvents(FilterBuilder(world)
              .With<ShootInputEvent>()
              .Build())
    {
    }

    void OnInit() override {}
    void OnUpdate(float deltaTimeSeconds) override;
};

#endif //SHOOTSYSTEM_H
