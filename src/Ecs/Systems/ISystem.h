#ifndef ISYSTEM_H
#define ISYSTEM_H

#include "IInitializer.h"

class ISystem : public IInitializer
{
public:
    explicit ISystem(World &world) : IInitializer(world) {}

    ~ISystem() override = default;
    virtual void OnUpdate() {}

    virtual void OnUpdate(float deltaTimeSeconds)
    {
        (void)deltaTimeSeconds;
        OnUpdate();
    }
};

#endif //ISYSTEM_H
