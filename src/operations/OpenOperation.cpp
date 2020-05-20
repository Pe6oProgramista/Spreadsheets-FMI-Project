#include <fstream>
#include <string>

#include "operations/OpenOperation.hpp"
#include "App.hpp"

namespace e_table {
    
    OpenOperation::OpenOperation(App& app)
        : Operation(app, "open", "opens <file>", 1, "<file>") {}
    
    void OpenOperation::execute(std::vector<std::string>& args) {
        if(get_args_count() != args.size()) {
            throw OperationException("ERROR: Different count of arguments");
        }

        std::ifstream in(args[0]);
        if (in.fail()) {
            throw OperationException("ERROR: File can't be opened. Filename: " + args[0]);
        }

        app.set_app_filename(args[0]);
        app.read(in);
    }

}