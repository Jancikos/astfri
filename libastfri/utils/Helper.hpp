#pragma once

#include <map>

namespace libastfri::utils {
    
    /**
     * Helper class for utility functions.
     */
    class Helper
    {
        public:
            /**
             * Retrieves the value associated with the given key from the map.
             * If the key does not exist in the map, a new value is created and added to the map. 
             * @param key The key to search for in the map. Also used as a parameter for the constructor of the value.
             * @param map The map to retrieve the value from.
             * @return A reference to the value associated with the key in the map.
             */
            template <typename K, typename T>
            static T& getValueFromMap(K key, std::map<K, T>& map);
    };   

    template <typename K, typename T>
    T& Helper::getValueFromMap(K key, std::map<K, T>& map)
    {
        auto it = map.find(key);
        if (it != map.end())
        {
            return it->second;
        }

        auto [newIt, success] = map.emplace(std::move(key), T(key));

        return newIt->second;
    }
}

