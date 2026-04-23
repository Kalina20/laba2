#include "UISystem.h"

#include <algorithm>
#include <string>

#include <imgui-SFML.h>
#include <imgui.h>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Keyboard.hpp>

void UISystem::OnUpdate(const float deltaTimeSeconds)
{
    ImGui::SFML::Update(_renderService.Window(), sf::seconds(deltaTimeSeconds));

    const bool togglePressedNow = sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::E);
    if (togglePressedNow && !_toggleKeyHeld)
    {
        _isVisible = !_isVisible;
    }
    _toggleKeyHeld = togglePressedNow;

    ImGui::SetNextWindowPos(ImVec2(12.0f, 12.0f), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(120.0f, 56.0f), ImGuiCond_Always);
    ImGui::Begin("UI Toggle", nullptr,
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoTitleBar);
    if (ImGui::Button(_isVisible ? "Hide UI" : "Show UI"))
    {
        _isVisible = !_isVisible;
    }
    ImGui::End();

    if (_isVisible)
    {
        ImGui::Begin("Game UI");

        for (const int settingsEntity : _spawnSettings)
        {
            auto& settings = _spawnSettingsComponents.Get(settingsEntity);

            int minMs = settings.MinIntervalMs;
            int maxMs = settings.MaxIntervalMs;
            ImGui::SliderInt("Asteroid spawn min (ms)", &minMs, 100, 5000);
            ImGui::SliderInt("Asteroid spawn max (ms)", &maxMs, 100, 5000);

            if (minMs > maxMs)
            {
                std::swap(minMs, maxMs);
            }

            settings.MinIntervalMs = minMs;
            settings.MaxIntervalMs = maxMs;
            break;
        }

        if (ImGui::Button("Spawn asteroid"))
        {
            const int eventEntity = world.CreateEntity();
            _spawnAsteroidEventComponents.Add(eventEntity, SpawnAsteroidEvent{});
        }

        ImGui::Separator();
        ImGui::Text("Entities:");

        const std::vector<int> alive = world.GetAliveEntities();
        for (const int entity : alive)
        {
            std::string line = "ID: " + std::to_string(entity);
            if (_transformComponents.Has(entity))
            {
                const auto& transform = _transformComponents.Get(entity);
                line += " | Pos: (" + std::to_string(transform.Position.x) + ", " + std::to_string(transform.Position.y) + ")";
            }
            else
            {
                line += " | Pos: n/a";
            }

            const EntityId packed = world.GetPackedEntity(entity);
            const auto& storageIds = packed.Components();
            line += " | Storages: [";
            for (size_t i = 0; i < storageIds.size(); ++i)
            {
                line += std::to_string(storageIds[i]);
                if (i + 1 < storageIds.size())
                {
                    line += ", ";
                }
            }
            line += "]";

            ImGui::TextUnformatted(line.c_str());
        }
        ImGui::End();
    }

    ImGui::SFML::Render(_renderService.Window());
    _renderService.EndFrame();
}
