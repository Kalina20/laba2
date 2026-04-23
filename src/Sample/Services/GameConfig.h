#ifndef GAMECONFIG_H
#define GAMECONFIG_H

#include <string>

struct GameConfig
{
    float PlayerSpeed = 380.0f;
    int ShootCooldownMs = 250;
    float BulletSpeed = 700.0f;

    int AsteroidSpawnMinMs = 500;
    int AsteroidSpawnMaxMs = 1300;

    float AsteroidSpeedMin = 80.0f;
    float AsteroidSpeedMax = 220.0f;
    float AsteroidRadiusMin = 12.0f;
    float AsteroidRadiusMax = 34.0f;
    float AsteroidDirXMin = -0.45f;
    float AsteroidDirXMax = 0.45f;
    float AsteroidDirYMin = 0.65f;
    float AsteroidDirYMax = 1.0f;

    int AsteroidPointsMin = 8;
    int AsteroidPointsMax = 22;

    std::string UiFontPath = "";
};

#endif //GAMECONFIG_H
