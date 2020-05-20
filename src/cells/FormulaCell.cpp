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
        FormulaCell::FormulaCell(Row& row, const std::string& formula)
            : Cell(row, "formula", formula) {
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
                        if(last_is_op) throw CellException("ERROR: Can't execute 2 operations at once");
                        operations.push_back(*it);
                        last_is_op = true;   
                } else {
                    if(last_is_op == false) throw CellException("ERROR: form.........");
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
                        do {
                            value.push_back(*it);
                            it++;
                        } while(utils::is_digit(*it));
                        
                        if(*it == 'C' && utils::is_digit(*(it + 1))) {
                            do {
                                value.push_back(*it);
                                it++;
                            } while(utils::is_digit(*it));
                        }
                    } else {
                        throw CellException("ERROR:.........");
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
                    it++;
                    while(utils::is_digit(*it)) {
                        result += (*it - '0') / floating_point;
                        floating_point *= 10;
                        it++;
                    }
                }
            } else if(*it == 'R' && utils::is_digit(*(it + 1))) {
                it++;
                int row = 0, col = 0;
                while(utils::is_digit(*it)) {
                    row *= 10;
                    row += *it - '0';
                    it++;
                }
                
                if(*it == 'C' && utils::is_digit(*(it + 1))) {
                    it++;
                    while(utils::is_digit(*it)) {
                        col *= 10;
                        col += *it - '0';
                        it++;
                    }
                }
                
                result = atoi(get_row().get_table().get_row(row)->get_cell(col)->get_value().c_str());
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

        double FormulaCell::calculate(std::size_t i, double res, std::size_t& next, int prior) const {
            if(values.size() == 1) return res;

            next++;
            double curr_res = parse(values[i + 1]);

            if( i != operations.size() - 1 &&
                priority(operations[i + 1]) > 2 &&
                priority(operations[i + 1]) >= priority(operations[i])) {
                    curr_res = calculate(i + 1, curr_res, next, priority(operations[i]));
                }

            if(next == operations.size() || priority(operations[next]) < prior) {
                return exec_bin_op(operations[i], res, curr_res);
            }

            return calculate(next, exec_bin_op(operations[i], res, curr_res), next, prior);
        }

        std::string FormulaCell::get_value() const {
            double result = 0;

            if(values.size() > 0) {
                std::size_t i = 0;
                result = calculate(0, parse(values[0]), i, 0);
            }

            std::stringstream ss;
            ss << result;
            return ss.str();
        }

}