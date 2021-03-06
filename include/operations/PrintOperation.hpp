#pragma once

#include "Operation.hpp"

namespace e_table {

    class PrintOperation : public Operation {
    public:
        PrintOperation(App& app);
        
        void execute(const std::vector<std::string>& args);
    };

}