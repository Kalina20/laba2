#include "EntityId.h"

EntityId::EntityId(const int id, const int gen) : _gen(gen), Id(id)
{
}

void EntityId::AddComponent(const int component)
{
    if (component < 0)
    {
        return;
    }

    if (component >= static_cast<int>(_componentMask.size()))
    {
        _componentMask.resize(component + 1, false);
    }
    _componentMask[component] = true;
}

int EntityId::RemoveComponent(const int component)
{
    if (component < 0 || component >= static_cast<int>(_componentMask.size()))
    {
        return -1;
    }

    if (_componentMask[component])
    {
        _componentMask[component] = false;
        return component;
    }

    return -1;
}

bool EntityId::HasComponent(const int component) const
{
    return component >= 0 && component < static_cast<int>(_componentMask.size()) && _componentMask[component];
}

bool EntityId::IsRemoved() const
{
    return _gen < 0;
}

const std::vector<bool>& EntityId::Components() const
{
    return _componentMask;
}

int EntityId::Gen() const
{
    return _gen;
}

void EntityId::Remove()
{
    if (!IsRemoved())
    {
        _gen = -_gen - 1;
    }
    _componentMask.clear();
}

void EntityId::Recycle()
{
    if (IsRemoved())
    {
        _gen = -_gen;
    }
}

bool EntityId::Equals(const EntityId &other) const
{
    return Id == other.Id && _gen == other._gen;
}

bool EntityId::operator==(const EntityId &other) const
{
    return this->Equals(other);
}

bool EntityId::operator!=(const EntityId &other) const
{
    return !this->Equals(other);
}

std::ostream& operator<<(std::ostream &os, const EntityId &eId)
{
    int activeComponents = 0;
    for (const bool hasComponent : eId.Components())
    {
        activeComponents += hasComponent ? 1 : 0;
    }

    os << "EntityId{id=" << eId.Id
       << ", gen=" << eId.Gen()
       << ", removed=" << (eId.IsRemoved() ? "true" : "false")
       << ", components=" << activeComponents << "}";
    return os;
}
