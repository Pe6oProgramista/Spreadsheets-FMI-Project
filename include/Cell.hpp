#pragma once

#include <string>

namespace e_table {

    class Row;

    class Cell {
    // fields
    private:
        std::string type;         

    protected:
        Row& row;
        int indx;

        std::string formula;

    // methods
    protected:
        friend class Row;

        Cell(Row& row, int indx, std::string type, std::string formula);
        void set_formula(const std::string& formula);
        
        virtual std::string valid(std::string val) = 0;
    
    public:
        virtual ~Cell() = default;

        std::string get_type() const;
        const Row& get_row() const;
        int get_indx() const;
        std::string get_formula() const;
        
        virtual std::string get_value() const = 0;
    };

    class CellException: virtual public std::exception {
    protected:
        std::string error_message;
        
    public:
        CellException(const std::string& msg)
            : error_message(msg) {}

        virtual ~CellException() throw () {}
        
        virtual const char* what() const throw () { return error_message.c_str(); }
    };

}