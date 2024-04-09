#include <libastfri-output/formatters/PlainTextFormatter.hpp>

namespace libastfrioutput::formatters
{
PlainTextFormatter::PlainTextFormatter(libastfri::utils::IOutputWriter& writer
) :
    libastfri::utils::OutputFormatterAdapter(writer),
    indentLevel(0),
    inlinePrinting(false)
{
}

void PlainTextFormatter::indentIncress()
{
    this->indentLevel++;
}

void PlainTextFormatter::indentDecress()
{
    this->indentLevel--;
}

void PlainTextFormatter::printIndent()
{
    if (this->inlinePrinting)
    {
        return;
    }

    for (int i = 0; i < this->indentLevel; i++)
    {
        this->getWriter().print("    ");
    }
}

void PlainTextFormatter::startInlinePrinting()
{
    this->inlinePrinting = true;
}

void PlainTextFormatter::endInlinePrinting()
{
    this->inlinePrinting = false;
}

void PlainTextFormatter::printEndl(bool semicolon)
{
    if (semicolon)
    {
        this->getWriter().print(";");
    }

    if (this->inlinePrinting)
    {
        this->getWriter().print(" ");
        return;
    }

    this->getWriter().print("\n");
}

} // namespace libastfrioutput::formatters