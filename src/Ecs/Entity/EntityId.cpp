#include "EntityId.h"

EntityId::EntityId(const int id, const int gen) : _gen(gen), Id(id)
{
}

void EntityId::AddComponent(const int component)
{
    for (const int existing : _components)
    {
        if (existing == component)
        {
            return;
        }
    }
    _components.push_back(component);
}

int EntityId::RemoveComponent(const int component)
{
    for (size_t i = 0; i < _components.size(); ++i)
    {
        if (_components[i] == component)
        {
            const int removed = _components[i];
            _components[i] = _components.back();
            _components.pop_back();
            return removed;
        }
    }

    return -1;
}

bool EntityId::IsRemoved() const
{
    return _gen < 0;
}

const std::vector<int>& EntityId::Components() const
{
    return _components;
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
    _components.clear();
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
    os << "EntityId{id=" << eId.Id << ", gen=" << eId.Gen() << ", removed=" << (eId.IsRemoved() ? "true" : "false") << "}";
    return os;
}
