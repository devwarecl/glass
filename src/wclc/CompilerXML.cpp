//
//#include "CompilerXML.hpp"
//
//#include "HeaderTemplate.hpp"
//#include "SourceTemplate.hpp"
//
//#include <list>
//#include <boost/algorithm/string.hpp>
//#include <wcl/xml/Document.hpp>
//
//namespace wclc {
//
//    std::map<std::string, std::string> CompilerXML::compile (
//        const boost::filesystem::path &input_file, 
//        const boost::filesystem::path &output_path) {
//
//        namespace bfs = boost::filesystem;
//        wcl::xml::Document document = ::xmlReadFile(input_file.string().c_str(), nullptr, 0);
//        wcl::xml::NodeRef frameNode = document.GetRootNode();
//
//        Frame frame = ParseFrame(frameNode);
//
//        bfs::path output_file = output_path / input_file.filename();
//        bfs::path output_header = output_file;
//        bfs::path output_source = output_file;
//
//        output_header.replace_extension(output_header.extension().string() + ".hpp");
//        output_source.replace_extension(output_file.extension().string() + ".cpp");
//
//        std::map<std::string, std::string> outputFiles = {
//            {output_header.string(), GenerateFrameHeader(frame)},
//            {output_source.string(), GenerateFrameSource(frame)}
//        };
//
//        return outputFiles;
//    }
//}
