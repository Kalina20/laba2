#include "World.h"

void World::EntityComponentsChanged(const int e, const int storageId, const bool added)
{
    if (!IsEntityAlive(e))
    {
        return;
    }

    if (added)
    {
        _entities[e].AddComponent(storageId);
    }
    else
    {
        _entities[e].RemoveComponent(storageId);
    }
}

World::World()
{
    _entities.reserve(DefaultEntitiesCapacity);
    _freeEntities.reserve(DefaultEntitiesCapacity);
}

int World::CreateEntity()
{
    if (!_freeEntities.empty())
    {
        const int e = _freeEntities.back();
        _freeEntities.pop_back();
        _entities[e].Recycle();
        return e;
    }

    const int e = static_cast<int>(_entities.size());
    _entities.emplace_back(e, 0);
    return e;
}

void World::RemoveEntity(int e)
{
    if (!IsEntityAlive(e))
    {
        return;
    }

    for (const auto& storage : _componentStorages)
    {
        storage->Remove(e);
    }

    _entities[e].Remove();
    _freeEntities.push_back(e);
}

EntityId World::GetPackedEntity(const int e) const
{
    if (!IsEntityAlive(e))
    {
        return InvalidEntity;
    }
    return _entities[e];
}

bool World::UnpackEntity(const EntityId &eId, int &e) const
{
    const int unpacked = eId.Id;
    if (unpacked < 0 || unpacked >= static_cast<int>(_entities.size()))
    {
        return false;
    }

    if (!_entities[unpacked].Equals(eId) || _entities[unpacked].IsRemoved())
    {
        return false;
    }

    e = unpacked;
    return true;
}

std::vector<int> World::GetAliveEntities() const
{
    std::vector<int> aliveEntities;
    aliveEntities.reserve(_entities.size() - _freeEntities.size());

    for (int entity = 0; entity < static_cast<int>(_entities.size()); ++entity)
    {
        if (IsEntityAlive(entity))
        {
            aliveEntities.push_back(entity);
        }
    }

    return aliveEntities;
}

const std::vector<std::shared_ptr<BaseComponentStorage>>& World::GetStorages() const
{
    return _componentStorages;
}

bool World::IsEntityAlive(const int e) const
{
    return e >= 0 && e < static_cast<int>(_entities.size()) && !_entities[e].IsRemoved();
}
