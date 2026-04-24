#include "PauseSystem.h"

#include <vector>

void PauseSystem::OnInit()
{
    GetOrCreatePauseState();
}

PauseStateComponent& PauseSystem::GetOrCreatePauseState()
{
    for (const int entity : _pauseStates.Entities())
        return _pauseStates.Get(entity);

    const int pauseStateEntity = world.CreateEntity();
    return _pauseStates.Add(pauseStateEntity, PauseStateComponent(false));
}

void PauseSystem::OnUpdate()
{
    std::vector<int> eventsToRemove;

    for (const int eventEntity : _pauseToggleEvents)
    {
        auto& pauseState = GetOrCreatePauseState();
        pauseState.IsPaused = !pauseState.IsPaused;
        eventsToRemove.push_back(eventEntity);
    }

    for (const int eventEntity : eventsToRemove)
        world.RemoveEntity(eventEntity);
}
