#include <iostream>

#include "operations/SaveOperation.hpp"
#include "App.hpp"

namespace e_table {
    
    SaveOperation::SaveOperation(App& app)
        : Operation(app, "save", "saves the currently open file", 0, "") {}
    
    void SaveOperation::execute(const std::vector<std::string>& args) {
        if(!app.get_status()) {
            throw OperationException("ERROR: There's no opened file. Please open a file and try again");
        }

        if(get_args_count() != args.size()) {
            throw OperationException("ERROR: Different count of arguments");
        }

        std::string file_name = app.get_app_filename();
        std::ofstream out(file_name);
        if (out.fail()) {
            throw OperationException("ERROR: File can't be opened. Filename: " + file_name);
        }

        app.write(out);
        std::cout << "Successfully saved " << file_name << '\n';
    }

}