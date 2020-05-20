#pragma once

#include <string>

namespace e_table {

    class Row;

    class Cell {
    public:
        class Ptr {
        private:
            Cell* c;
        public:
            Ptr() : c(nullptr) {}
            Ptr(Cell* c) : c(c) { ++c->count; }
            Ptr(const Ptr& p) : c(p.c) { ++c->count; }
            ~Ptr() { if (!is_null() && --c->count == 0) delete c; }

            Ptr& operator= (const Ptr& p) {
                Cell* const old = c;
                c = p.c;
                ++c->count;
                if (--old->count == 0) delete old;
                return *this;
            }
            
            Cell* operator-> () const { return c; }
            Cell& operator* ()  { return *c; }

            bool is_null() const { return c == nullptr; }
        };

    private:
        std::size_t count = 0;

        std::string type;         

    protected:
        std::string formula;
        Row& row;
        int col;

        virtual std::string valid(std::string val) = 0;

    public:
        Cell(Row& row, std::string type, std::string formula);
        virtual ~Cell() = default;

        std::string get_type() const;
        Row& get_row() const;
        int get_col() const;
        std::string get_formula() const;
        void set_formula(const std::string& formula);
        
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

    class BinOperationException: virtual public std::exception {
        protected:
            std::string error_message;
            
        public:
            BinOperationException(const std::string& msg)
                : error_message(msg) {}

            virtual ~BinOperationException() throw () {}
            
            virtual const char* what() const throw () { return error_message.c_str(); }
    };

}