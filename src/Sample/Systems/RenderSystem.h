#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include <string>

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

#include "../../Ecs/Filter/FilterBuilder.h"
#include "../../Ecs/Systems/ISystem.h"

#include "../Components/CircleShapeComponent.h"
#include "../Components/PlayerComponent.h"
#include "../Components/RectangleShapeComponent.h"
#include "../Components/TransformComponent.h"
#include "../Services/RenderService.h"

class RenderSystem final : public ISystem
{
    RenderService& _renderService;
    float _windowWidth;
    float _windowHeight;

    ComponentStorage<TransformComponent>& _transformComponents;
    ComponentStorage<CircleShapeComponent>& _circleShapeComponents;
    ComponentStorage<RectangleShapeComponent>& _rectangleShapeComponents;
    ComponentStorage<PlayerComponent>& _playerComponents;

    Filter _circleRenderables;
    Filter _rectangleRenderables;
    Filter _players;

    sf::Font _font;
    sf::Text _scoreText;
    sf::Text _gameOverText;
    bool _hasFont = false;

    void DrawCircles();
    void DrawRectangles();
    void DrawHud(int score);
    bool GetPlayerState(bool& hasAlivePlayer, int& score) const;

public:
    RenderSystem(
        World& world,
        RenderService& renderService,
        const float windowWidth,
        const float windowHeight,
        const std::string& fontPath)
        : ISystem(world),
          _renderService(renderService),
          _windowWidth(windowWidth),
          _windowHeight(windowHeight),
          _transformComponents(world.GetStorage<TransformComponent>()),
          _circleShapeComponents(world.GetStorage<CircleShapeComponent>()),
          _rectangleShapeComponents(world.GetStorage<RectangleShapeComponent>()),
          _playerComponents(world.GetStorage<PlayerComponent>()),
          _circleRenderables(FilterBuilder(world)
              .With<TransformComponent>()
              .With<CircleShapeComponent>()
              .Build()),
          _rectangleRenderables(FilterBuilder(world)
              .With<TransformComponent>()
              .With<RectangleShapeComponent>()
              .Build()),
          _players(FilterBuilder(world)
              .With<PlayerComponent>()
              .Build()),
          _scoreText(_font),
          _gameOverText(_font)
    {
        _hasFont = _font.openFromFile(fontPath);
        if (_hasFont)
        {
            _scoreText.setCharacterSize(26);
            _scoreText.setFillColor(sf::Color::White);
            _scoreText.setPosition(sf::Vector2f(16.0f, 12.0f));

            _gameOverText.setCharacterSize(56);
            _gameOverText.setFillColor(sf::Color::White);
        }
    }

    void OnInit() override {}
    void OnUpdate(float deltaTimeSeconds) override;
};

#endif //RENDERSYSTEM_H
