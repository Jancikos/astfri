#pragma once

#include <map>
#include <string>

namespace libastfri::structures
{
enum class BinaryOperators;
enum class UnaryOperators;
} // namespace libastfri::structures

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

    static std::string convertBinaryOperator (structures::BinaryOperators op);
    static std::string convertUnaryOperator (structures::UnaryOperators op);
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
