#ifndef PAUSESYSTEM_H
#define PAUSESYSTEM_H

#include "../../Ecs/Filter/Filter.h"
#include "../../Ecs/Filter/FilterBuilder.h"
#include "../../Ecs/Systems/ISystem.h"

#include "../Components/PauseStateComponent.h"
#include "../Components/PauseToggleEvent.h"

class PauseSystem final : public ISystem
{
    ComponentStorage<PauseStateComponent>& _pauseStates;

    Filter _pauseToggleEvents;

    PauseStateComponent& GetOrCreatePauseState();

public:
    PauseSystem(World& world)
        : ISystem(world),
          _pauseStates(world.GetStorage<PauseStateComponent>()),
          _pauseToggleEvents(FilterBuilder(world)
              .With<PauseToggleEvent>()
              .Build())
    {
    }

    void OnInit() override;
    void OnUpdate() override;
};

#endif //PAUSESYSTEM_H
