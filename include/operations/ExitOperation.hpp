#pragma once

#include "Operation.hpp"

namespace e_table {

    class ExitOperation : public Operation {
    public:
        ExitOperation(App& app);
        
        void execute(std::vector<std::string>& args);
    };

}