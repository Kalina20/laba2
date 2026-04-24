#ifndef SCORINGSYSTEM_H
#define SCORINGSYSTEM_H

#include "../../Ecs/Filter/Filter.h"
#include "../../Ecs/Filter/FilterBuilder.h"
#include "../../Ecs/Systems/ISystem.h"

#include "../Components/PlayerComponent.h"
#include "../Components/ScoreIncreaseEvent.h"

class ScoringSystem final : public ISystem
{
    ComponentStorage<PlayerComponent>& _players;
    ComponentStorage<ScoreIncreaseEvent>& _scoreIncreaseEvents;

    Filter _scoreIncreaseEventsFilter;

public:
    ScoringSystem(World& world)
        : ISystem(world),
          _players(world.GetStorage<PlayerComponent>()),
          _scoreIncreaseEvents(world.GetStorage<ScoreIncreaseEvent>()),
          _scoreIncreaseEventsFilter(FilterBuilder(world)
              .With<ScoreIncreaseEvent>()
              .Build())
    {
    }

    void OnInit() override;
    void OnUpdate() override;
};

#endif //SCORINGSYSTEM_H
