#ifndef BOXCOLLIDERCOMPONENT_H
#define BOXCOLLIDERCOMPONENT_H

#include <SFML/System/Vector2.hpp>

struct BoxColliderComponent
{
    sf::Vector2f Size{0.0f, 0.0f};
    sf::Vector2f Offset{0.0f, 0.0f};
};

#endif //BOXCOLLIDERCOMPONENT_H
