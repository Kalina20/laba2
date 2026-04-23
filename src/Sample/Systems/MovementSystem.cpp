#include "MovementSystem.h"

#include <algorithm>

void MovementSystem::OnInit()
{

}

void MovementSystem::ClampPlayerToBounds(const int playerEntity) const
{
    auto& transform = _transformComponents.Get(playerEntity);

    constexpr float halfWidth = 28.0f;
    const float minX = halfWidth;
    const float maxX = std::max(minX, _windowWidth - halfWidth);
    transform.Position.x = std::clamp(transform.Position.x, minX, maxX);
}

void MovementSystem::OnUpdate(const float deltaTimeSeconds)
{
    for (const int entity : _movables)
    {
        auto& transform = _transformComponents.Get(entity);
        const auto& movement = _movementComponents.Get(entity);
        transform.Position += movement.Direction * movement.Speed * deltaTimeSeconds;
    }

    for (const int playerEntity : _players)
    {
        ClampPlayerToBounds(playerEntity);
    }
}
