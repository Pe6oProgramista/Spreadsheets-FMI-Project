#pragma once

#include <vector>
#include <string>

#include "Cell.hpp"
#include "utility/SmartPtr.hpp"

namespace e_table {
    class Table;

    class Row {
    // fields
    private:
        Table& table;
        int indx;

        std::vector<utils::SmartPtr<Cell>> cells;

    // methods
    private:
        utils::SmartPtr<Cell> read_cell(const std::string& data, int cell_indx);

    protected:
        friend class Table;

        Row(Table& table);

        void add_cell(const utils::SmartPtr<Cell>& cell);
        void add_cell(const std::string& str);
        void edit_cell(std::size_t col, const std::string& value);

        // read/write funcitons
        void read(std::istream& in);
        void write(std::ostream& out) const;

        Row& operator= (const Row& r);
    
    public:
        int get_indx() const;
        const Table& get_table() const;
        utils::SmartPtr<const Cell> get_cell(const std::size_t& col) const;
        std::size_t cells_cnt() const;
    };

    class RowException: virtual public std::exception {
    protected:
        std::string error_message;
        
    public:
        RowException(const std::string& msg)
            : error_message(msg) {}

        virtual ~RowException() throw () {}
        
        virtual const char* what() const throw () { return error_message.c_str(); }
    };

}