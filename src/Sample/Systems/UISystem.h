#ifndef UISYSTEM_H
#define UISYSTEM_H

#include "../../Ecs/Filter/FilterBuilder.h"
#include "../../Ecs/Systems/ISystem.h"

#include "../Components/AsteroidSpawnSettingsComponent.h"
#include "../Components/SpawnAsteroidEvent.h"
#include "../Components/TransformComponent.h"
#include "../Services/RenderService.h"

class UISystem final : public ISystem
{
    RenderService& _renderService;
    bool _isVisible = true;
    bool _toggleKeyHeld = false;

    ComponentStorage<AsteroidSpawnSettingsComponent>& _spawnSettingsComponents;
    ComponentStorage<SpawnAsteroidEvent>& _spawnAsteroidEventComponents;
    ComponentStorage<TransformComponent>& _transformComponents;

    Filter _spawnSettings;

public:
    UISystem(World& world, RenderService& renderService)
        : ISystem(world),
          _renderService(renderService),
          _spawnSettingsComponents(world.GetStorage<AsteroidSpawnSettingsComponent>()),
          _spawnAsteroidEventComponents(world.GetStorage<SpawnAsteroidEvent>()),
          _transformComponents(world.GetStorage<TransformComponent>()),
          _spawnSettings(FilterBuilder(world)
              .With<AsteroidSpawnSettingsComponent>()
              .Build())
    {
    }

    void OnInit() override {}
    void OnUpdate(float deltaTimeSeconds) override;
};

#endif //UISYSTEM_H
