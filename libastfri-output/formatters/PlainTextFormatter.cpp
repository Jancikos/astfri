#include <libastfri-output/formatters/PlainTextFormatter.hpp>

namespace libastfrioutput::formatters
{
PlainTextFormatter::PlainTextFormatter(libastfri::utils::IOutputWriter& writer
) :
    libastfri::utils::OutputFormatterAdapter(writer)
{
}

void PlainTextFormatter::printIndent()
{
    if (this->isInlinePrinting())
    {
        return;
    }

    for (int i = 0; i < this->getIndentLevel(); i++)
    {
        this->getWriter().write("    ");
    }
}

void PlainTextFormatter::printEndl(bool semicolon)
{
    if (semicolon)
    {
        this->getWriter().write(";");
    }

    if (this->isInlinePrinting())
    {
        this->getWriter().write(" ");
        return;
    }

    this->getWriter().write("\n");
}

} // namespace libastfrioutput::formatters