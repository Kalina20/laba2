#ifndef CONFIGSERVICE_H
#define CONFIGSERVICE_H

#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>

#include "GameConfig.h"

class ConfigService
{
    GameConfig _config;

    static std::string Trim(const std::string& value)
    {
        const size_t first = value.find_first_not_of(" \t\r\n");
        if (first == std::string::npos)
        {
            return "";
        }

        const size_t last = value.find_last_not_of(" \t\r\n");
        return value.substr(first, last - first + 1);
    }

    static float ParseFloat(const std::unordered_map<std::string, std::string>& values,
        const std::string& key, const float fallback)
    {
        const auto it = values.find(key);
        if (it == values.end())
        {
            return fallback;
        }

        try
        {
            return std::stof(it->second);
        }
        catch (...)
        {
            return fallback;
        }
    }

    static int ParseInt(const std::unordered_map<std::string, std::string>& values,
        const std::string& key, const int fallback)
    {
        const auto it = values.find(key);
        if (it == values.end())
        {
            return fallback;
        }

        try
        {
            return std::stoi(it->second);
        }
        catch (...)
        {
            return fallback;
        }
    }

public:
    bool Load(const std::string& path)
    {
        std::ifstream input(path);
        if (!input.is_open())
        {
            return false;
        }

        std::unordered_map<std::string, std::string> values;
        std::string line;
        while (std::getline(input, line))
        {
            const std::string trimmed = Trim(line);
            if (trimmed.empty() || trimmed[0] == '#')
            {
                continue;
            }

            const size_t sep = trimmed.find('=');
            if (sep == std::string::npos)
            {
                continue;
            }

            const std::string key = Trim(trimmed.substr(0, sep));
            const std::string value = Trim(trimmed.substr(sep + 1));
            if (!key.empty())
            {
                values[key] = value;
            }
        }

        _config.PlayerSpeed = ParseFloat(values, "player_speed", _config.PlayerSpeed);
        _config.ShootCooldownMs = ParseInt(values, "shoot_cooldown_ms", _config.ShootCooldownMs);
        _config.BulletSpeed = ParseFloat(values, "bullet_speed", _config.BulletSpeed);

        _config.AsteroidSpawnMinMs = ParseInt(values, "asteroid_spawn_min_ms", _config.AsteroidSpawnMinMs);
        _config.AsteroidSpawnMaxMs = ParseInt(values, "asteroid_spawn_max_ms", _config.AsteroidSpawnMaxMs);

        _config.AsteroidSpeedMin = ParseFloat(values, "asteroid_speed_min", _config.AsteroidSpeedMin);
        _config.AsteroidSpeedMax = ParseFloat(values, "asteroid_speed_max", _config.AsteroidSpeedMax);
        _config.AsteroidRadiusMin = ParseFloat(values, "asteroid_radius_min", _config.AsteroidRadiusMin);
        _config.AsteroidRadiusMax = ParseFloat(values, "asteroid_radius_max", _config.AsteroidRadiusMax);
        _config.AsteroidDirXMin = ParseFloat(values, "asteroid_dir_x_min", _config.AsteroidDirXMin);
        _config.AsteroidDirXMax = ParseFloat(values, "asteroid_dir_x_max", _config.AsteroidDirXMax);
        _config.AsteroidDirYMin = ParseFloat(values, "asteroid_dir_y_min", _config.AsteroidDirYMin);
        _config.AsteroidDirYMax = ParseFloat(values, "asteroid_dir_y_max", _config.AsteroidDirYMax);

        _config.AsteroidPointsMin = ParseInt(values, "asteroid_points_min", _config.AsteroidPointsMin);
        _config.AsteroidPointsMax = ParseInt(values, "asteroid_points_max", _config.AsteroidPointsMax);

        const auto fontIt = values.find("ui_font_path");
        if (fontIt != values.end())
        {
            _config.UiFontPath = fontIt->second;
        }

        if (_config.AsteroidSpawnMinMs > _config.AsteroidSpawnMaxMs)
        {
            std::swap(_config.AsteroidSpawnMinMs, _config.AsteroidSpawnMaxMs);
        }

        if (_config.AsteroidSpeedMin > _config.AsteroidSpeedMax)
        {
            std::swap(_config.AsteroidSpeedMin, _config.AsteroidSpeedMax);
        }

        if (_config.AsteroidRadiusMin > _config.AsteroidRadiusMax)
        {
            std::swap(_config.AsteroidRadiusMin, _config.AsteroidRadiusMax);
        }

        if (_config.AsteroidPointsMin > _config.AsteroidPointsMax)
        {
            std::swap(_config.AsteroidPointsMin, _config.AsteroidPointsMax);
        }

        return true;
    }

    const GameConfig& Get() const
    {
        return _config;
    }
};

#endif //CONFIGSERVICE_H
