#include "ScoreSystem.h"

#include <vector>

void ScoreSystem::OnUpdate(const float deltaTimeSeconds)
{
    (void)deltaTimeSeconds;

    int scoreDelta = 0;
    std::vector<int> eventsToRemove;

    for (const int eventEntity : _addScoreEvents)
    {
        if (_addScoreEventComponents.Has(eventEntity))
        {
            scoreDelta += _addScoreEventComponents.Get(eventEntity).Value;
            eventsToRemove.push_back(eventEntity);
        }
    }

    if (scoreDelta != 0)
    {
        for (const int player : _players)
        {
            auto& playerComponent = _playerComponents.Get(player);
            playerComponent.Score += scoreDelta;
        }
    }

    for (const int eventEntity : eventsToRemove)
    {
        if (world.IsEntityAlive(eventEntity))
        {
            world.RemoveEntity(eventEntity);
        }
    }
}
