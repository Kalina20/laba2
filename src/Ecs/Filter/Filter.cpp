#include "Filter.h"

#include <limits>

Filter::Filter(World &world,
    const std::vector<std::shared_ptr<BaseComponentStorage>> &componentStorages)
    : _world(world),
      _componentStorages(componentStorages),
      _minStorageIndex(std::numeric_limits<size_t>::max())
{
}

size_t Filter::FindMinComponentStorage() const
{
    if (_componentStorages.empty())
    {
        return std::numeric_limits<size_t>::max();
    }

    size_t minIndex = 0;
    int minCount = _componentStorages[0]->Count();

    for (size_t i = 1; i < _componentStorages.size(); ++i)
    {
        const int currentCount = _componentStorages[i]->Count();
        if (currentCount < minCount)
        {
            minCount = currentCount;
            minIndex = i;
        }
    }

    return minIndex;
}

bool Filter::Iterator::HasAllComponents() const
{
    if (!_world.IsEntityAlive(_currentEntity))
    {
        return false;
    }

    for (const auto& storage : _storages)
    {
        if (!storage->Has(_currentEntity))
        {
            return false;
        }
    }

    return true;
}

Filter::Iterator& Filter::Iterator::Increment()
{
    while (_current < _minStorageEntities.size())
    {
        _currentEntity = _minStorageEntities[_current];
        if (HasAllComponents())
        {
            return *this;
        }
        ++_current;
    }

    _currentEntity = -1;
    return *this;
}

Filter::Iterator::Iterator(
    World &world,
    const std::vector<std::shared_ptr<BaseComponentStorage>> &storages,
    const std::span<const int> &minStorageEntities,
    const size_t minStorageIndex,
    const size_t current)
    : _world(world),
      _minStorageEntities(minStorageEntities),
      _storages(storages),
      _minStorageIndex(minStorageIndex),
      _currentEntity(-1),
      _current(current)
{
    if (_current < _minStorageEntities.size())
    {
        Increment();
    }
}

Filter::Iterator::value_type Filter::Iterator::operator*() const
{
    return _currentEntity;
}

Filter::Iterator& Filter::Iterator::operator++()
{
    if (_current < _minStorageEntities.size())
    {
        ++_current;
    }
    return Increment();
}

bool Filter::Iterator::operator!=(const Iterator &other) const
{
    return !(*this == other);
}

bool Filter::Iterator::operator==(const Iterator &other) const
{
    return _current == other._current && &_world == &other._world;
}

Filter::Iterator Filter::begin()
{
    _minStorageIndex = FindMinComponentStorage();
    if (_minStorageIndex == std::numeric_limits<size_t>::max())
    {
        static const std::vector<int> empty;
        return Iterator(_world, _componentStorages, std::span<const int>(empty), _minStorageIndex, 0);
    }

    return Iterator(_world, _componentStorages, _componentStorages[_minStorageIndex]->Entities(), _minStorageIndex, 0);
}

Filter::Iterator Filter::begin() const
{
    return const_cast<Filter*>(this)->begin();
}

Filter::Iterator Filter::end()
{
    if (_minStorageIndex == std::numeric_limits<size_t>::max())
    {
        static const std::vector<int> empty;
        return Iterator(_world, _componentStorages, std::span<const int>(empty), _minStorageIndex, 0);
    }

    const auto minEntities = _componentStorages[_minStorageIndex]->Entities();
    return Iterator(_world, _componentStorages, minEntities, _minStorageIndex, minEntities.size());
}

Filter::Iterator Filter::end() const
{
    return const_cast<Filter*>(this)->end();
}
