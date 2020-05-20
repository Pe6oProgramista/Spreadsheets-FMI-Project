#pragma once

#include "Operation.hpp"

namespace e_table {

    class SaveAsOperation : public Operation {
    public:
        SaveAsOperation(App& app);
        
        void execute(const std::vector<std::string>& args);
    };

}