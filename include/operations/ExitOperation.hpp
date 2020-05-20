#pragma once

#include "Operation.hpp"

namespace e_table {

    class ExitOperation : public Operation {
    public:
        ExitOperation(App& app);
        
        void execute(const std::vector<std::string>& args);
    };

}