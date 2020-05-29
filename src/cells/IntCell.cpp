#include "cells/IntCell.hpp"

#include "utility/utils.hpp"

namespace e_table {

        IntCell::IntCell(Row& row, int indx, const std::string& formula)
            : Cell(row, indx, "int", formula) {
                set_formula(formula);
        }

        std::string IntCell::valid(std::string val) {
            val = utils::trim(val);
            std::string::iterator it = val.begin();

            if(*it == '+' || *it == '-') {
                it++;
            }

            while(utils::is_digit(*it) && it != val.end()) it++;

            if(it != val.end()) throw CellException("ERROR:.........");

            return val;
        }

        std::string IntCell::get_value() const {
            return formula;
        }

}