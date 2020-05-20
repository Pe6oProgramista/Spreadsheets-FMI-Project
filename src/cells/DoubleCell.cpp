#include "cells/DoubleCell.hpp"

#include "utility/utils.hpp"

namespace e_table {

    DoubleCell::DoubleCell(Row& row, const std::string& formula)
        : Cell(row, "double", formula) {
            set_formula(formula);
    }

    std::string DoubleCell::valid(std::string val) {
        val = utils::trim(val);
        std::string::iterator it = val.begin();

        it = val.begin();
        if(*it == '+' || *it == '-') {
            it++;
        }

        while(utils::is_digit(*it) && it != val.end()) it++;

        if(it == val.end() || *it != '.') throw CellException("ERROR:.........");
        it++;

        while(utils::is_digit(*it) && it != val.end()) it++;
        
        if(it != val.end()) throw CellException("ERROR:.........");

        return val;
    }

    std::string DoubleCell::get_value() const {
        return formula;
    }

}