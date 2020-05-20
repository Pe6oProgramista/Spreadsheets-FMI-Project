#include <iostream>

#include "operations/SaveAsOperation.hpp"
#include "App.hpp"

namespace e_table {
    
    SaveAsOperation::SaveAsOperation(App& app)
        : Operation(app, "saveas", "saves the currently open file in <file>", 1, "<file>") {}
    
    void SaveAsOperation::execute(const std::vector<std::string>& args) {
        if(!app.get_status()) {
            throw OperationException("ERROR: There's no opened file. Please open a file and try again");
        }

        if(get_args_count() != args.size()) {
            throw OperationException("ERROR: Different count of arguments");
        }

        std::ofstream out(args[0]);
        if (out.fail()) {
            throw OperationException("ERROR: File can't be opened. Filename: " + args[0]);
        }
        
        app.write(out);
        std::cout << "Successfully saved " << args[0] << '\n';
    }

}