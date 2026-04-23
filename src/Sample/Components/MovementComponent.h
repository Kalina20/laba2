#ifndef MOVEMENTCOMPONENT_H
#define MOVEMENTCOMPONENT_H

#include <SFML/System/Vector2.hpp>

struct MovementComponent
{
    sf::Vector2f Direction{0.0f, 0.0f};
    float Speed = 0.0f;
};

#endif //MOVEMENTCOMPONENT_H
