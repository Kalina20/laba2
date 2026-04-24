#ifndef COOLDOWNBOOSTEVENT_H
#define COOLDOWNBOOSTEVENT_H

struct CooldownBoostEvent
{
    int Player = -1;
    float Multiplier = 0.5f;
    float DurationMs = 0.0f;

    CooldownBoostEvent() = default;
    CooldownBoostEvent(const int player, const float multiplier, const float durationMs)
        : Player(player),
          Multiplier(multiplier),
          DurationMs(durationMs)
    {
    }
};

#endif //COOLDOWNBOOSTEVENT_H
