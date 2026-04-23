#ifndef WORLD_H
#define WORLD_H

#include <unordered_map>
#include <vector>
#include <memory>
#include <typeinfo>
#include <utility>

#include "IWorldInternal.h"
#include "../Entity/EntityId.h"
#include "../Components/ComponentStorage.hpp"

class World final : public internal::IWorldInternal {
    const int DefaultEntitiesCapacity = 64;

    std::vector<EntityId> _entities; //?
    std::vector<int> _freeEntities; //?

    std::unordered_map<size_t, std::shared_ptr<BaseComponentStorage>> _componentStoragesHash;
    std::vector<std::shared_ptr<BaseComponentStorage>> _componentStorages;

    int _storagesCount = 0;

public:
    World();

    int CreateEntity();
    void RemoveEntity(int e);

    EntityId GetPackedEntity(int e) const;
    bool UnpackEntity(const EntityId& eId, int& e) const;
    std::vector<int> GetAliveEntities() const;
    const std::vector<std::shared_ptr<BaseComponentStorage>>& GetStorages() const;

    bool IsEntityAlive(int e) const override;
    void EntityComponentsChanged(int e, int storageId, bool added) override;

    template <typename T>
    std::shared_ptr<ComponentStorage<T>> GetRawStorage()
    {
        const size_t hash = typeid(T).hash_code();
        const auto it = _componentStoragesHash.find(hash);
        if (it != _componentStoragesHash.end())
        {
            return std::static_pointer_cast<ComponentStorage<T>>(it->second);
        }

        auto storage = std::make_shared<ComponentStorage<T>>(*this, _storagesCount++);
        _componentStoragesHash[hash] = storage;
        _componentStorages.push_back(storage);
        return storage;
    }

    template <typename T>
    ComponentStorage<T>& GetStorage()
    {
        return *GetRawStorage<T>();
    }

    template <typename T, typename... TArgs>
    int CreateEvent(TArgs&&... args)
    {
        const int eventEntity = CreateEntity();
        GetStorage<T>().Add(eventEntity, T{std::forward<TArgs>(args)...});
        return eventEntity;
    }

    template <typename T>
    void ClearEvents()
    {
        auto& storage = GetStorage<T>();
        const auto entities = storage.Entities();
        std::vector<int> toRemove(entities.begin(), entities.end());

        for (const int entity : toRemove)
        {
            RemoveEntity(entity);
        }
    }
};

#endif //WORLD_H
