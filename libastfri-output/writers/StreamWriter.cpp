#include <libastfri-output/writers/StreamWriter.hpp>

namespace libastfrioutput::writers
{
StreamWriter::StreamWriter(std::ostream& outStream) :
    outStream(outStream),
    indentLevel(0),
    inlinePrinting(false)
{
}

void StreamWriter::indentIncress()
{
    this->indentLevel++;
}

void StreamWriter::indentDecress()
{
    this->indentLevel--;
}

void StreamWriter::printIndent()
{
    if (this->inlinePrinting)
    {
        return;
    }
    
    for (int i = 0; i < this->indentLevel; i++)
    {
        this->outStream << "    ";
    }
}

void StreamWriter::startInlinePrinting()
{
    this->inlinePrinting = true;
}

void StreamWriter::endInlinePrinting()
{
    this->inlinePrinting = false;
}

void StreamWriter::printEndl(bool semicolon)
{
    if (semicolon)
    {
        this->outStream << ";";
    }

    if (this->inlinePrinting)
    {
        this->outStream << " ";
        return;
    }

    this->outStream << std::endl;
}

void StreamWriter::printOnNewLine(std::string const& str, bool endLine)
{
    this->printIndent();
    this->outStream << str;

    if (endLine)
    {
        this->printEndl();
    }
}

void StreamWriter::print(std::string const& str)
{
    this->outStream << str;
}

} // namespace libastfri::output