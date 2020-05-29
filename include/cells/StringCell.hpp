#pragma once

#include <string>

#include "Cell.hpp"

namespace e_table {

    class StringCell : public Cell {
    private:
        std::string valid(std::string val);

    public:
        StringCell(Row& row, int indx, const std::string& formula);

        std::string get_value() const;
    };

}