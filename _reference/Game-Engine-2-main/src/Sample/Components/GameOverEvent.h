#ifndef GAMEOVEREVENT_H
#define GAMEOVEREVENT_H

struct GameOverEvent
{
    int Player = -1;
    int Score = 0;

    GameOverEvent() = default;
    GameOverEvent(const int player, const int score): Player(player), Score(score) {}
};

#endif //GAMEOVEREVENT_H

