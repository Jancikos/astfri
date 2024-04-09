#pragma once

#include <string>
namespace libastfri::utils
{
class IOutputWriter
{
    public:
    virtual void print(std::string const& str) = 0;
};
} // namespace libastfri::utils