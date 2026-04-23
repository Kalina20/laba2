#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

#include "../../Ecs/Filter/FilterBuilder.h"
#include "../../Ecs/Systems/ISystem.h"

#include "../Components/MovementComponent.h"
#include "../Components/PlayerComponent.h"
#include "../Components/TransformComponent.h"

class MovementSystem final : public ISystem {
    ComponentStorage<TransformComponent>& _transformComponents;
    ComponentStorage<MovementComponent>& _movementComponents;
    ComponentStorage<PlayerComponent>& _playerComponents;

    float _windowWidth;

    Filter _movables;
    Filter _players;

    void ClampPlayerToBounds(int playerEntity) const;

public:
    MovementSystem(World &world, const float windowWidth)
        : ISystem(world),
            _transformComponents(world.GetStorage<TransformComponent>()),
            _movementComponents(world.GetStorage<MovementComponent>()),
            _playerComponents(world.GetStorage<PlayerComponent>()),
            _windowWidth(windowWidth),
            _movables(FilterBuilder(world)
                .With<TransformComponent>()
                .With<MovementComponent>()
                .Build()),
            _players(FilterBuilder(world)
                .With<PlayerComponent>()
                .With<TransformComponent>()
                .With<MovementComponent>()
                .Build())
    {
    }

    void OnInit() override;

    void OnUpdate(float deltaTimeSeconds) override;
};

#endif //MOVEMENTSYSTEM_H
