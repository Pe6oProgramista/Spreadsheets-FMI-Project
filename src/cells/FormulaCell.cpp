#include <list>
#include <string>
#include <stdlib.h>
#include <cmath>
#include <sstream>
#include <vector>

#include "cells/FormulaCell.hpp"

#include "Row.hpp"
#include "Table.hpp"
#include "utility/utils.hpp"

namespace e_table {
        FormulaCell::FormulaCell(Row& row, int indx, const std::string& formula)
            : Cell(row, indx, "formula", formula) {
                set_formula(formula);
        }

        std::string FormulaCell::valid(std::string val) {
            val = utils::trim(val);
            std::vector<std::string> values;
            std::vector<char> operations;

            bool last_is_op = true; // ако последния елемент е бил операция

            std::string value;
            for(std::string::const_iterator it = val.begin(); it != val.end(); it++) {
                while(*it == ' ') it++;

                if(*it == '-' ||
                    *it == '+' ||
                    *it == '*' ||
                    *it == '/' ||
                    *it == '^') {
                        if(last_is_op) throw FormulaCellException("ERROR: Can't execute 2 operations at once");
                        operations.push_back(*it);
                        last_is_op = true;   
                } else {
                    if(last_is_op == false) throw FormulaCellException("ERROR: Missing operation");
                    last_is_op = false;

                    if(utils::is_digit(*it)) {
                        while(utils::is_digit(*it)) {
                            value.push_back(*it);
                            it++;
                        }
                        if(*it == '.') {
                            do {
                                value.push_back(*it);
                                it++;
                            } while(utils::is_digit(*it));
                        }
                    } else if(*it == 'R' && utils::is_digit(*(it + 1))) {
                        value.push_back(*(it++));
                        
                        int row = 0, col = 0;
                        while(utils::is_digit(*it)) {
                            row *= 10;
                            row += *it - '0';
                            value.push_back(*(it++));
                        }
                        
                        if(*it == 'C' && utils::is_digit(*(it + 1))) {
                            value.push_back(*(it++));

                            while(utils::is_digit(*it)) {
                                col *= 10;
                                col += *it - '0';
                                value.push_back(*(it++));
                            }
                        }

                        // checks for reference to previous cells
                        if(row - 1 == this->row.get_indx() && col - 1 == indx) throw FormulaCellException("ERROR: You try to make circular reference");
                        // if(row - 1 <= this->row.get_indx() && col - 1 <= indx) {
                        if(this->row.get_table().rows_cnt() > (std::size_t)row - 1 &&
                            this->row.get_table().get_row(row-1)->cells_cnt() > (std::size_t)col - 1) {
                            
                            utils::SmartPtr<const Cell> cell = this->row.get_table().get_row(row - 1)->get_cell(col - 1);
                            utils::SmartPtr<const FormulaCell> ref_cell = utils::smart_ptr_cast<const FormulaCell>(cell);
                            if (!ref_cell.is_null()) {
                                for(const std::string& v : ref_cell->values) {
                                    std::string::const_iterator ref_it = v.begin();
                                    if(*ref_it == 'R') {
                                        int ref_row = 0, ref_col = 0;
                                        while(utils::is_digit(*(++ref_it))) {
                                            ref_row *= 10;
                                            ref_row += *ref_it - '0';
                                        }

                                        while(utils::is_digit(*(++ref_it))) {
                                            ref_col *= 10;
                                            ref_col += *ref_it - '0';
                                        }

                                        if( ref_row - 1 == this->row.get_indx() &&
                                            ref_col - 1 == indx) {
                                                throw FormulaCellException("ERROR: You try to make circular reference");
                                        }
                                    }
                                }
                            }
                        }
                    } else {
                        throw CellException("ERROR: Invalid formula cell input");
                    }

                    values.push_back(value);
                    value.clear();
                    it--;
                }
            }

            this->values = values;
            this->operations = operations;

            return val;
        }

        double FormulaCell::parse(const std::string& val) const {
            double result = 0;
            double floating_point = 10;
            
            std::string::const_iterator it = val.begin();
            if(utils::is_digit(*it)) {
                while(utils::is_digit(*it)) {
                    result *= 10;
                    result += *it - '0';
                    it++;
                }
                if(*it == '.') {
                    while(utils::is_digit(*(++it))) {
                        result += (*it - '0') / floating_point;
                        floating_point *= 10;
                    }
                }
            } else if(*it == 'R' && utils::is_digit(*(it + 1))) {
                int row = 0, col = 0;
                while(utils::is_digit(*(++it))) {
                    row *= 10;
                    row += *it - '0';
                }
                
                if(*it == 'C' && utils::is_digit(*(it + 1))) {
                    while(utils::is_digit(*(++it))) {
                        col *= 10;
                        col += *it - '0';
                    }
                }
                
                result = atof(get_row().get_table().get_cell_value(row - 1, col - 1).c_str());
            }
            
            if(*it != '\0') {
                throw CellException("ERROR:.........");
            }

            return result;
        }

        int FormulaCell::priority(const char& op) {
            if(op == '^') return 5;
            if(op == '/') return 4;
            if(op == '*') return 3;
            if(op == '-') return 2;
            if(op == '+') return 1;
            return 0;
        }

        double FormulaCell::exec_bin_op(char op, double val1, double val2) {
            const double eps = 0.001;

            if(op == '+') return val1 + val2;
            else if(op == '-') return val1 - val2;
            else if(op == '*') return val1 * val2;
            else if(op == '/') {
                if(fabs(val2) < eps) throw BinOperationException("ERROR: Division by zero");
                return val1 / val2;
            } else if(op == '^') return pow(val1, val2);

            throw CellException("ERROR: Unknown operation in exec_bin_op()");
        }

        double FormulaCell::calculate_recursive(std::size_t i, double res, std::size_t& next, int prior) const {
            if(i >= values.size()) return 0; // if values.size = 0
            if(i == operations.size()) return res; // if operations.size = 0

            next++;
            double curr_res = parse(values[i + 1]);

            if( i != operations.size() - 1 &&
                priority(operations[i + 1]) > 2 &&
                priority(operations[i + 1]) >= priority(operations[i])) {
                    curr_res = calculate_recursive(i + 1, curr_res, next, priority(operations[i]));
                }

            if(next == operations.size() || priority(operations[next]) < prior) {
                return exec_bin_op(operations[i], res, curr_res);
            }

            return calculate_recursive(next, exec_bin_op(operations[i], res, curr_res), next, prior);
        }

        double FormulaCell::calculate() const {
            std::size_t i = 0;
            return calculate_recursive(0, parse(values[0]), i, 0);
        }

        std::string FormulaCell::get_value() const {
            double result = calculate();

            std::stringstream ss;
            ss << result;
            return ss.str();
        }

}