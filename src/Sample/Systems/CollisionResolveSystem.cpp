#include "CollisionResolveSystem.h"

#include <unordered_set>

void CollisionResolveSystem::OnUpdate(const float deltaTimeSeconds)
{
    (void)deltaTimeSeconds;

    std::unordered_set<int> entitiesToDestroy;

    for (const int bullet : _bullets)
    {
        const auto& collisions = _collisionComponents.Get(bullet).CollidedWith;
        for (const int other : collisions)
        {
            if (!world.IsEntityAlive(other) || !_asteroidComponents.Has(other))
            {
                continue;
            }

            entitiesToDestroy.insert(bullet);
            entitiesToDestroy.insert(other);

            const int addScoreEventEntity = world.CreateEntity();
            _addScoreEventComponents.Add(addScoreEventEntity, AddScoreEvent{_asteroidComponents.Get(other).ScoreValue});
        }
    }

    for (const int player : _players)
    {
        auto& playerComponent = _playerComponents.Get(player);
        if (!playerComponent.IsAlive)
        {
            continue;
        }

        const auto& collisions = _collisionComponents.Get(player).CollidedWith;
        for (const int other : collisions)
        {
            if (!world.IsEntityAlive(other) || !_asteroidComponents.Has(other))
            {
                continue;
            }

            entitiesToDestroy.insert(other);
            playerComponent.IsAlive = false;

            const int gameOverEventEntity = world.CreateEntity();
            _gameOverEventComponents.Add(gameOverEventEntity, GameOverEvent{player});
            break;
        }
    }

    for (const int entity : entitiesToDestroy)
    {
        if (world.IsEntityAlive(entity))
        {
            world.RemoveEntity(entity);
        }
    }
}
