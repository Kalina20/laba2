#ifndef RANDOMSERVICE_H
#define RANDOMSERVICE_H

#include <random>

class RandomService
{
    std::mt19937 _rng;

public:
    RandomService() : _rng(std::random_device{}()) {}

    explicit RandomService(const unsigned int seed) : _rng(seed) {}

    int IntInRange(const int minValue, const int maxValue)
    {
        std::uniform_int_distribution<int> dist(minValue, maxValue);
        return dist(_rng);
    }

    float FloatInRange(const float minValue, const float maxValue)
    {
        std::uniform_real_distribution<float> dist(minValue, maxValue);
        return dist(_rng);
    }
};

#endif //RANDOMSERVICE_H
