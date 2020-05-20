#pragma once

#include "Operation.hpp"

namespace e_table {

    class CloseOperation : public Operation {
    public:
        CloseOperation(App& app);
        
        void execute(const std::vector<std::string>& args);
    };

}