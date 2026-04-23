#ifndef INITSYSTEM_H
#define INITSYSTEM_H

#include "../../Ecs/Systems/IInitializer.h"

class InitSystem final : public IInitializer {
    float _windowWidth;
    float _windowHeight;
    float _playerSpeed;
    int _shootCooldownMs;
    int _asteroidSpawnMinMs;
    int _asteroidSpawnMaxMs;

public:
    InitSystem(
        World& world,
        const float windowWidth,
        const float windowHeight,
        const float playerSpeed,
        const int shootCooldownMs,
        const int asteroidSpawnMinMs,
        const int asteroidSpawnMaxMs)
        : IInitializer(world),
          _windowWidth(windowWidth),
          _windowHeight(windowHeight),
          _playerSpeed(playerSpeed),
          _shootCooldownMs(shootCooldownMs),
          _asteroidSpawnMinMs(asteroidSpawnMinMs),
          _asteroidSpawnMaxMs(asteroidSpawnMaxMs)
    {
    }

    void OnInit() override;
};



#endif //INITSYSTEM_H
