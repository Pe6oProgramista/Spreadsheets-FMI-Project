#include <fstream>
#include <string>

#include "operations/EditOperation.hpp"
#include "App.hpp"
#include "utility/utils.hpp"

namespace e_table {
    
    EditOperation::EditOperation(App& app)
        : Operation(app, "edit", "change value of cell <coordinates> to <value>", 2, "<coordinates> <value>") {}
    
    void EditOperation::execute(std::vector<std::string>& args) {
        if(get_args_count() != args.size()) {
            throw OperationException("ERROR: Different count of arguments");
        }

        std::string::const_iterator it = args[0].begin();
        if(*it == 'R' && utils::is_digit(*(it + 1))) {
            it++;
            int row = 0, col = 0;
            while(utils::is_digit(*it)) {
                row *= 10;
                row += *it - '0';
                it++;
            }
            
            if(*it == 'C' && utils::is_digit(*(it + 1))) {
                it++;
                while(utils::is_digit(*it)) {
                    col *= 10;
                    col += *it - '0';
                    it++;
                }

                app.get_table().get_row(row)->edit_cell(col, args[1]);
                return;
            }
        }

        throw OperationException("ERROR: Invalid coordinates");
    }

}