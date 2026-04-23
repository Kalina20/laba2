set(TARGET_NAME main)
set(SOURCES main.cpp
        Sample/Services/GameConfig.h
        Sample/Services/ConfigService.h
        Sample/Services/InputService.h
        Sample/Services/TimeService.h
        Sample/Services/RenderService.h
        Sample/Services/RandomService.h
        Sample/Systems/MovementSystem.cpp
        Sample/Systems/MovementSystem.h
        Sample/Systems/AsteroidSpawnSystem.cpp
        Sample/Systems/AsteroidSpawnSystem.h
        Sample/Systems/BoundsCleanupSystem.cpp
        Sample/Systems/BoundsCleanupSystem.h
        Sample/Systems/CollisionDetectionSystem.cpp
        Sample/Systems/CollisionDetectionSystem.h
        Sample/Systems/CollisionResolveSystem.cpp
        Sample/Systems/CollisionResolveSystem.h
        Sample/Systems/ScoreSystem.cpp
        Sample/Systems/ScoreSystem.h
        Sample/Systems/GameOverSystem.cpp
        Sample/Systems/GameOverSystem.h
        Sample/Systems/RenderSystem.cpp
        Sample/Systems/RenderSystem.h
        Sample/Systems/UISystem.cpp
        Sample/Systems/UISystem.h
        Sample/Systems/ShootSystem.cpp
        Sample/Systems/ShootSystem.h
        Sample/Systems/InitSystem.cpp
        Sample/Systems/InitSystem.h
        Sample/Components/TransformComponent.h
        Sample/Components/MovementComponent.h
        Sample/Components/CollisionComponent.h
        Sample/Components/BoxColliderComponent.h
        Sample/Components/CircleColliderComponent.h
        Sample/Components/CircleShapeComponent.h
        Sample/Components/RectangleShapeComponent.h
        Sample/Components/ShooterComponent.h
        Sample/Components/PlayerComponent.h
        Sample/Components/BulletComponent.h
        Sample/Components/AsteroidComponent.h
        Sample/Components/AsteroidSpawnSettingsComponent.h
        Sample/Components/ShootInputEvent.h
        Sample/Components/SpawnAsteroidEvent.h
        Sample/Components/AddScoreEvent.h
        Sample/Components/GameOverEvent.h
        Sample/Systems/InputSystem.cpp
        Sample/Systems/InputSystem.h
        Sample/Components/PositionComponent.h
)

add_subdirectory(Ecs)

add_executable(${TARGET_NAME} 
    ${SOURCES})

#target_compile_options(${TARGET_NAME} PRIVATE -Wall -Wextra -Wpedantic -Werror)
target_compile_features(${TARGET_NAME} PRIVATE cxx_std_20)

target_link_libraries(${TARGET_NAME} PUBLIC ${ECS_LIB_NAME})
target_link_libraries(${TARGET_NAME} PUBLIC ImGui-SFML::ImGui-SFML)
