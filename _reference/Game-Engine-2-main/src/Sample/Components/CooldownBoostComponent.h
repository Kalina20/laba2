#ifndef COOLDOWNBOOSTCOMPONENT_H
#define COOLDOWNBOOSTCOMPONENT_H

struct CooldownBoostComponent
{
    float OriginalCooldownMs = 0.0f;
    float RemainingMs = 0.0f;
    float Multiplier = 0.5f;

    CooldownBoostComponent() = default;
    CooldownBoostComponent(const float originalCooldownMs, const float remainingMs, const float multiplier)
        : OriginalCooldownMs(originalCooldownMs),
          RemainingMs(remainingMs),
          Multiplier(multiplier)
    {
    }
};

#endif //COOLDOWNBOOSTCOMPONENT_H
