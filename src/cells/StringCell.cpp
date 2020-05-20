#include "cells/StringCell.hpp"

#include "utility/utils.hpp"

namespace e_table {

        StringCell::StringCell(Row& row, const std::string& formula)
            : Cell(row, "string", formula) {
                set_formula(formula);
        }

        std::string StringCell::valid(std::string val) {
            val = utils::trim(val);
            std::string::iterator it = val.begin();

            if(*it != '\"') throw CellException("ERROR:.........");
            it++;

            while(*it != '\"' && it != val.end()) {
                if(*it == '\\' && *(it + 1) == '\"') it++; 
                it++;
            }

            if(it == val.end() || it + 1 != val.end()) throw CellException("ERROR:.........");

            return val;
        }

        std::string StringCell::get_value() const {
            std::string result;
            for(std::string::const_iterator it = formula.begin() + 1; it != formula.end() - 1; it++) {
                if(*it == '\\') it++;
                result.push_back(*it);
            }
            return result;
        }

}