#ifndef SCORESYSTEM_H
#define SCORESYSTEM_H

#include "../../Ecs/Filter/FilterBuilder.h"
#include "../../Ecs/Systems/ISystem.h"

#include "../Components/AddScoreEvent.h"
#include "../Components/PlayerComponent.h"

class ScoreSystem final : public ISystem
{
    ComponentStorage<AddScoreEvent>& _addScoreEventComponents;
    ComponentStorage<PlayerComponent>& _playerComponents;

    Filter _addScoreEvents;
    Filter _players;

public:
    explicit ScoreSystem(World& world)
        : ISystem(world),
          _addScoreEventComponents(world.GetStorage<AddScoreEvent>()),
          _playerComponents(world.GetStorage<PlayerComponent>()),
          _addScoreEvents(FilterBuilder(world)
              .With<AddScoreEvent>()
              .Build()),
          _players(FilterBuilder(world)
              .With<PlayerComponent>()
              .Build())
    {
    }

    void OnInit() override {}
    void OnUpdate(float deltaTimeSeconds) override;
};

#endif //SCORESYSTEM_H
