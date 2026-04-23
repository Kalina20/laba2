#include "BoundsCleanupSystem.h"

#include <vector>

void BoundsCleanupSystem::OnUpdate(const float deltaTimeSeconds)
{
    (void)deltaTimeSeconds;

    std::vector<int> toRemove;

    for (const int bullet : _bullets)
    {
        const auto& transform = _transformComponents.Get(bullet);
        if (transform.Position.y < -50.0f)
        {
            toRemove.push_back(bullet);
        }
    }

    for (const int asteroid : _asteroids)
    {
        const auto& transform = _transformComponents.Get(asteroid);
        float radius = 0.0f;
        if (_circleColliderComponents.Has(asteroid))
        {
            radius = _circleColliderComponents.Get(asteroid).Radius;
        }

        const bool outOfBounds =
            transform.Position.x < -radius - 40.0f ||
            transform.Position.x > _windowWidth + radius + 40.0f ||
            transform.Position.y > _windowHeight + radius + 40.0f;
        if (outOfBounds)
        {
            toRemove.push_back(asteroid);
        }
    }

    for (const int entity : toRemove)
    {
        if (world.IsEntityAlive(entity))
        {
            world.RemoveEntity(entity);
        }
    }
}
