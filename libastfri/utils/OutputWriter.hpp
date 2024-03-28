#pragma once

#include <string>
namespace libastfri::utils
{
class IOutputWriter
{
    public:
    virtual void indentIncress() = 0;
    virtual void indentDecress() = 0;
    virtual void printIndent() = 0;

    virtual void startInlinePrinting() = 0;
    virtual void endInlinePrinting() = 0;
    
    virtual void printEndl(bool semicolon = true) = 0;
    virtual void printOnNewLine(std::string const& str, bool endLine = true) = 0;
    virtual void print(std::string const& str) = 0;
};
} // namespace libastfri::utils