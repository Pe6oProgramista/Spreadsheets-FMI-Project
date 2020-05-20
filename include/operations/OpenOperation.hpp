#pragma once

#include "Operation.hpp"

namespace e_table {

    class OpenOperation : public Operation {
    public:
        OpenOperation(App& app);
        
        void execute(const std::vector<std::string>& args);
    };

}