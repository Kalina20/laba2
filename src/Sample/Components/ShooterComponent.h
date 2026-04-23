#ifndef SHOOTERCOMPONENT_H
#define SHOOTERCOMPONENT_H

struct ShooterComponent
{
    bool CanShoot = true;
    int CooldownMs = 0;
    int LastShotTimeMs = -1000000;
};

#endif //SHOOTERCOMPONENT_H
