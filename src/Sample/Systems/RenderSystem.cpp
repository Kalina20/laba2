#include "RenderSystem.h"

#include <string>

void RenderSystem::DrawCircles()
{
    for (const int entity : _circleRenderables)
    {
        const auto& transform = _transformComponents.Get(entity);
        auto& circle = _circleShapeComponents.Get(entity);

        circle.Shape.setRadius(circle.Radius);
        circle.Shape.setPointCount(circle.PointCount);
        circle.Shape.setFillColor(circle.FillColor);
        circle.Shape.setOrigin(sf::Vector2f(circle.Radius, circle.Radius));
        circle.Shape.setPosition(transform.Position);

        _renderService.Draw(circle.Shape);
    }
}

void RenderSystem::DrawRectangles()
{
    for (const int entity : _rectangleRenderables)
    {
        const auto& transform = _transformComponents.Get(entity);
        auto& rectangle = _rectangleShapeComponents.Get(entity);

        rectangle.Shape.setSize(rectangle.Size);
        rectangle.Shape.setFillColor(rectangle.FillColor);
        rectangle.Shape.setOrigin(rectangle.Size * 0.5f);
        rectangle.Shape.setPosition(transform.Position);

        _renderService.Draw(rectangle.Shape);
    }
}

void RenderSystem::DrawHud(const int score)
{
    if (!_hasFont)
    {
        return;
    }

    _scoreText.setString("Score: " + std::to_string(score));
    _renderService.Draw(_scoreText);
}

bool RenderSystem::GetPlayerState(bool& hasAlivePlayer, int& score) const
{
    bool hasAnyPlayer = false;
    hasAlivePlayer = false;
    score = 0;

    for (const int player : _players)
    {
        hasAnyPlayer = true;
        const auto& playerComponent = _playerComponents.Get(player);
        score = playerComponent.Score;
        if (playerComponent.IsAlive)
        {
            hasAlivePlayer = true;
        }
    }

    return hasAnyPlayer;
}

void RenderSystem::OnUpdate(const float deltaTimeSeconds)
{
    (void)deltaTimeSeconds;

    bool hasAlivePlayer = true;
    int playerScore = 0;
    const bool hasPlayer = GetPlayerState(hasAlivePlayer, playerScore);

    _renderService.BeginFrame(sf::Color(10, 10, 18));

    if (!hasPlayer || hasAlivePlayer)
    {
        DrawCircles();
        DrawRectangles();
        DrawHud(playerScore);
    }
    else if (_hasFont)
    {
        _gameOverText.setString("Game Over\nScore: " + std::to_string(playerScore) + "\nPress any key");
        const sf::FloatRect localBounds = _gameOverText.getLocalBounds();
        _gameOverText.setOrigin(sf::Vector2f(localBounds.position.x + localBounds.size.x * 0.5f,
            localBounds.position.y + localBounds.size.y * 0.5f));
        _gameOverText.setPosition(sf::Vector2f(_windowWidth * 0.5f, _windowHeight * 0.5f));
        _renderService.Draw(_gameOverText);
    }

}
