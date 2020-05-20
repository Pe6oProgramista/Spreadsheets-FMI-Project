#pragma once

#include "Operation.hpp"

namespace e_table {

    class HelpOperation : public Operation {
    public:
        HelpOperation(App& app);
        
        void execute(const std::vector<std::string>& args);
    };

}