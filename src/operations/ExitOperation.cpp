#include <iostream>
#include <vector>

#include "operations/ExitOperation.hpp"
#include "App.hpp"

namespace e_table {
    
    ExitOperation::ExitOperation(App& app)
        : Operation(app, "exit", "exists the program", 0, "") {}
    
    void ExitOperation::execute(const std::vector<std::string>& args) {
        if(get_args_count() != args.size()) {
            throw OperationException("ERROR: Different count of arguments");
        }

        if(app.get_status()) {
            app.find_operation("close")->execute(std::vector<std::string>());
            app.set_status(false);
        }

        std::cout << "Exiting the program...\n";
    }

}