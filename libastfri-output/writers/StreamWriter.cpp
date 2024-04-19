#include <libastfri-output/writers/StreamWriter.hpp>

namespace libastfrioutput::writers
{
StreamWriter::StreamWriter(std::ostream& outStream) : outStream(outStream)
{
}

void StreamWriter::write(std::string const& str)
{
    this->outStream << str;
}

} // namespace libastfrioutput::writers