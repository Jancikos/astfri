#pragma once

#include <map>
#include <string>

#include <libastfri/structures/Type.hpp>

using namespace libastfri::structures;

namespace libastfri::factories {

    // TODO - refaktornut to cele na staticke metody ???

    class TypeFactory
    {
        private:
            static TypeFactory* instance;

            IntType intType;
            FloatType floatType;
            CharType charType;
            BoolType boolType;
            VoidType voidType;

            std::map<std::string, UserType> userTypes;

            TypeFactory ();

        public:
            static TypeFactory* getInstance();

            IntType* getIntType () { return &intType; }
            FloatType* getFloatType () { return &floatType; }
            CharType* getCharType () { return &charType; }
            BoolType* getBoolType () { return &boolType; }
            VoidType* getVoidType () { return &voidType; }

            UserType* getUserType (std::string name);
    };

    inline TypeFactory::TypeFactory ()
    {
        userTypes = std::map<std::string, UserType>();
    }

    inline TypeFactory* TypeFactory::getInstance()
    {
        if (instance == nullptr)
        {
            instance = new TypeFactory();
        }

        return instance;
    }

    inline UserType* TypeFactory::getUserType (std::string name)
    {
        if (userTypes.find(name) == userTypes.end())
        {
            userTypes[name] = UserType(name);
        }

        return &userTypes[name];
    }
}

