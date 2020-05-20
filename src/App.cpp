#include "App.hpp"

#include "Operation.hpp"


#include <iostream>
namespace e_table {

    App::~App() {
        for(Operation*& it : operations) {
            delete it;
        }
    }

    Table& App::get_table() { return table; }
    const Table& App::get_const_table() const { return table; }

    bool App::get_status() const { return status; }
    void App::set_status(bool status) { this->status = status; }

    std::string App::get_app_filename() const { return app_filename; }
    void App::set_app_filename(std::string filename) { app_filename = filename; }

    void App::add_operation(Operation* operation) {
        operations.push_back(operation);
    }

    Operation* App::find_operation(std::string name) {
        for (std::vector<Operation*>::iterator it = operations.begin(); it != operations.end(); ++it) {
			if ((*it)->get_name() == name) {
				return *it;
			}
		}
		throw OperationException("ERROR: Unknown operation");
    }

    // TODO
    void update() {

    }

    // read/write funcitons
    void App::read(std::istream& in) {
        table.read(in);
    }

    void App::write(std::ostream& out) const {
        table.write(out);
    }

}