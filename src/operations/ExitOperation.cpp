#include <iostream>

#include "operations/ExitOperation.hpp"
#include "App.hpp"

namespace e_table {
    
    ExitOperation::ExitOperation(App& app)
        : Operation(app, "exit", "exists the program", 0, "") {}
    
    void ExitOperation::execute(std::vector<std::string>& args) {
        if(get_args_count() != args.size()) {
            throw OperationException("ERROR: Different count of arguments");
        }

        std::cout << "Exiting the program...\n";
    }

}