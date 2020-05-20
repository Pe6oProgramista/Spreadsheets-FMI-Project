#include <fstream>
#include <string>
#include <iostream>

#include "operations/PrintOperation.hpp"
#include "App.hpp"

namespace e_table {
    
    PrintOperation::PrintOperation(App& app)
        : Operation(app, "print", "prints content of a table", 0, "") {}
    
    void PrintOperation::execute(std::vector<std::string>& args) {
        if(get_args_count() != args.size()) {
            throw OperationException("ERROR: Different count of arguments");
        }

        app.get_const_table().print(std::cout);
    }

}