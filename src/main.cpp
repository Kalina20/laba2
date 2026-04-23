#include <iostream>
#include <filesystem>
#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>

#include "Ecs/Systems/SystemsManager.h"
#include "Ecs/World/World.h"

#include "Sample/Services/ConfigService.h"
#include "Sample/Services/InputService.h"
#include "Sample/Services/RandomService.h"
#include "Sample/Services/RenderService.h"
#include "Sample/Services/TimeService.h"
#include "Sample/Systems/AsteroidSpawnSystem.h"
#include "Sample/Systems/BoundsCleanupSystem.h"
#include "Sample/Systems/CollisionDetectionSystem.h"
#include "Sample/Systems/CollisionResolveSystem.h"
#include "Sample/Systems/GameOverSystem.h"
#include "Sample/Systems/InitSystem.h"
#include "Sample/Systems/InputSystem.h"
#include "Sample/Systems/MovementSystem.h"
#include "Sample/Systems/RenderSystem.h"
#include "Sample/Systems/ScoreSystem.h"
#include "Sample/Systems/ShootSystem.h"
#include "Sample/Systems/UISystem.h"

int main() {
    // Пример использования
    setlocale(LC_ALL, "");

    const int wWidth = 1280;
    const int wHeight = 720;
    sf::RenderWindow window(sf::VideoMode({wWidth, wHeight}), "Test");
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);

    ConfigService configService;
    const std::filesystem::path configPath = std::filesystem::exists("src/Sample/Config/game.cfg")
        ? std::filesystem::path("src/Sample/Config/game.cfg")
        : std::filesystem::path("../src/Sample/Config/game.cfg");
    configService.Load(configPath.string());
    const GameConfig& config = configService.Get();
    const std::string fontPath = !config.UiFontPath.empty() ? config.UiFontPath : "C:/Windows/Fonts/arial.ttf";

    InputService inputService(window);
    RandomService randomService;
    RenderService renderService(window);
    TimeService timeService;

    World world;
    SystemsManager systems(world);
    systems.AddInitializer(std::make_shared<InitSystem>(
        world,
        static_cast<float>(wWidth),
        static_cast<float>(wHeight),
        config.PlayerSpeed,
        config.ShootCooldownMs,
        config.AsteroidSpawnMinMs,
        config.AsteroidSpawnMaxMs));
    systems.AddSystem(std::make_shared<InputSystem>(world, inputService));
    systems.AddSystem(std::make_shared<ShootSystem>(world, timeService, config.BulletSpeed));
    systems.AddSystem(std::make_shared<AsteroidSpawnSystem>(
        world,
        timeService,
        randomService,
        config,
        static_cast<float>(wWidth)));
    systems.AddSystem(std::make_shared<MovementSystem>(world, static_cast<float>(wWidth)));
    systems.AddSystem(std::make_shared<BoundsCleanupSystem>(
        world,
        static_cast<float>(wWidth),
        static_cast<float>(wHeight)));
    systems.AddSystem(std::make_shared<CollisionDetectionSystem>(world));
    systems.AddSystem(std::make_shared<CollisionResolveSystem>(world));
    systems.AddSystem(std::make_shared<ScoreSystem>(world));
    systems.AddSystem(std::make_shared<GameOverSystem>(
        world,
        inputService,
        static_cast<float>(wWidth),
        static_cast<float>(wHeight),
        config.PlayerSpeed,
        config.ShootCooldownMs,
        config.AsteroidSpawnMinMs,
        config.AsteroidSpawnMaxMs));
    systems.AddSystem(std::make_shared<RenderSystem>(
        world,
        renderService,
        static_cast<float>(wWidth),
        static_cast<float>(wHeight),
        fontPath));
    systems.AddSystem(std::make_shared<UISystem>(world, renderService));
    timeService.RestartGameClock();

    while (window.isOpen()) {
        const float deltaTimeSeconds = timeService.RestartFrame();
        systems.Update(deltaTimeSeconds);
    }

    ImGui::SFML::Shutdown();
    return 0;
}
