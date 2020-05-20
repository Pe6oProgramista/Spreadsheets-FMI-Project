#pragma once

#include <vector>
#include <string>

#include "Cell.hpp"

namespace e_table {

    class FormulaCell : public Cell {
    private:
        std::vector<std::string> values;
        std::vector<char> operations; // existing operation in this formula

    private:
        std::string valid(std::string val);

        double parse(const std::string& val) const;
        static int priority(const char& op);
        static double exec_bin_op(char op, double val1, double val2);
        double calculate(std::size_t i, double res, std::size_t& next, int prior) const;
    
    public:
        FormulaCell(Row& row, const std::string& formula);
        
        std::string get_value() const;

        void set_values(std::vector<std::string>& values) { this->values = values; }
        void set_ops(std::vector<char>& ops) { operations = ops; }
    };

}