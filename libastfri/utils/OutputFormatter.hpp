#pragma once

#include <libastfri/utils/OutputWriter.hpp>

#include <clang/Basic/ExpressionTraits.h>
#include <string>

namespace libastfri::utils
{
enum class OutputToken
{
    Keyword,
    Identifier,
    Literal,
    IntLiteral,
    FloatLiteral,
    CharLiteral,
    StringLiteral,
    BoolLiteral,
    Operator,
    Separator,
    Comment,
    Error,
    None
};

class IOutputFormatter
{
public:
    virtual IOutputWriter& getWriter ()                            = 0;

    virtual void print (std::string const& str)                    = 0;
    virtual void print (std::string const& str, OutputToken token) = 0;
    virtual void printIndented (
        std::string const& str,
        OutputToken token = OutputToken::None
    )                                                        = 0;

    virtual void indentIncress ()                            = 0;
    virtual void indentDecress ()                            = 0;
    virtual void printIndent ()                              = 0;

    virtual void startInlinePrinting ()                      = 0;
    virtual void endInlinePrinting ()                        = 0;

    virtual void printEndl (bool semicolon = true)           = 0;

    virtual void printKeyword (std::string const& str)       = 0;
    virtual void printIdentifier (std::string const& str)    = 0;
    virtual void printLiteral (std::string const& str)       = 0;
    virtual void printIntLiteral (std::string const& str)    = 0;
    virtual void printFloatLiteral (std::string const& str)  = 0;
    virtual void printCharLiteral (std::string const& str)   = 0;
    virtual void printStringLiteral (std::string const& str) = 0;
    virtual void printBoolLiteral (std::string const& str)   = 0;
    virtual void printOperator (std::string const& str)      = 0;
    virtual void printSeparator (std::string const& str)     = 0;
    virtual void printComment (std::string const& str)       = 0;
    virtual void printError (std::string const& str)         = 0;
    virtual void printNone (std::string const& str)          = 0;
};

class OutputFormatterAdapter : public IOutputFormatter
{
public:
    IOutputWriter& writer;

    OutputFormatterAdapter(IOutputWriter& writer) : writer(writer)
    {
    }

    virtual IOutputWriter& getWriter () override
    {
        return writer;
    }

    virtual void print (std::string const& str) override
    {
        writer.print(str);
    }

    virtual void print (std::string const& str, OutputToken token) override
    {
        switch (token)
        {
        case OutputToken::Keyword:
            printKeyword(str);
            break;
        case OutputToken::Identifier:
            printIdentifier(str);
            break;
        case OutputToken::Literal:
            printLiteral(str);
            break;
        case OutputToken::IntLiteral:
            printIntLiteral(str);
            break;
        case OutputToken::FloatLiteral:
            printFloatLiteral(str);
            break;
        case OutputToken::CharLiteral:
            printCharLiteral(str);
            break;
        case OutputToken::StringLiteral:
            printStringLiteral(str);
            break;
        case OutputToken::BoolLiteral:
            printBoolLiteral(str);
            break;
        case OutputToken::Operator:
            printOperator(str);
            break;
        case OutputToken::Separator:
            printSeparator(str);
            break;
        case OutputToken::Comment:
            printComment(str);
            break;
        case OutputToken::Error:
            printError(str);
            break;
        case OutputToken::None:
        default:
            printNone(str);
            break;
        }
    }

    virtual void printIndented (
        std::string const& str,
        OutputToken token = OutputToken::None
    ) override
    {
        printIndent();
        print(str, token);
    }

    virtual void printKeyword (std::string const& str) override
    {
        print(str);
    }

    virtual void printIdentifier (std::string const& str) override
    {
        print(str);
    }

    virtual void printLiteral (std::string const& str) override
    {
        print(str);
    }

    virtual void printIntLiteral (std::string const& str) override
    {
        print(str);
    }

    virtual void printFloatLiteral (std::string const& str) override
    {
        print(str);
    }

    virtual void printCharLiteral (std::string const& str) override
    {
        print(str);
    }

    virtual void printStringLiteral (std::string const& str) override
    {
        print(str);
    }

    virtual void printBoolLiteral (std::string const& str) override
    {
        print(str);
    }

    virtual void printOperator (std::string const& str) override
    {
        print(str);
    }

    virtual void printSeparator (std::string const& str) override
    {
        print(str);
    }

    virtual void printComment (std::string const& str) override
    {
        print(str);
    }

    virtual void printError (std::string const& str) override
    {
        print(str);
    }

    virtual void printNone (std::string const& str) override
    {
        print(str);
    }
};
} // namespace libastfri::utils