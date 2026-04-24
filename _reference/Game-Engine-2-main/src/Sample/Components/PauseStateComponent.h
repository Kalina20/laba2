#ifndef PAUSESTATECOMPONENT_H
#define PAUSESTATECOMPONENT_H

#include "../../Ecs/Components/ComponentStorage.hpp"

struct PauseStateComponent
{
    bool IsPaused = false;

    PauseStateComponent() = default;
    PauseStateComponent(const bool isPaused): IsPaused(isPaused) {}
};

namespace PauseState
{
    inline bool IsPaused(ComponentStorage<PauseStateComponent>& pauseStates)
    {
        for (const int entity : pauseStates.Entities())
        {
            if (pauseStates.Get(entity).IsPaused)
                return true;
        }
        return false;
    }
}

#endif //PAUSESTATECOMPONENT_H
