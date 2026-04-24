#ifndef SCOREINCREASEEVENT_H
#define SCOREINCREASEEVENT_H

struct ScoreIncreaseEvent
{
    int Player = -1;
    int Value = 0;

    ScoreIncreaseEvent() = default;
    ScoreIncreaseEvent(const int player, const int value): Player(player), Value(value) {}
};

#endif //SCOREINCREASEEVENT_H
