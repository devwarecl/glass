
#include "Compiler.hpp"
#include <wcl/xml/Document.hpp>

namespace wclc {

    namespace bfs = boost::filesystem;

    Compiler::Compiler(Parser *parser, Generator *generator) {
        this->parser = parser;
        this->generator = generator;
    }

    std::map<std::string, std::string> Compiler::compile(const boost::filesystem::path &input_file, const boost::filesystem::path &output_path) {
        Frame frame = this->parser->parse();

        bfs::path output_file = output_path / input_file.filename();
        bfs::path output_header = output_file;
        bfs::path output_source = output_file;

        output_header.replace_extension(output_header.extension().string() + ".hpp");
        output_source.replace_extension(output_file.extension().string() + ".cpp");

        std::map<std::string, std::string> outputFiles = {
            {output_header.string(), this->generator->generateHeader()},
            {output_source.string(), this->generator->generateSource()}
        };

        return outputFiles;
    }
}
