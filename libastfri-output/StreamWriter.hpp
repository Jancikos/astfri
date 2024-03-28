#include <libastfri/utils/OutputWriter.hpp>

#include <ostream>

namespace libastfri::output
{
    class StreamWriter : public libastfri::utils::IOutputWriter
    {
        public:
        void indentIncress() override;
        void indentDecress() override;
        void printIndent() override;

        void startInlinePrinting() override;
        void endInlinePrinting() override;
        
        void printEndl(bool semicolon = true) override;
        void printOnNewLine(std::string const& str, bool endLine = true) override;
        void print(std::string const& str) override;

        StreamWriter(std::ostream& outStream);

    private:
        std::ostream& outStream;
        int indentLevel;
        bool inlinePrinting;
    };
}