#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

#include "../../Ecs/Filter/Filter.h"
#include "../../Ecs/Filter/FilterBuilder.h"
#include "../../Ecs/Systems/ISystem.h"

#include "../Components/PositionComponent.h"
#include "../Components/MovementComponent.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/PauseStateComponent.h"
#include "../Components/PlayerComponent.h"

class MovementSystem final : public ISystem {
    ComponentStorage<PositionComponent>& _positionComponents;
    ComponentStorage<MovementComponent>& _movementComponents;
    ComponentStorage<PauseStateComponent>& _pauseStates;
    ComponentStorage<PlayerComponent>& _players;
    ComponentStorage<BoxColliderComponent>& _boxColliders;

    Filter _moveables;
    float _windowWidth = 0.0f;

    void ClampPlayerPosition(int entity);

    void Print(int ent); // ��� ���� ����� ������� � ��������� �������

public:
    MovementSystem(World &world)
        : ISystem(world),
            _positionComponents(world.GetStorage<PositionComponent>()),
            _movementComponents(world.GetStorage<MovementComponent>()),
            _pauseStates(world.GetStorage<PauseStateComponent>()),
            _players(world.GetStorage<PlayerComponent>()),
            _boxColliders(world.GetStorage<BoxColliderComponent>()),
            _moveables(FilterBuilder(world)
                .With<PositionComponent>()
                .With<MovementComponent>()
                .Build())
    {
    }

    void OnInit() override;

    void OnUpdate() override;
};

#endif //MOVEMENTSYSTEM_H
