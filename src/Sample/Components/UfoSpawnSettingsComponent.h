#ifndef UFOSPAWNSETTINGSCOMPONENT_H
#define UFOSPAWNSETTINGSCOMPONENT_H

struct UfoSpawnSettingsComponent
{
    float MinSpawnPeriodMs = 0.0f;
    float MaxSpawnPeriodMs = 0.0f;

    UfoSpawnSettingsComponent() = default;
    UfoSpawnSettingsComponent(const float minSpawnPeriodMs, const float maxSpawnPeriodMs)
        : MinSpawnPeriodMs(minSpawnPeriodMs),
          MaxSpawnPeriodMs(maxSpawnPeriodMs)
    {
    }
};

#endif //UFOSPAWNSETTINGSCOMPONENT_H
