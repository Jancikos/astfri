#pragma once

#include <libastfri/utils/OutputFormatter.hpp>
#include <libastfri/utils/OutputWriter.hpp>

namespace libastfrioutput::formatters
{
namespace lsfu = libastfri::utils;

class PlainTextFormatter : public lsfu::OutputFormatterAdapter
{
public:
    PlainTextFormatter(lsfu::IOutputWriter& writer);

    void indentIncress () override;
    void indentDecress () override;
    void printIndent () override;

    void startInlinePrinting () override;
    void endInlinePrinting () override;

    void printEndl (bool semicolon = true) override;
private:
    int indentLevel;
    bool inlinePrinting;
};
} // namespace libastfrioutput::formatters