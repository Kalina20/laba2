#include "GameOverSystem.h"

#include <vector>

void GameOverSystem::OnInit()
{
}

void GameOverSystem::OnUpdate()
{
    std::vector<int> eventsToRemove;
    std::vector<int> asteroidsToRemove;

    for (const auto eventEntity : _gameOverEventsFilter)
    {
        const auto& gameOverEvent = _gameOverEvents.Get(eventEntity);

        int gameStateEntity = -1;
        for (const auto entity : _gameStatesFilter)
        {
            gameStateEntity = entity;
            break;
        }

        if (gameStateEntity == -1)
        {
            gameStateEntity = world.CreateEntity();
            _gameStates.Add(gameStateEntity, GameStateComponent(true, gameOverEvent.Player, gameOverEvent.Score));
        }
        else
        {
            auto& gameState = _gameStates.Get(gameStateEntity);
            gameState.IsGameOver = true;
            gameState.Player = gameOverEvent.Player;
            gameState.Score = gameOverEvent.Score;
        }

        eventsToRemove.push_back(eventEntity);
    }

    if (!eventsToRemove.empty())
    {
        for (const int asteroid : _asteroids)
            asteroidsToRemove.push_back(asteroid);
    }

    for (const int asteroid : asteroidsToRemove)
    {
        if (world.IsEntityAlive(asteroid))
            world.RemoveEntity(asteroid);
    }

    for (const int eventEntity : eventsToRemove)
        world.RemoveEntity(eventEntity);
}

