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
        this->getWriter().print("    ");
    }
}

void PlainTextFormatter::printEndl(bool semicolon)
{
    if (semicolon)
    {
        this->getWriter().print(";");
    }

    if (this->isInlinePrinting())
    {
        this->getWriter().print(" ");
        return;
    }

    this->getWriter().print("\n");
}

} // namespace libastfrioutput::formatters