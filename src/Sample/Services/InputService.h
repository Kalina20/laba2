#ifndef INPUTSERVICE_H
#define INPUTSERVICE_H

#include <optional>

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Window.hpp>

class InputService
{
    sf::Window& _window;

public:
    explicit InputService(sf::Window& window) : _window(window) {}

    sf::Window& Window() const
    {
        return _window;
    }

    std::optional<sf::Event> PollEvent()
    {
        return _window.pollEvent();
    }

    bool IsPressed(const sf::Keyboard::Scancode key) const
    {
        return sf::Keyboard::isKeyPressed(key);
    }

    bool IsAnyKeyPressed() const
    {
        for (int code = 0; code < static_cast<int>(sf::Keyboard::ScancodeCount); ++code)
        {
            if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Scancode>(code)))
            {
                return true;
            }
        }
        return false;
    }

    void SetKeyRepeatEnabled(const bool enabled)
    {
        _window.setKeyRepeatEnabled(enabled);
    }

    void Close()
    {
        _window.close();
    }
};

#endif //INPUTSERVICE_H
