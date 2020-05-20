#pragma once

#include <string>
#include <vector>

namespace e_table {
    
    class App;

    class Operation {
    private:
        std::string name;
        std::string description;
        std::size_t args_count;
        std::string args_names;

    protected:
        App& app;

    public:
        Operation(App& app, std::string name, std::string description, int args_count, std::string args_names)
            : name(name), description(description), args_count(args_count), args_names(args_names), app(app) {}

        virtual ~Operation() = default;

        std::string get_name() const { return name; }
        std::string get_description() const { return description; }
        std::size_t get_args_count() const { return args_count; }
        std::string get_args_names() const { return args_names; }
        
        virtual void execute(std::vector<std::string>& args) = 0;
    };

    class OperationException: virtual public std::exception {
    protected:
        std::string error_message;
        
    public:
        OperationException(const std::string& msg)
            : error_message(msg) {}

        virtual ~OperationException() throw () {}
        
        virtual const char* what() const throw () { return error_message.c_str(); }
    };

}