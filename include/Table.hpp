#pragma once

#include <vector>

#include "Row.hpp"
#include "Cell.hpp"

namespace e_table {

    class Table {
    private:
        std::vector<utils::SmartPtr<Row>> rows;
        std::size_t max_cells_cnt;

    public:
        void add_row(const utils::SmartPtr<Row>& row);
        void add_row(const std::string& str);
        utils::SmartPtr<const Row> get_row(std::size_t row) const;
        std::size_t rows_cnt() const;
        
        std::string get_cell_value(int row, int col) const;
        std::string get_cell_formula(int row, int col) const;
        void edit_cell(int row, int col, std::string value);

        // read/write operations
        void read(std::istream& in);
        void write(std::ostream& out) const;

        void print(std::ostream& out) const;
    };

    class TableException: virtual public std::exception {
    protected:
        std::string error_message;
        
    public:
        TableException(const std::string& msg)
            : error_message(msg) {}

        virtual ~TableException() throw () {}
        
        virtual const char* what() const throw () { return error_message.c_str(); }
    };

}