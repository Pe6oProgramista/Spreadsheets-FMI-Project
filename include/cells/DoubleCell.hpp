#pragma once

#include <string>

#include "Cell.hpp"

namespace e_table {
    
    class DoubleCell : public Cell {
    private:
        std::string valid(std::string val);

    public:
        DoubleCell(Row& row, int indx, const std::string& formula);

        std::string get_value() const;
    };

}