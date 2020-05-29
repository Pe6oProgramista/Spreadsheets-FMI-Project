#include "App.hpp"

#include "Operation.hpp"


#include <iostream>
namespace e_table {

    void App::init() {
        table = Table();
        app_filename.clear();
    }

    Table& App::get_table() { return table; }

    bool App::get_status() const { return status; }
    void App::set_status(bool status) { this->status = status; }

    std::string App::get_app_filename() const { return app_filename; }
    void App::set_app_filename(std::string filename) { app_filename = filename; }

    utils::SmartPtr<const Operation> App::get_operation(std::size_t indx) const { return operations[indx]; }

    void App::add_operation(utils::SmartPtr<Operation> operation) {
        operations.push_back(operation);
    }

    utils::SmartPtr<Operation> App::find_operation(const std::string& name) {
        for (std::vector<utils::SmartPtr<Operation>>::iterator it = operations.begin(); it != operations.end(); ++it) {
			if ((*it)->get_name() == name) {
				return *it;
			}
		}
		throw OperationException("ERROR: Unknown operation");
    }

    std::size_t App::ops_cnt() const { return operations.size(); }

    // read/write funcitons
    void App::read(std::istream& in) {
        table.read(in);
    }

    void App::write(std::ostream& out) const {
        table.write(out);
    }

}