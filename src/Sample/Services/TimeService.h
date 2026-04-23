#ifndef TIMESERVICE_H
#define TIMESERVICE_H

#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

class TimeService
{
    sf::Clock _frameClock;
    sf::Clock _gameClock;

public:
    float RestartFrame()
    {
        return _frameClock.restart().asSeconds();
    }

    int ElapsedMilliseconds() const
    {
        return static_cast<int>(_gameClock.getElapsedTime().asMilliseconds());
    }

    void RestartGameClock()
    {
        _gameClock.restart();
    }
};

#endif //TIMESERVICE_H
