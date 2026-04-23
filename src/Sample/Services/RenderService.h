#ifndef RENDERSERVICE_H
#define RENDERSERVICE_H

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class RenderService
{
    sf::RenderWindow& _window;

public:
    explicit RenderService(sf::RenderWindow& window) : _window(window) {}

    sf::RenderWindow& Window() const
    {
        return _window;
    }

    void BeginFrame(const sf::Color clearColor = sf::Color::Black)
    {
        _window.clear(clearColor);
    }

    void Draw(const sf::Drawable& drawable)
    {
        _window.draw(drawable);
    }

    void EndFrame()
    {
        _window.display();
    }
};

#endif //RENDERSERVICE_H
