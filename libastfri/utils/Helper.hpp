#pragma once

#include <map>

namespace libastfri::utils
{

/**
 * Helper class for utility functions.
 */
class Helper
{
public:
    template<typename K, typename T, typename Emplacer>
    static T& getValueFromMap (
        K key,
        std::map<K, T>& map,
        Emplacer customEmplace
    );
};

template<typename K, typename T, typename Emplacer>
T& Helper::getValueFromMap(K key, std::map<K, T>& map, Emplacer customEmplace)
{
    auto it = map.find(key);
    if (it != map.end())
    {
        return it->second;
    }

    auto [newIt, success] = customEmplace(map, key);

    return newIt->second;
}
} // namespace libastfri::utils
