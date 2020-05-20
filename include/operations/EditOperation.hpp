#pragma once

#include "Operation.hpp"

namespace e_table {

    class EditOperation : public Operation {
    public:
        EditOperation(App& app);
        
        void execute(std::vector<std::string>& args);
    };

}