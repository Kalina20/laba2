#ifndef GAMESTATECOMPONENT_H
#define GAMESTATECOMPONENT_H

struct GameStateComponent
{
    bool IsGameOver = false;
    int Player = -1;
    int Score = 0;

    GameStateComponent() = default;
    GameStateComponent(const bool isGameOver, const int player, const int score): IsGameOver(isGameOver), Player(player), Score(score) {}
};

#endif //GAMESTATECOMPONENT_H

