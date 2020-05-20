#pragma once

#include "Operation.hpp"

namespace e_table {

    class OpenOperation : public Operation {
    public:
        OpenOperation(App& app);
        
        void execute(std::vector<std::string>& args);
    };

}