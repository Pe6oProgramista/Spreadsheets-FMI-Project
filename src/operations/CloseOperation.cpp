#include <iostream>

#include "operations/CloseOperation.hpp"
#include "App.hpp"

namespace e_table {
    
    CloseOperation::CloseOperation(App& app)
        : Operation(app, "close", "closes currently opened file", 0, "") {}
    
    void CloseOperation::execute(const std::vector<std::string>& args) {
        if(!app.get_status()) {
            throw OperationException("ERROR: There's no opened file. Please open a file and try again");
        }
        
        if(get_args_count() != args.size()) {
            throw OperationException("ERROR: Different count of arguments");
        }


        app.get_table() = e_table::Table();
        app.set_app_filename("");
        app.set_status(false);

        std::cout << "Successfully closed " << app.get_app_filename() << '\n';
    }

}