#include <iostream>
#include <SFML/Graphics.hpp>

#include "Ecs/Systems/SystemsManager.h"
#include "Ecs/World/World.h"

#include "Config/Config.h"

#include "Sample/Systems/AsteroidSpawnSystem.h"
#include "Sample/Systems/CollisionDetectionSystem.h"
#include "Sample/Systems/CollisionHandlerSystem.h"
#include "Sample/Systems/CooldownBoostSystem.h"
#include "Sample/Systems/GameOverSystem.h"
#include "Sample/Systems/InputSystem.h"
#include "Sample/Systems/MovementSystem.h"
#include "Sample/Systems/OutOfScreenCleanupSystem.h"
#include "Sample/Systems/PauseSystem.h"
#include "Sample/Systems/RenderSystem.h"
#include "Sample/Systems/RestartSystem.h"
#include "Sample/Systems/ScoringSystem.h"
#include "Sample/Systems/ShootSystem.h"
#include "Sample/Systems/UfoSpawnSystem.h"

int main() {
    // Пример использования
    setlocale(LC_ALL, "");

    Config config("config.txt");
    const int windowWidth = config.getFloat("window_width");
    const int windowHeight = config.getFloat("window_height");
    std::cout << windowHeight << " " << windowWidth << "\n";

    sf::RenderWindow window(sf::VideoMode({
        static_cast<unsigned int>(windowWidth),
        static_cast<unsigned int>(windowHeight)
    }), "COOL SPACE SHOOTER");
    window.setFramerateLimit(60);

    World world;
    SystemsManager systems(world);
    systems.AddSystem(std::make_shared<InputSystem>(world));
    systems.AddSystem(std::make_shared<PauseSystem>(world));
    systems.AddSystem(std::make_shared<RestartSystem>(world));
    systems.AddSystem(std::make_shared<ShootSystem>(world));
    systems.AddSystem(std::make_shared<AsteroidSpawnSystem>(world,windowWidth));
    systems.AddSystem(std::make_shared<UfoSpawnSystem>(world, windowWidth));
    systems.AddSystem(std::make_shared<MovementSystem>(world));
    systems.AddSystem(std::make_shared<CollisionDetectionSystem>(world));
    systems.AddSystem(std::make_shared<CollisionHandlerSystem>(world));
    systems.AddSystem(std::make_shared<ScoringSystem>(world));
    systems.AddSystem(std::make_shared<CooldownBoostSystem>(world));
    systems.AddSystem(std::make_shared<GameOverSystem>(world));
    systems.AddSystem(std::make_shared<RenderSystem>(world, window));
    systems.AddSystem(std::make_shared<OutOfScreenCleanupSystem>(world));

    while (window.isOpen()) {
        systems.Update();
    }

    return 0;
}
