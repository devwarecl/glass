//
//#include <iostream>
//#include <list>
//#include <string>
//#include <map>
//#include <functional>
//#include <algorithm>
//#include <fstream>
//#include <boost/algorithm/string.hpp>
//#include <boost/filesystem.hpp>
//#include <boost/program_options.hpp>
//
//#include <wcl/xml/Node.hpp>
//#include <wcl/xml/Document.hpp>
//
//#include "Compiler.hpp"
//#include "ParserXML.hpp"
//#include "Generator.hpp"
//
//namespace bpo = boost::program_options;
//namespace bfs = boost::filesystem;
//
//int main(int argc, char **argv) {
//
//    try {
//        using namespace wclc;
//
//        const char WCLC_CMD_HELP[]            = "help";
//        const char WCLC_CMD_INPUT[]            = "input";
//        const char WCLC_CMD_OUTPUTPATH[]    = "output-path";
//
//        // Parse the command line
//        bpo::options_description desc("Allowed options");
//        desc.add_options()
//            (WCLC_CMD_HELP, "Produces this help message")
//            (WCLC_CMD_INPUT, bpo::value<bfs::path>()->required(), "XML User Interface Definition File")
//            (WCLC_CMD_OUTPUTPATH, bpo::value<bfs::path>(), "Where to put the generated C++ source files from the XML User Interface Definition File." );
//
//        try {
//            bpo::positional_options_description desc_positional;
//            desc_positional.add("input", -1);
//
//            bpo::command_line_parser parser(argc, argv);
//            bpo::basic_parsed_options<char> options = parser.options(desc).positional(desc_positional).run();
//
//            bpo::variables_map vm;
//            bpo::store(options, vm);
//            bpo::notify(vm);
//
//            // Handle help display command
//            if (vm.count(WCLC_CMD_HELP)) {
//                std::cout << desc << std::endl;
//                return 0;
//            }
//
//            // Validate the input file
//            bfs::path input_file = vm[WCLC_CMD_INPUT].as<bfs::path>();
//            if (!bfs::exists(input_file) || bfs::is_directory(input_file)) {
//                std::string msg = "The file "
//                    + ("'" + input_file.string() + "'")
//                    + ("isn't valid");
//
//                throw std::runtime_error(msg);
//            }
//
//            // Validate the output path
//            bfs::path output_path = bfs::current_path();
//
//            if (vm.count(WCLC_CMD_OUTPUTPATH)) {
//                output_path = vm[WCLC_CMD_OUTPUTPATH].as<bfs::path>();
//
//                if (!bfs::is_directory(output_path) || !bfs::exists(output_path)) {
//                    std::string msg = "The output path "
//                        + ("'" + output_path.string() + "'")
//                        + ("isn't valid");
//
//                    throw std::runtime_error(msg);
//                }
//            }
//
//            // Generate the files.
//            wcl::xml::Document document(::xmlReadFile(input_file.string().c_str(), nullptr, 0));
//            wclc::ParserXML parserXml(document.GetRootNode());
//            wclc::Generator generator;
//
//            Compiler compiler (&parserXml, &generator);
//
//            const auto outputFiles = compiler.compile(input_file, output_path);
//
//            for (const auto &output : outputFiles) {
//                std::ofstream fs;
//
//                fs.open(output.first.c_str());
//                fs << output.second;
//            }
//
//            return 0;
//
//        } catch (const bpo::error &exp) {
//            std::cout << "Error: " << exp.what() << std::endl;
//            std::cout << desc << std::endl;
//            return 1;
//
//        } catch (const std::runtime_error &exp) {
//            std::cout << "Runtime Error: " << exp.what() << std::endl;
//            return 2;
//        }
//    } catch (const std::exception &exp) {
//        std::cout << "The following error occured:" << std::endl;
//        std::cout << exp.what() << std::endl;
//
//        return 1;
//    }
//}

int main() {
    return 0;
}
