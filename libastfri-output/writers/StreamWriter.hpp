#include <libastfri/utils/OutputWriter.hpp>

#include <ostream>

namespace libastfrioutput::writers
{
class StreamWriter : public libastfri::utils::IOutputWriter
{
public:
    void write (std::string const& str) override;

    StreamWriter(std::ostream& outStream);

private:
    std::ostream& outStream;
};
} // namespace libastfrioutput::writers