#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H

#include "../../Ecs/Filter/Filter.h"
#include "../../Ecs/Filter/FilterBuilder.h"
#include "../../Ecs/Systems/ISystem.h"

#include "../Components/MovementComponent.h"
#include "../Components/PlayerComponent.h"
#include "../Components/ShootInputEvent.h"
#include "../Services/InputService.h"

class InputSystem : public ISystem {
    InputService& _input;
    ComponentStorage<MovementComponent>& _movementComponents;
    ComponentStorage<PlayerComponent>& _playerComponents;
    ComponentStorage<ShootInputEvent>& _shootEvents;
    Filter _players;

public:
    InputSystem(World& world, InputService& input)
        : ISystem(world),
        _input(input),
        _movementComponents(world.GetStorage<MovementComponent>()),
        _playerComponents(world.GetStorage<PlayerComponent>()),
        _shootEvents(world.GetStorage<ShootInputEvent>()),
        _players(FilterBuilder(world)
            .With<PlayerComponent>()
            .With<MovementComponent>()
            .Build())
    {

    }

    void OnInit() override;

    void OnUpdate(float deltaTimeSeconds) override;
};



#endif //INPUTSYSTEM_H
