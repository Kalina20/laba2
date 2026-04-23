#ifndef RECTANGLESHAPECOMPONENT_H
#define RECTANGLESHAPECOMPONENT_H

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>

struct RectangleShapeComponent
{
    sf::RectangleShape Shape{};
    sf::Vector2f Size{0.0f, 0.0f};
    sf::Color FillColor = sf::Color::White;
};

#endif //RECTANGLESHAPECOMPONENT_H
