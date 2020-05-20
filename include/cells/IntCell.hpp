#pragma once

#include <string>

#include "Cell.hpp"

namespace e_table {
    
    class IntCell : public Cell {
    private:
        std::string valid(std::string val);
        
    public:
        IntCell(Row& row, const std::string& formula);

        std::string get_value() const;
    };

}