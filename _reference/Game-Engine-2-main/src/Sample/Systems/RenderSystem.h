#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/String.hpp>
#include <SFML/Window/Event.hpp>

#include "../../Ecs/Filter/Filter.h"
#include "../../Ecs/Filter/FilterBuilder.h"
#include "../../Ecs/Systems/ISystem.h"

#include "../Components/CircleShapeComponent.h"
#include "../Components/GameStateComponent.h"
#include "../Components/GuiToggleEvent.h"
#include "../Components/PauseStateComponent.h"
#include "../Components/PlayerComponent.h"
#include "../Components/PositionComponent.h"
#include "../Components/RectangleShapeComponent.h"
#include "../../GUI/GUI.h"

class RenderSystem final : public ISystem
{
    sf::RenderWindow& _window;
    sf::Font _font;
    sf::Clock _imguiClock;
    GUI _gui;
    bool _imguiInitialized = false;
    unsigned int _textSize = 24;

    ComponentStorage<PositionComponent>& _positions;
    ComponentStorage<CircleShapeComponent>& _circleShapes;
    ComponentStorage<RectangleShapeComponent>& _rectangleShapes;
    ComponentStorage<PlayerComponent>& _players;
    ComponentStorage<GameStateComponent>& _gameStates;
    ComponentStorage<PauseStateComponent>& _pauseStates;

    Filter _circleShapeEntities;
    Filter _rectangleShapeEntities;
    Filter _playerEntities;
    Filter _gameStateEntities;
    Filter _guiToggleEvents;

    int GetPlayerScore();
    int GetGameOverScore();
    bool IsGameOver();
    void HandleGuiToggleEvents();
    void HandleWindowEvents();
    void DrawGame();
    void DrawGameOver();
    void DrawPause();
    void DrawTextCentered(const sf::String& string);
    void ShutdownImGui();

public:
    RenderSystem(World& world, sf::RenderWindow& window)
        : ISystem(world),
          _window(window),
          _positions(world.GetStorage<PositionComponent>()),
          _circleShapes(world.GetStorage<CircleShapeComponent>()),
          _rectangleShapes(world.GetStorage<RectangleShapeComponent>()),
          _players(world.GetStorage<PlayerComponent>()),
          _gameStates(world.GetStorage<GameStateComponent>()),
          _pauseStates(world.GetStorage<PauseStateComponent>()),
          _circleShapeEntities(FilterBuilder(world)
              .With<PositionComponent>()
              .With<CircleShapeComponent>()
              .Build()),
          _rectangleShapeEntities(FilterBuilder(world)
              .With<PositionComponent>()
              .With<RectangleShapeComponent>()
              .Build()),
          _playerEntities(FilterBuilder(world)
              .With<PlayerComponent>()
              .Build()),
          _gameStateEntities(FilterBuilder(world)
              .With<GameStateComponent>()
              .Build()),
          _guiToggleEvents(FilterBuilder(world)
              .With<GuiToggleEvent>()
              .Build())
    {
    }

    ~RenderSystem() override;

    void OnInit() override;
    void OnUpdate() override;
};

#endif //RENDERSYSTEM_H
