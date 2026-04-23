#include "InputSystem.h"

#include <imgui-SFML.h>

void InputSystem::OnInit()
{
    _input.SetKeyRepeatEnabled(false);
}

void InputSystem::OnUpdate(const float deltaTimeSeconds)
{
    (void)deltaTimeSeconds;

    bool shootPressed = false;
    while (const std::optional event = _input.PollEvent())
    {
        ImGui::SFML::ProcessEvent(_input.Window(), *event);

        if (event->is<sf::Event::Closed>())
        {
            _input.Close();
        }
        else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            if (keyPressed->scancode == sf::Keyboard::Scancode::Space)
            {
                shootPressed = true;
            }
        }
    }

    float directionX = 0.0f;
    if (_input.IsPressed(sf::Keyboard::Scancode::A) ||
        _input.IsPressed(sf::Keyboard::Scancode::Left))
    {
        directionX -= 1.0f;
    }
    if (_input.IsPressed(sf::Keyboard::Scancode::D) ||
        _input.IsPressed(sf::Keyboard::Scancode::Right))
    {
        directionX += 1.0f;
    }

    for (const int player : _players)
    {
        const auto& playerComponent = _playerComponents.Get(player);
        auto& movement = _movementComponents.Get(player);

        if (!playerComponent.IsAlive)
        {
            movement.Direction = sf::Vector2f(0.0f, 0.0f);
            continue;
        }

        movement.Direction.x = directionX;
        movement.Direction.y = 0.0f;

        if (shootPressed)
        {
            const int eventEntity = world.CreateEntity();
            _shootEvents.Add(eventEntity, ShootInputEvent{player});
        }
    }
}
