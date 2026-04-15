#include "SystemsManager.h"

SystemsManager::SystemsManager(World &world) : _world(world)
{
}

SystemsManager& SystemsManager::AddInitializer(std::shared_ptr<IInitializer> initializer)
{
    _newInitializers.push_back(std::move(initializer));
    return *this;
}

SystemsManager& SystemsManager::AddSystem(std::shared_ptr<ISystem> system)
{
    AddInitializer(system);
    _systems.push_back(std::move(system));
    return *this;
}

void SystemsManager::Initialize()
{
    if (_newInitializers.empty())
    {
        return;
    }

    for (const auto& initializer : _newInitializers)
    {
        initializer->OnInit();
        _initializers.push_back(initializer);
    }
    _newInitializers.clear();
}

void SystemsManager::Update()
{
    Initialize();

    for (const auto& system : _systems)
    {
        system->OnUpdate();
    }
}
