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

    void printIndent () override;
    void printEndl (bool semicolon = true) override;
};
} // namespace libastfrioutput::formatters