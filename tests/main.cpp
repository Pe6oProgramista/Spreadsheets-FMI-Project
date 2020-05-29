#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "App.hpp"

#include "Table.hpp"
#include "Row.hpp"
#include "cells/FormulaCell.hpp"
#include "utility/utils.hpp"

using namespace e_table;
using namespace utils;
using namespace std;
int main() {
    e_table::App app;
    e_table::utils::load_all_operations(app);

    std::string command;
    while (true) {
        try {
            std::cout << "> ";
            std::getline(std::cin, command);

            std::vector<std::string> args = e_table::utils::split(command, ' ');
            if(args.size() == 0) continue;
            
            e_table::utils::SmartPtr<e_table::Operation> operation = app.find_operation(args[0]);

            args.erase(args.begin());
            operation->execute(args);

            if(operation->get_name() == "exit") {
                break;
            }

        } catch(std::exception& e) {
            std::cout << e.what() << std::endl;
        }
    }
    
    return 0;
}