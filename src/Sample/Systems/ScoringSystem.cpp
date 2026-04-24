#include "ScoringSystem.h"

#include <vector>

void ScoringSystem::OnInit()
{
}

void ScoringSystem::OnUpdate()
{
    std::vector<int> eventsToRemove;

    for (const auto eventEntity : _scoreIncreaseEventsFilter)
    {
        const auto& scoreEvent = _scoreIncreaseEvents.Get(eventEntity);

        if (_players.Has(scoreEvent.Player)){
            auto& player = _players.Get(scoreEvent.Player);
            player.AddScore(scoreEvent.Value);
        }

        eventsToRemove.push_back(eventEntity);
    }

    for (const int eventEntity : eventsToRemove)
        world.RemoveEntity(eventEntity);
}
