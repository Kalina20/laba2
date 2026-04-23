#include "InitSystem.h"

#include "../Components/BoxColliderComponent.h"
#include "../Components/AsteroidSpawnSettingsComponent.h"
#include "../Components/CircleShapeComponent.h"
#include "../Components/CollisionComponent.h"
#include "../Components/MovementComponent.h"
#include "../Components/PlayerComponent.h"
#include "../Components/ShooterComponent.h"
#include "../Components/TransformComponent.h"

void InitSystem::OnInit()
{
    const int player = world.CreateEntity();
    auto& transformStorage = world.GetStorage<TransformComponent>();
    auto& movementStorage = world.GetStorage<MovementComponent>();
    auto& boxColliderStorage = world.GetStorage<BoxColliderComponent>();
    auto& collisionStorage = world.GetStorage<CollisionComponent>();
    auto& shapeStorage = world.GetStorage<CircleShapeComponent>();
    auto& shooterStorage = world.GetStorage<ShooterComponent>();
    auto& playerStorage = world.GetStorage<PlayerComponent>();
    auto& spawnSettingsStorage = world.GetStorage<AsteroidSpawnSettingsComponent>();

    transformStorage.Add(player, TransformComponent{sf::Vector2f(_windowWidth * 0.5f, _windowHeight - 60.0f)});
    movementStorage.Add(player, MovementComponent{sf::Vector2f(0.0f, 0.0f), _playerSpeed});
    boxColliderStorage.Add(player, BoxColliderComponent{sf::Vector2f(56.0f, 56.0f), sf::Vector2f(-28.0f, -28.0f)});
    collisionStorage.Add(player, CollisionComponent{});
    shapeStorage.Add(player, CircleShapeComponent{sf::CircleShape{}, 28.0f, 3, sf::Color::Cyan});
    shooterStorage.Add(player, ShooterComponent{true, _shootCooldownMs, -1000000});
    playerStorage.Add(player, PlayerComponent{0, true});

    const int spawnSettings = world.CreateEntity();
    spawnSettingsStorage.Add(spawnSettings, AsteroidSpawnSettingsComponent{_asteroidSpawnMinMs, _asteroidSpawnMaxMs});
}
