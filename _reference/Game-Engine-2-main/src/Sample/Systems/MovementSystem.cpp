#include "MovementSystem.h"

#include <algorithm>

#include "../../Config/Config.h"

void MovementSystem::Print(int ent)
{
    auto &position = _positionComponents.Get(ent);

    std::cout << ent << " Pos: " << position.Position.x << ", " << position.Position.y << std::endl;
}

void MovementSystem::OnInit()
{
    Config config("config.txt");
    _windowWidth = config.getFloat("window_width");
}

void MovementSystem::ClampPlayerPosition(const int entity)
{
    if (!_players.Has(entity))
        return;

    float halfWidth = 0.0f;
    if (_boxColliders.Has(entity))
        halfWidth = _boxColliders.Get(entity).Extents.x;

    auto& position = _positionComponents.Get(entity);
    position.Position.x = std::clamp(position.Position.x, halfWidth, _windowWidth - halfWidth);
}

void MovementSystem::OnUpdate()
{
    if (PauseState::IsPaused(_pauseStates))
        return;

    for (const auto ent : _moveables)
    {
        auto& position = _positionComponents.Get(ent);
        auto& movement = _movementComponents.Get(ent);

        position.Position.x += movement.Speed * movement.Direction.x;
        position.Position.y += movement.Speed * movement.Direction.y;

        ClampPlayerPosition(ent);
    }
}
