#pragma once

#include <map>
#include <string>

#include <libastfri/structures/Type.hpp>

using namespace libastfri::structures;

namespace libastfri::factories {
    class TypeFactory
    {
        public:
            static TypeFactory& getInstance();

        private:
            IntType intType;
            FloatType floatType;
            CharType charType;
            BoolType boolType;
            VoidType voidType;

            std::map<std::string, UserType> userTypes;

            TypeFactory ();
        public:
            IntType* getIntType () { return &intType; }
            FloatType* getFloatType () { return &floatType; }
            CharType* getCharType () { return &charType; }
            BoolType* getBoolType () { return &boolType; }
            VoidType* getVoidType () { return &voidType; }

            UserType* getUserType (std::string name);

            TypeFactory(TypeFactory const&) = delete;
            void operator=(TypeFactory const&) = delete;
    };

    inline TypeFactory::TypeFactory ()
    {
        // TODO - sem mozem davat len bezparametricke konstruktory? (do user type som musel priadat defaultny parameter, aby som to vedel skompilovat...)
        userTypes = std::map<std::string, UserType>();
    }

    inline TypeFactory& TypeFactory::getInstance()
    {
        static TypeFactory instance;

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

