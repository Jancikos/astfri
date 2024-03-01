#pragma once

#include <map>

namespace libastfri::utils {
    class Helper
    {
        public:
            template <typename K, typename T>
            static T& getValueFromMap(K key, std::map<K, T> map);
    };   

    template <typename K, typename T>
    T& Helper::getValueFromMap(K key, std::map<K, T> map)
    {
        if (map.find(key) == map.end())
        {
            map[key] = T(key);
        }

        return map[key];
    }
}

