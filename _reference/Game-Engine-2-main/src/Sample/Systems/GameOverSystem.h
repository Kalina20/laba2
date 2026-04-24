#ifndef GAMEOVERSYSTEM_H
#define GAMEOVERSYSTEM_H

#include "../../Ecs/Filter/Filter.h"
#include "../../Ecs/Filter/FilterBuilder.h"
#include "../../Ecs/Systems/ISystem.h"

#include "../Components/AsteroidComponent.h"
#include "../Components/GameOverEvent.h"
#include "../Components/GameStateComponent.h"

class GameOverSystem final : public ISystem
{
    ComponentStorage<GameOverEvent>& _gameOverEvents;
    ComponentStorage<GameStateComponent>& _gameStates;

    Filter _gameOverEventsFilter;
    Filter _gameStatesFilter;
    Filter _asteroids;

public:
    GameOverSystem(World& world)
        : ISystem(world),
          _gameOverEvents(world.GetStorage<GameOverEvent>()),
          _gameStates(world.GetStorage<GameStateComponent>()),
          _gameOverEventsFilter(FilterBuilder(world)
              .With<GameOverEvent>()
              .Build()),
          _gameStatesFilter(FilterBuilder(world)
              .With<GameStateComponent>()
              .Build()),
          _asteroids(FilterBuilder(world)
              .With<AsteroidComponent>()
              .Build())
    {
    }

    void OnInit() override;
    void OnUpdate() override;
};

#endif //GAMEOVERSYSTEM_H
