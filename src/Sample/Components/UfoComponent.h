#ifndef UFOCOMPONENT_H
#define UFOCOMPONENT_H

struct UfoComponent
{
    float Speed = 0.0f;

    UfoComponent() = default;
    UfoComponent(const float speed): Speed(speed) {}
};

#endif //UFOCOMPONENT_H
