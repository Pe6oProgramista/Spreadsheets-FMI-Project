#pragma once

#include <vector>

#include "Row.hpp"
#include "Cell.hpp"

namespace e_table {

    class Table {
    private:
        std::vector<Row::Ptr> rows;
        std::size_t cells_count;

    public:
        const std::vector<Row::Ptr>& get_rows() const;
        void add_row(Row::Ptr& row);
        Row::Ptr& get_row(std::size_t row);
        
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