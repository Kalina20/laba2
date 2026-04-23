#include "AsteroidSpawnSystem.h"

#include <algorithm>
#include <cmath>
#include <vector>

int AsteroidSpawnSystem::NextSpawnDelayMs()
{
    int minMs = _config.AsteroidSpawnMinMs;
    int maxMs = _config.AsteroidSpawnMaxMs;

    for (const int settingsEntity : _spawnSettings)
    {
        const auto& settings = _spawnSettingsComponents.Get(settingsEntity);
        minMs = settings.MinIntervalMs;
        maxMs = settings.MaxIntervalMs;
        break;
    }

    if (minMs > maxMs)
    {
        std::swap(minMs, maxMs);
    }

    return _randomService.IntInRange(minMs, maxMs);
}

void AsteroidSpawnSystem::SpawnAsteroid()
{
    const float radius = _randomService.FloatInRange(_config.AsteroidRadiusMin, _config.AsteroidRadiusMax);
    const float speed = _randomService.FloatInRange(_config.AsteroidSpeedMin, _config.AsteroidSpeedMax);
    float dirX = _randomService.FloatInRange(_config.AsteroidDirXMin, _config.AsteroidDirXMax);
    float dirY = _randomService.FloatInRange(_config.AsteroidDirYMin, _config.AsteroidDirYMax);

    const float length = std::sqrt(dirX * dirX + dirY * dirY);
    if (length > 0.0001f)
    {
        dirX /= length;
        dirY /= length;
    }
    else
    {
        dirX = 0.0f;
        dirY = 1.0f;
    }

    const float spawnX = _randomService.FloatInRange(radius, std::max(radius, _windowWidth - radius));
    const float spawnY = -radius - 20.0f;
    const unsigned int points = static_cast<unsigned int>(
        _randomService.IntInRange(_config.AsteroidPointsMin, _config.AsteroidPointsMax));

    const int asteroid = world.CreateEntity();
    _transformComponents.Add(asteroid, TransformComponent{sf::Vector2f(spawnX, spawnY)});
    _movementComponents.Add(asteroid, MovementComponent{sf::Vector2f(dirX, dirY), speed});
    _collisionComponents.Add(asteroid, CollisionComponent{});
    _circleColliderComponents.Add(asteroid, CircleColliderComponent{radius, sf::Vector2f(0.0f, 0.0f)});
    _circleShapeComponents.Add(asteroid, CircleShapeComponent{sf::CircleShape{}, radius, points, sf::Color(180, 180, 180)});
    _asteroidComponents.Add(asteroid, AsteroidComponent{1});
}

void AsteroidSpawnSystem::OnInit()
{
    _nextSpawnAtMs = _timeService.ElapsedMilliseconds() + NextSpawnDelayMs();
}

void AsteroidSpawnSystem::OnUpdate(const float deltaTimeSeconds)
{
    (void)deltaTimeSeconds;

    bool hasAlivePlayer = false;
    for (const int player : _players)
    {
        if (_playerComponents.Get(player).IsAlive)
        {
            hasAlivePlayer = true;
            break;
        }
    }

    if (!hasAlivePlayer)
    {
        return;
    }

    std::vector<int> manualEvents;
    for (const int eventEntity : _manualSpawnEvents)
    {
        manualEvents.push_back(eventEntity);
    }
    for (const int eventEntity : manualEvents)
    {
        SpawnAsteroid();
        if (world.IsEntityAlive(eventEntity))
        {
            world.RemoveEntity(eventEntity);
        }
    }

    const int nowMs = _timeService.ElapsedMilliseconds();
    while (nowMs >= _nextSpawnAtMs)
    {
        SpawnAsteroid();
        _nextSpawnAtMs += NextSpawnDelayMs();
    }
}
