#ifndef SHOOTINPUTEVENT_H
#define SHOOTINPUTEVENT_H

struct ShootInputEvent
{
    int Entity = -1;
    bool Shoot = false;

    ShootInputEvent() = default;
    ShootInputEvent(const int entity, const bool shoot): Entity(entity), Shoot(shoot) {}
};

#endif //SHOOTINPUTEVENT_H
