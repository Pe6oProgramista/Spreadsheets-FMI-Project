#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "App.hpp"
#include "Table.hpp"
#include "Row.hpp"
#include "cells/FormulaCell.hpp"

int main() {
    std::cout << "\n-----Formula Cell Test-----\n";  
    e_table::Table t;
    t.add_row("5 + R1C2, 0");

    t.edit_cell(0, 0, "R1C2"); // 0
    std::cout << t.get_cell_value(0, 0) << '\n';

    t.edit_cell(0, 1, "1");

    t.edit_cell(0, 0, "5 + R1C2"); // 6
    std::cout << t.get_cell_value(0, 0) << '\n';

    t.edit_cell(0, 0, "5 ^ 2 ^ 3"); // 390625
    std::cout << t.get_cell_value(0, 0) << '\n';

    t.edit_cell(0, 0, "2 + 3 * 4 / 5 - 1 * 16"); // -11.6
    std::cout << t.get_cell_value(0, 0) << '\n';

    t.edit_cell(0, 0, "3 * 2 * 4 ^ 2 + 11"); // 107
    std::cout << t.get_cell_value(0, 0) << '\n';

    t.edit_cell(0, 0, "5 ^ 2 ^ 1 * 4 * 7 - 22 + 3 ^ 5"); // 921
    std::cout << t.get_cell_value(0, 0) << '\n';

    t.edit_cell(0, 0, "2 + 3 + 5 ^ 2 ^ 1 - 4 * 5 / 2 * 3 ^ 2 + 1 - 7"); // -66
    std::cout << t.get_cell_value(0, 0) << '\n';

    t.edit_cell(0, 0, "5 * 2 * 3"); // 30
    std::cout << t.get_cell_value(0, 0) << '\n';

    // recursive ref to same cell
    try {
        t.edit_cell(0, 0, "R1C1"); // ERROR: You try to make circular reference
        std::cout << t.get_cell_value(0, 0) << '\n';
    } catch(std::exception& e) {
        std::cout << e.what() << '\n';
    }

    std::cout << "test finished\n";

    return 0;
}