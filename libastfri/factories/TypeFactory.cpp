#include <libastfri/factories/TypeFactory.hpp>
#include <libastfri/utils/Helper.hpp>

namespace lsfu = libastfri::utils;

namespace libastfri::factories {
TypeFactory::TypeFactory() {}

TypeFactory &TypeFactory::getInstance() {
    static TypeFactory instance;

    return instance;
}

lsfs::IntType *TypeFactory::getIntType() { return &this->intType; }

lsfs::FloatType *TypeFactory::getFloatType() { return &this->floatType; }

lsfs::CharType *TypeFactory::getCharType() { return &this->charType; }

lsfs::BoolType *TypeFactory::getBoolType() { return &this->boolType; }

lsfs::VoidType *TypeFactory::getVoidType() { return &this->voidType; }

lsfs::UserType *TypeFactory::getUserType(std::string name) {
    return &lsfu::Helper::getValueFromMap(
        name, userTypes, [](auto &p_map, auto p_key) {
            return p_map.emplace(p_key, lsfs::UserType{{p_key}});
        });
}
} // namespace libastfri::factories
