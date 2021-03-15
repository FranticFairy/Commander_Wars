#pragma once
#include "3rd_party/oxygine-framework/oxygine/oxygine-include.h"
#include "3rd_party/oxygine-framework/oxygine/core/intrusive_ptr.h"
#include "3rd_party/oxygine-framework/oxygine/core/ref_counter.h"
#include <unordered_map>
#include <qmutex.h>

namespace oxygine
{
    inline void hash_combine(std::size_t& seed) { }

    template <typename T, typename... Rest>
    inline void hash_combine(std::size_t& seed, const T& v, Rest... rest)
    {
        std::hash<T> hasher;
        seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        hash_combine(seed, rest...);
    }

    class Material;
    typedef intrusive_ptr<Material> spMaterialX;

    class MaterialCache
    {
    public:
        MaterialCache();

        template<class T>
        intrusive_ptr<T> cache(const T& other)
        {
            return (T*)clone_(other);
        }

        void clear();
        void removeUnused();
        size_t getTotalMaterials() const { return _materials.size(); }

    protected:
        typedef std::unordered_multimap<size_t, spMaterialX> materials;
        materials _materials;

        QMutex _lock;
        int _addCounter;

        Material* clone_(const Material& other);
        void removeUnusedNoLock();
    };

    MaterialCache& mc();
}
