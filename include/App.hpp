#pragma once

#include <fstream>
#include <vector>
#include <string>

#include "Table.hpp"
#include "Operation.hpp"

namespace e_table {

    class App {
    private:
        Table table;

        std::vector<Operation*> operations;

        bool status;
        std::string app_filename;
    
    public:
        App() = default;
        App(const App& app) = delete;
        ~App();

        Table& get_table();
        const Table& get_const_table() const;

        bool get_status() const;
        void set_status(bool status);

        std::string get_app_filename() const;
        void set_app_filename(std::string filename);
    
        void add_operation(Operation* operation);
        Operation* find_operation(std::string name);

        // read/write funcitons
        void read(std::istream& in);
        void write(std::ostream& out) const;
    };

    class AppException: virtual public std::exception {
    protected:
        std::string error_message;
        
    public:
        AppException(const std::string& msg)
            : error_message(msg) {}

        virtual ~AppException() throw () {}
        
        virtual const char* what() const throw () { return error_message.c_str(); }
    };

}