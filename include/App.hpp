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

        std::vector<utils::SmartPtr<Operation>> operations;

        std::string app_filename;
        bool status = false;
    
    public:
        App() = default;
        App(const App& app) = delete;

        void init();

        // check "unsafe" to see where its used
        Table& get_table();
        
        utils::SmartPtr<const Operation> get_operation(std::size_t indx) const;
        void add_operation(utils::SmartPtr<Operation> operation);
        utils::SmartPtr<Operation> find_operation(const std::string& name);
        std::size_t ops_cnt() const;

        bool get_status() const;
        void set_status(bool status);

        std::string get_app_filename() const;
        void set_app_filename(std::string filename);

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