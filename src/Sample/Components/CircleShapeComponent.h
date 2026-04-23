#ifndef CIRCLESHAPECOMPONENT_H
#define CIRCLESHAPECOMPONENT_H

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>

struct CircleShapeComponent
{
    sf::CircleShape Shape{};
    float Radius = 0.0f;
    unsigned int PointCount = 30;
    sf::Color FillColor = sf::Color::White;
};

#endif //CIRCLESHAPECOMPONENT_H
