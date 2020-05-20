#pragma once

#include <vector>
#include <string>

#include "Cell.hpp"

namespace e_table {
    class Table;

    class Row {
    public:
        class Ptr {
        private:
            Row* r;
        public:
            Ptr() : r(nullptr) {}
            Ptr(Row* r) : r(r) { ++r->count; }
            Ptr(const Ptr& p) : r(p.r) { ++r->count; }
            ~Ptr() { if (!is_null() && --r->count == 0) delete r; }

            Ptr& operator= (const Ptr& p) {
                Row* const old = r;
                r = p.r;
                ++r->count;
                if (--old->count == 0) delete old;
                return *this;
            }
            
            Row* operator-> () const { return r; }
            Row& operator* ()  { return *r; }

            bool is_null() const { return r == nullptr; }
        };

    private:
        std::size_t count = 0;

        std::vector<Cell::Ptr> cells;
        Table& table;

    private:
        Cell::Ptr read_cell(const std::string& data);

    public:
        Row(Table& table)
            : table(table) {}

        Table& get_table() const;
        const std::vector<Cell::Ptr>& get_cells() const;
        void add_cell(const Cell::Ptr& cell);
        Cell::Ptr& get_cell(std::size_t col);
        void edit_cell(std::size_t col, const std::string& value);
        std::size_t cells_cnt() const;
        
        // read/write funcitons
        void read(std::istream& in);
        void write(std::ostream& out) const;

        Row operator= (const Row& r);
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