#ifndef CIRCLECOLLIDERCOMPONENT_H
#define CIRCLECOLLIDERCOMPONENT_H

#include <SFML/System/Vector2.hpp>

struct CircleColliderComponent
{
    float Radius = 0.0f;
    sf::Vector2f Offset{0.0f, 0.0f};
};

#endif //CIRCLECOLLIDERCOMPONENT_H
