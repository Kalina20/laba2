#ifndef FILTERBUILDER_H
#define FILTERBUILDER_H

#include "Filter.h"
#include "../World/World.h"

class FilterBuilder
{
    World& _world;
    std::vector<std::shared_ptr<BaseComponentStorage>> _componentStorages;

public:
    explicit FilterBuilder(World& world) : _world(world) {}

    template <typename T>
    FilterBuilder& With()
    {
        _componentStorages.push_back(_world.GetRawStorage<T>());
        return *this;
    }

    Filter Build() const;
};

#endif //FILTERBUILDER_H
