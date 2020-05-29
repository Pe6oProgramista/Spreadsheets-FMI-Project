#include <iostream>
#include <iomanip>

#include "operations/HelpOperation.hpp"
#include "App.hpp"

namespace e_table {
    
    HelpOperation::HelpOperation(App& app)
        : Operation(app, "help", "prints this information", 0, "") {}
    
    void HelpOperation::execute(const std::vector<std::string>& args) {
        if(get_args_count() != args.size()) {
            throw OperationException("ERROR: Different count of arguments");
        }

        std::cout << "The following commands are supported:\n";

        std::size_t name_size = 0;
        std::size_t args_names_size = 0;
        std::size_t description_size = 0;

        std::size_t ops_cnt = app.ops_cnt();
        for(std::size_t i = 0; i < ops_cnt; i++) {
            utils::SmartPtr<const Operation> op = app.get_operation(i);
            if(name_size < op->get_name().size()) {
                name_size = op->get_name().size();
            }
            if(args_names_size < op->get_args_names().size()) {
                args_names_size = op->get_args_names().size();
            }
            if(description_size < op->get_description().size()) {
                description_size = op->get_description().size();
            }
        }

        std::cout << "  "
            << std::left
            << std::setw(name_size)
            << "name"
            << "  "
            << std::setw(args_names_size)
            << "args"
            << "  "
            << std::setw(description_size)
            << "description"
            << "\n\n";

        for(std::size_t i = 0; i < ops_cnt; i++) {
            utils::SmartPtr<const Operation> op = app.get_operation(i);
            std::cout << "  "
                << std::left
                << std::setw(name_size)
                << op->get_name()
                << "  "
                << std::setw(args_names_size)
                << op->get_args_names()
                << "  "
                << std::setw(description_size)
                << op->get_description()
                << '\n';
        }
    }

}