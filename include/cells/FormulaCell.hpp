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
        double calculate_recursive(std::size_t i, double res, std::size_t& next, int prior) const;
        double calculate() const;
    
    public:
        FormulaCell(Row& row, int indx, const std::string& formula);
        
        std::string get_value() const;
    };

    class BinOperationException: virtual public std::exception {
    protected:
        std::string error_message;
        
    public:
        BinOperationException(const std::string& msg)
            : error_message(msg) {}

        virtual ~BinOperationException() throw () {}
        
        virtual const char* what() const throw () { return error_message.c_str(); }
    };

    class FormulaCellException: public CellException {        
    public:
        FormulaCellException(const std::string& msg)
            : CellException(msg) {}

    };

}