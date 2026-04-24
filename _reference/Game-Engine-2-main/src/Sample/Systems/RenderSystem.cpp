#include "RenderSystem.h"

#include "imgui-SFML.h"

#include <optional>
#include <string>
#include <vector>

#include "../../Config/Config.h"

void RenderSystem::OnInit()
{
    Config config("config.txt");
    _textSize = config.getInt("text_size");
    _font.openFromFile(config.getString("font_path"));
    _imguiInitialized = ImGui::SFML::Init(_window);
}

RenderSystem::~RenderSystem()
{
    ShutdownImGui();
}

void RenderSystem::ShutdownImGui()
{
    if (!_imguiInitialized)
        return;

    ImGui::SFML::Shutdown();
    _imguiInitialized = false;
}

int RenderSystem::GetPlayerScore()
{
    for (const int playerEntity : _playerEntities)
        return _players.Get(playerEntity).Score;

    return 0;
}

int RenderSystem::GetGameOverScore()
{
    for (const int gameStateEntity : _gameStateEntities)
        return _gameStates.Get(gameStateEntity).Score;

    return GetPlayerScore();
}

bool RenderSystem::IsGameOver()
{
    for (const int gameStateEntity : _gameStateEntities)
    {
        if (_gameStates.Get(gameStateEntity).IsGameOver)
            return true;
    }

    return false;
}

void RenderSystem::HandleWindowEvents()
{
    while (const std::optional event = _window.pollEvent())
    {
        ImGui::SFML::ProcessEvent(_window, *event);

        if (event->is<sf::Event::Closed>())
        {
            ShutdownImGui();
            _window.close();
        }
    }
}

void RenderSystem::HandleGuiToggleEvents()
{
    std::vector<int> eventsToRemove;

    for (const int eventEntity : _guiToggleEvents)
    {
        _gui.ToggleCollapsed();
        eventsToRemove.push_back(eventEntity);
    }

    for (const int eventEntity : eventsToRemove)
        world.RemoveEntity(eventEntity);
}

void RenderSystem::DrawGame()
{
    for (const int entity : _circleShapeEntities)
    {
        auto& shape = _circleShapes.Get(entity).Shape;
        const auto& position = _positions.Get(entity).Position;
        shape.setPosition(position);
        _window.draw(shape);
    }

    for (const int entity : _rectangleShapeEntities)
    {
        auto& shape = _rectangleShapes.Get(entity).Shape;
        const auto& position = _positions.Get(entity).Position;
        shape.setPosition(position);
        _window.draw(shape);
    }

    sf::Text scoreText(_font);
    scoreText.setCharacterSize(_textSize);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setString("Score: " + std::to_string(GetPlayerScore()));
    scoreText.setPosition({20.0f, 20.0f});
    _window.draw(scoreText);
}

void RenderSystem::DrawTextCentered(const sf::String& string)
{
    sf::Text text(_font);
    text.setCharacterSize(_textSize * 2);
    text.setFillColor(sf::Color::White);
    text.setString(string);

    const sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin({
        bounds.position.x + bounds.size.x / 2.0f,
        bounds.position.y + bounds.size.y / 2.0f
    });

    const sf::Vector2u windowSize = _window.getSize();
    text.setPosition({
        windowSize.x / 2.0f,
        windowSize.y / 2.0f
    });

    _window.draw(text);
}

void RenderSystem::DrawGameOver()
{
    DrawTextCentered("Game Over\nScore: " + std::to_string(GetGameOverScore()));
}

void RenderSystem::DrawPause()
{
    DrawTextCentered("Pause");
}

void RenderSystem::OnUpdate()
{
    HandleWindowEvents();

    if (!_window.isOpen())
        return;

    HandleGuiToggleEvents();
    ImGui::SFML::Update(_window, _imguiClock.restart());

    _window.clear(sf::Color::Black);

    if (PauseState::IsPaused(_pauseStates))
        DrawPause();
    else if (IsGameOver())
        DrawGameOver();
    else
        DrawGame();

    _gui.Draw(world);
    ImGui::SFML::Render(_window);
    _window.display();
}
