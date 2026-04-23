#ifndef COLLISIONDETECTIONSYSTEM_H
#define COLLISIONDETECTIONSYSTEM_H

#include "../../Ecs/Systems/ISystem.h"

#include "../Components/BoxColliderComponent.h"
#include "../Components/CircleColliderComponent.h"
#include "../Components/CollisionComponent.h"
#include "../Components/TransformComponent.h"

class CollisionDetectionSystem final : public ISystem
{
    ComponentStorage<TransformComponent>& _transformComponents;
    ComponentStorage<CollisionComponent>& _collisionComponents;
    ComponentStorage<BoxColliderComponent>& _boxColliderComponents;
    ComponentStorage<CircleColliderComponent>& _circleColliderComponents;

    static bool Contains(const std::vector<int>& values, int value);

    bool IntersectsAabbAabb(int leftEntity, int rightEntity) const;
    bool IntersectsAabbCircle(int boxEntity, int circleEntity) const;
    bool IntersectsCircleCircle(int leftEntity, int rightEntity) const;
    bool Intersects(int leftEntity, int rightEntity) const;

public:
    explicit CollisionDetectionSystem(World& world)
        : ISystem(world),
          _transformComponents(world.GetStorage<TransformComponent>()),
          _collisionComponents(world.GetStorage<CollisionComponent>()),
          _boxColliderComponents(world.GetStorage<BoxColliderComponent>()),
          _circleColliderComponents(world.GetStorage<CircleColliderComponent>())
    {
    }

    void OnInit() override {}
    void OnUpdate(float deltaTimeSeconds) override;
};

#endif //COLLISIONDETECTIONSYSTEM_H
