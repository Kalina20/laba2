#include "CooldownBoostSystem.h"

#include <vector>

#include <SFML/System/Time.hpp>

void CooldownBoostSystem::OnInit()
{
    _clock.restart();
}

void CooldownBoostSystem::ApplyBoost(const int playerEntity, const float multiplier, const float durationMs)
{
    if (!_shooters.Has(playerEntity))
        return;

    auto& shooter = _shooters.Get(playerEntity);

    if (_cooldownBoosts.Has(playerEntity))
    {
        auto& boost = _cooldownBoosts.Get(playerEntity);
        boost.RemainingMs = durationMs;
        boost.Multiplier = multiplier;
        shooter.CooldownMs = boost.OriginalCooldownMs * multiplier;
        if (!shooter.CanShoot && shooter.TimeToShootMs > shooter.CooldownMs)
            shooter.TimeToShootMs = shooter.CooldownMs;
        return;
    }

    const float originalCooldownMs = shooter.CooldownMs;
    _cooldownBoosts.Add(playerEntity, CooldownBoostComponent(originalCooldownMs, durationMs, multiplier));
    shooter.CooldownMs = originalCooldownMs * multiplier;
    if (!shooter.CanShoot && shooter.TimeToShootMs > shooter.CooldownMs)
        shooter.TimeToShootMs = shooter.CooldownMs;
}

void CooldownBoostSystem::ClearBoost(const int playerEntity)
{
    if (!_cooldownBoosts.Has(playerEntity))
        return;

    const auto& boost = _cooldownBoosts.Get(playerEntity);
    if (_shooters.Has(playerEntity))
        _shooters.Get(playerEntity).CooldownMs = boost.OriginalCooldownMs;

    _cooldownBoosts.Remove(playerEntity);
}

void CooldownBoostSystem::OnUpdate()
{
    if (PauseState::IsPaused(_pauseStates))
    {
        _clock.restart();
        return;
    }

    const float deltaTimeMs = static_cast<float>(_clock.restart().asMilliseconds());

    std::vector<int> eventsToRemove;
    for (const int eventEntity : _boostEvents)
    {
        const auto& event = _cooldownBoostEvents.Get(eventEntity);
        ApplyBoost(event.Player, event.Multiplier, event.DurationMs);
        eventsToRemove.push_back(eventEntity);
    }

    for (const int eventEntity : eventsToRemove)
        world.RemoveEntity(eventEntity);

    std::vector<int> boostsToRemove;
    for (const int playerEntity : _activeBoosts)
    {
        auto& boost = _cooldownBoosts.Get(playerEntity);
        boost.RemainingMs -= deltaTimeMs;
        if (boost.RemainingMs <= 0.0f)
            boostsToRemove.push_back(playerEntity);
    }

    for (const int playerEntity : boostsToRemove)
        ClearBoost(playerEntity);
}
