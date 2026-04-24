#ifndef ASTEROIDSPAWNSETTINGSCOMPONENT_H
#define ASTEROIDSPAWNSETTINGSCOMPONENT_H

struct AsteroidSpawnSettingsComponent
{
    float MinSpawnPeriodMs = 0.0f;
    float MaxSpawnPeriodMs = 0.0f;

    AsteroidSpawnSettingsComponent() = default;
    AsteroidSpawnSettingsComponent(const float minSpawnPeriodMs, const float maxSpawnPeriodMs)
        : MinSpawnPeriodMs(minSpawnPeriodMs),
          MaxSpawnPeriodMs(maxSpawnPeriodMs)
    {
    }
};

#endif //ASTEROIDSPAWNSETTINGSCOMPONENT_H
