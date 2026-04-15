#ifndef COMPONENTSTORAGE_H
#define COMPONENTSTORAGE_H

#include <algorithm>
#include <stdexcept>
#include <vector>

#include "BaseComponentStorage.h"
#include "../World/IWorldInternal.h"

template <typename T>
class ComponentStorage final : public BaseComponentStorage {
    internal::IWorldInternal& _world;

    std::vector<T> _data;      // Для плотного хранения данных
    std::vector<int> _sparse;  // Для разреженного хранения индексов элементов (сущностей)
    std::vector<int> _dense;   // Для плотного хранения реально существующих элементов (сущностей, на которых есть компоненты)
    
    int _count = 0;            // Текущее число элементов

    int _id;

    void Resize(const int sparseSize, const int dataSize)
    {
        if (sparseSize > static_cast<int>(_sparse.size()))
        {
            _sparse.resize(sparseSize, -1);
        }

        if (dataSize > static_cast<int>(_data.size()))
        {
            _data.resize(dataSize);
            _dense.resize(dataSize, -1);
        }
    }

public:
    ComponentStorage(internal::IWorldInternal& w, const int id) : _world(w), _id(id)
    {
        Resize(64, 64);
    }

    bool Has(const int e) const override
    {
        if (e < 0 || e >= static_cast<int>(_sparse.size()))
        {
            return false;
        }

        const int denseIndex = _sparse[e];
        return denseIndex >= 0 && denseIndex < _count && _dense[denseIndex] == e;
    }

    T& Get(const int e)
    {
        if (!Has(e))
        {
            throw std::out_of_range("Component does not exist on entity");
        }
        return _data[_sparse[e]];
    }

    T& Add(const int e, const T& value)
    {
        if (e < 0)
        {
            throw std::out_of_range("Entity id must be non-negative");
        }

        if (Has(e))
        {
            _data[_sparse[e]] = value;
            return _data[_sparse[e]];
        }

        if (e >= static_cast<int>(_sparse.size()))
        {
            Resize(std::max(static_cast<int>(_sparse.size()) * 2, e + 1), static_cast<int>(_data.size()));
        }
        if (_count >= static_cast<int>(_data.size()))
        {
            const int newCap = std::max(1, static_cast<int>(_data.size()) * 2);
            Resize(static_cast<int>(_sparse.size()), newCap);
        }

        _sparse[e] = _count;
        _dense[_count] = e;
        _data[_count] = value;
        ++_count;

        _world.EntityComponentsChanged(e, _id, true);
        return _data[_sparse[e]];
    }

    void Remove(const int e) override
    {
        if (!Has(e))
        {
            return;
        }

        const int removeIdx = _sparse[e];
        const int lastIdx = _count - 1;
        const int lastEntity = _dense[lastIdx];

        _data[removeIdx] = _data[lastIdx];
        _dense[removeIdx] = lastEntity;
        _sparse[lastEntity] = removeIdx;

        _sparse[e] = -1;
        _dense[lastIdx] = -1;
        --_count;

        _world.EntityComponentsChanged(e, _id, false);
    }

    std::span<const T> All() const
    {
        return std::span<const T>(_data.data(), static_cast<size_t>(_count));
    }
    std::span<const int> Entities() const override
    {
        return std::span<const int>(_dense.data(), static_cast<size_t>(_count));
    }

    int Count() const override
    {
        return _count;
    }
    int Id() const override
    {
        return _id;
    }
};

#endif //COMPONENTSTORAGE_H
