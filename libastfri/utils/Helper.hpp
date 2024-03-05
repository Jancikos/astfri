#pragma once

#include <functional>
#include <map>

namespace libastfri::utils {
    
    /**
     * Helper class for utility functions.
     */
    class Helper
    {
        public:
            template <typename K, typename T>
            static T& getValueFromMap(K key, std::map<K, T>& map, std::function<std::pair<typename std::map<K, T>::iterator, bool>> customEmplace);
    };   

    template <typename K, typename T>
    inline T& Helper::getValueFromMap(K key, std::map<K, T>& map, std::function<std::pair<typename std::map<K, T>::iterator, bool>> customEmplace)
    {
        auto it = map.find(key);
        if (it != map.end())
        {
            return it->second;
        }

        auto [newIt, success] = customEmplace(map, key);

        return newIt->second;
    }
}

