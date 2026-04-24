#ifndef COOLDOWNBOOSTSYSTEM_H
#define COOLDOWNBOOSTSYSTEM_H

#include <SFML/System/Clock.hpp>

#include "../../Ecs/Filter/Filter.h"
#include "../../Ecs/Filter/FilterBuilder.h"
#include "../../Ecs/Systems/ISystem.h"

#include "../Components/CooldownBoostComponent.h"
#include "../Components/CooldownBoostEvent.h"
#include "../Components/PauseStateComponent.h"
#include "../Components/ShooterComponent.h"

class CooldownBoostSystem final : public ISystem
{
    ComponentStorage<CooldownBoostEvent>& _cooldownBoostEvents;
    ComponentStorage<CooldownBoostComponent>& _cooldownBoosts;
    ComponentStorage<ShooterComponent>& _shooters;
    ComponentStorage<PauseStateComponent>& _pauseStates;

    Filter _boostEvents;
    Filter _activeBoosts;
    sf::Clock _clock;

    void ApplyBoost(int playerEntity, float multiplier, float durationMs);
    void ClearBoost(int playerEntity);

public:
    CooldownBoostSystem(World& world)
        : ISystem(world),
          _cooldownBoostEvents(world.GetStorage<CooldownBoostEvent>()),
          _cooldownBoosts(world.GetStorage<CooldownBoostComponent>()),
          _shooters(world.GetStorage<ShooterComponent>()),
          _pauseStates(world.GetStorage<PauseStateComponent>()),
          _boostEvents(FilterBuilder(world)
              .With<CooldownBoostEvent>()
              .Build()),
          _activeBoosts(FilterBuilder(world)
              .With<CooldownBoostComponent>()
              .Build())
    {
    }

    void OnInit() override;
    void OnUpdate() override;
};

#endif //COOLDOWNBOOSTSYSTEM_H
