#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "App.hpp"

#include "Table.hpp"
#include "Row.hpp"
#include "cells/FormulaCell.hpp"

#include "operations/OpenOperation.hpp"
#include "operations/ExitOperation.hpp"

#include "operations/PrintOperation.hpp"
#include "operations/EditOperation.hpp"

#include "utility/utils.hpp"

int main() {
    // 1
    std::cout << std::endl << "----------1----------" << std::endl;
    {
        // e_table::Table t;
        // e_table::Row::Ptr row = new e_table::Row(t);
        // e_table::FormulaCell::Ptr fc = new e_table::FormulaCell(*row, "5 + R1C2");
        // e_table::FormulaCell::Ptr fc2 = new e_table::FormulaCell(*row, "1");
        // row->add_cell(fc);
        // row->add_cell(fc2);
        // t.add_row(row);

        // fc->set_formula(""); // 0
        // std::cout << fc->get_value() << '\n';

        // fc->set_formula("5 + R1C2"); // 6
        // std::cout << fc->get_value() << '\n';

        // fc->set_formula("5 ^ 2 ^ 3"); // 390625
        // std::cout << fc->get_value() << '\n';

        // fc->set_formula("2 + 3 * 4 / 5 - 1 * 16"); // -11.6
        // std::cout << fc->get_value() << '\n';

        // fc->set_formula("3 * 2 * 4 ^ 2 + 11"); // 107
        // std::cout << fc->get_value() << '\n';

        // fc->set_formula("5 ^ 2 ^ 1 * 4 * 7 - 22 + 3 ^ 5"); // 921
        // std::cout << fc->get_value() << '\n';

        // fc->set_formula("2 + 3 + 5 ^ 2 ^ 1 - 4 * 5 / 2 * 3 ^ 2 + 1 - 7"); // -66
        // std::cout << fc->get_value() << '\n';

        // fc->set_formula("5 * 2 * 3"); // 30
        // std::cout << fc->get_value() << '\n';
    }

    e_table::App app;
    app.add_operation(new e_table::OpenOperation(app));
    app.add_operation(new e_table::ExitOperation(app));

    app.add_operation(new e_table::PrintOperation(app));
    app.add_operation(new e_table::EditOperation(app));

    std::string command;
    while (true) {
        try {
            std::cout << "> ";
            std::getline(std::cin, command);

            std::vector<std::string> args = e_table::utils::split(command, ' ');
            e_table::Operation* operation = app.find_operation(args[0]);

            args.erase(args.begin());
            operation->execute(args);

            if(operation->get_name() == "exit") { // dynamic_cast<e_table::ExitOperation*>(operation)
                break;
            }

        } catch(std::exception& e) {
            std::cout << e.what() << std::endl;
        }
    }
    
    return 0;
}