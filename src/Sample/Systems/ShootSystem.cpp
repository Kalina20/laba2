#include "ShootSystem.h"

#include <vector>

void ShootSystem::SpawnBullet(const int shooterEntity)
{
    const auto& shooterTransform = _transformComponents.Get(shooterEntity);
    const int bullet = world.CreateEntity();

    _transformComponents.Add(bullet, TransformComponent{sf::Vector2f(shooterTransform.Position.x, shooterTransform.Position.y - 34.0f)});
    _movementComponents.Add(bullet, MovementComponent{sf::Vector2f(0.0f, -1.0f), _bulletSpeed});
    _collisionComponents.Add(bullet, CollisionComponent{});
    _boxColliderComponents.Add(bullet, BoxColliderComponent{sf::Vector2f(8.0f, 20.0f), sf::Vector2f(-4.0f, -10.0f)});
    _rectangleShapeComponents.Add(bullet, RectangleShapeComponent{sf::RectangleShape{}, sf::Vector2f(8.0f, 20.0f), sf::Color::Yellow});
    _bulletComponents.Add(bullet, BulletComponent{1});
}

void ShootSystem::OnUpdate(const float deltaTimeSeconds)
{
    (void)deltaTimeSeconds;

    std::vector<int> events;
    for (const int eventEntity : _shootEvents)
    {
        events.push_back(eventEntity);
    }

    const int nowMs = _timeService.ElapsedMilliseconds();
    for (const int eventEntity : events)
    {
        if (!world.IsEntityAlive(eventEntity) || !_shootEventComponents.Has(eventEntity))
        {
            continue;
        }

        const ShootInputEvent eventData = _shootEventComponents.Get(eventEntity);
        const int shooterEntity = eventData.ShooterEntity;

        if (!world.IsEntityAlive(shooterEntity) ||
            !_shooterComponents.Has(shooterEntity) ||
            !_transformComponents.Has(shooterEntity))
        {
            world.RemoveEntity(eventEntity);
            continue;
        }

        auto& shooter = _shooterComponents.Get(shooterEntity);
        const bool cooldownReady = nowMs - shooter.LastShotTimeMs >= shooter.CooldownMs;
        if (shooter.CanShoot && cooldownReady)
        {
            SpawnBullet(shooterEntity);
            shooter.LastShotTimeMs = nowMs;
        }

        world.RemoveEntity(eventEntity);
    }
}
