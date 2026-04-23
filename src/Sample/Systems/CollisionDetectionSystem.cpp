#include "CollisionDetectionSystem.h"

#include <algorithm>
#include <cmath>

namespace
{
    struct BoxBounds
    {
        float MinX;
        float MinY;
        float MaxX;
        float MaxY;
    };

    BoxBounds MakeBounds(const TransformComponent& transform, const BoxColliderComponent& box)
    {
        const sf::Vector2f min = transform.Position + box.Offset;
        return BoxBounds{min.x, min.y, min.x + box.Size.x, min.y + box.Size.y};
    }
}

bool CollisionDetectionSystem::Contains(const std::vector<int>& values, const int value)
{
    return std::find(values.begin(), values.end(), value) != values.end();
}

bool CollisionDetectionSystem::IntersectsAabbAabb(const int leftEntity, const int rightEntity) const
{
    const BoxBounds left = MakeBounds(_transformComponents.Get(leftEntity), _boxColliderComponents.Get(leftEntity));
    const BoxBounds right = MakeBounds(_transformComponents.Get(rightEntity), _boxColliderComponents.Get(rightEntity));

    return left.MinX <= right.MaxX &&
        left.MaxX >= right.MinX &&
        left.MinY <= right.MaxY &&
        left.MaxY >= right.MinY;
}

bool CollisionDetectionSystem::IntersectsAabbCircle(const int boxEntity, const int circleEntity) const
{
    const BoxBounds box = MakeBounds(_transformComponents.Get(boxEntity), _boxColliderComponents.Get(boxEntity));
    const auto& circleTransform = _transformComponents.Get(circleEntity);
    const auto& circleCollider = _circleColliderComponents.Get(circleEntity);

    const sf::Vector2f center = circleTransform.Position + circleCollider.Offset;
    const float closestX = std::clamp(center.x, box.MinX, box.MaxX);
    const float closestY = std::clamp(center.y, box.MinY, box.MaxY);

    const float dx = center.x - closestX;
    const float dy = center.y - closestY;
    return dx * dx + dy * dy <= circleCollider.Radius * circleCollider.Radius;
}

bool CollisionDetectionSystem::IntersectsCircleCircle(const int leftEntity, const int rightEntity) const
{
    const auto& leftTransform = _transformComponents.Get(leftEntity);
    const auto& rightTransform = _transformComponents.Get(rightEntity);
    const auto& leftCollider = _circleColliderComponents.Get(leftEntity);
    const auto& rightCollider = _circleColliderComponents.Get(rightEntity);

    const sf::Vector2f leftCenter = leftTransform.Position + leftCollider.Offset;
    const sf::Vector2f rightCenter = rightTransform.Position + rightCollider.Offset;
    const float dx = leftCenter.x - rightCenter.x;
    const float dy = leftCenter.y - rightCenter.y;
    const float radii = leftCollider.Radius + rightCollider.Radius;
    return dx * dx + dy * dy <= radii * radii;
}

bool CollisionDetectionSystem::Intersects(const int leftEntity, const int rightEntity) const
{
    if (!_transformComponents.Has(leftEntity) || !_transformComponents.Has(rightEntity))
    {
        return false;
    }

    const bool leftBox = _boxColliderComponents.Has(leftEntity);
    const bool rightBox = _boxColliderComponents.Has(rightEntity);
    const bool leftCircle = _circleColliderComponents.Has(leftEntity);
    const bool rightCircle = _circleColliderComponents.Has(rightEntity);

    if (leftBox && rightBox)
    {
        return IntersectsAabbAabb(leftEntity, rightEntity);
    }

    if (leftBox && rightCircle)
    {
        return IntersectsAabbCircle(leftEntity, rightEntity);
    }

    if (leftCircle && rightBox)
    {
        return IntersectsAabbCircle(rightEntity, leftEntity);
    }

    if (leftCircle && rightCircle)
    {
        return IntersectsCircleCircle(leftEntity, rightEntity);
    }

    return false;
}

void CollisionDetectionSystem::OnUpdate(const float deltaTimeSeconds)
{
    (void)deltaTimeSeconds;

    const std::vector<int> aliveEntities = world.GetAliveEntities();

    for (const int entity : aliveEntities)
    {
        if (_collisionComponents.Has(entity))
        {
            _collisionComponents.Get(entity).CollidedWith.clear();
        }
    }

    for (size_t i = 0; i < aliveEntities.size(); ++i)
    {
        const int left = aliveEntities[i];
        if (!_collisionComponents.Has(left))
        {
            continue;
        }

        for (size_t j = i + 1; j < aliveEntities.size(); ++j)
        {
            const int right = aliveEntities[j];
            if (!_collisionComponents.Has(right))
            {
                continue;
            }

            if (!Intersects(left, right))
            {
                continue;
            }

            auto& leftCollisions = _collisionComponents.Get(left).CollidedWith;
            auto& rightCollisions = _collisionComponents.Get(right).CollidedWith;

            if (!Contains(leftCollisions, right))
            {
                leftCollisions.push_back(right);
            }
            if (!Contains(rightCollisions, left))
            {
                rightCollisions.push_back(left);
            }
        }
    }
}
