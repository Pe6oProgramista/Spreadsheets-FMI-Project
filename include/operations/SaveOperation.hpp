#pragma once

#include "Operation.hpp"

namespace e_table {

    class SaveOperation : public Operation {
    public:
        SaveOperation(App& app);
        
        void execute(const std::vector<std::string>& args);
    };

}