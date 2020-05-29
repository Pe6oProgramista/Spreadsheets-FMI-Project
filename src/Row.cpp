#include <string>
#include <iostream>

#include "Row.hpp"

#include "Table.hpp"
#include "Cell.hpp"
#include "cells/IntCell.hpp"
#include "cells/DoubleCell.hpp"
#include "cells/StringCell.hpp"
#include "cells/FormulaCell.hpp"
#include "utility/utils.hpp"

namespace e_table {

    Row::Row(Table& table) : table(table) {
        indx = table.rows_cnt();
    }

    utils::SmartPtr<Cell> Row::read_cell(const std::string& data, int cell_indx = -1) {
        if(cell_indx < 0) cell_indx = cells_cnt();

        if(utils::trim(data) == "") return new StringCell(*this, cell_indx, "\"\"");

        try {
            return new IntCell(*this, cell_indx, data);
        } catch(CellException& e){};

        try {
            return new DoubleCell(*this, cell_indx, data);
        } catch(CellException& e){};

        try {
            return new StringCell(*this, cell_indx, data);
        } catch(CellException& e){};

        try {
            return new FormulaCell(*this, cell_indx, data);
        } catch(FormulaCellException& e){throw;};
        
        throw RowException("ERROR: Unknown data type"); // Error: row 2, col 5, 123.123.123 is unknown data type
    }
    
    int Row::get_indx() const { return indx; }

    const Table& Row::get_table() const { return table; }

    void Row::add_cell(const utils::SmartPtr<Cell>& cell) {
        if(&cell->get_row() != this) throw RowException("ERROR: Trying to add cell from different row");
        cells.push_back(cell);
    }

    void Row::add_cell(const std::string& str) {
        utils::SmartPtr<Cell> cell = read_cell(str);
        cells.push_back(cell);
    }

    utils::SmartPtr<const Cell> Row::get_cell(const std::size_t& col) const {
        if(col < 0 || col >= cells.size()) {
            throw RowException("ERROR: cells out of range");
        }

        return cells[col];
    }

    std::size_t Row::cells_cnt() const { return cells.size(); }

    void Row::edit_cell(std::size_t col, const std::string& value) {
        int cell_indx = cells[col]->get_indx();
        cells[col] = read_cell(value, cell_indx);
    }

    void Row::read(std::istream& in) {
        std::vector<utils::SmartPtr<Cell>> old_cells = cells;

        cells.clear();

        try {
            std::string cell_data;
            while(std::getline(in, cell_data, ',')) {
                utils::SmartPtr<Cell> cell = read_cell(cell_data);
                cells.push_back(cell);
            }
        } catch(std::exception& e) {
            cells = old_cells;
            throw;
        }
    }

    void Row::write(std::ostream& out) const {
        for(std::vector<utils::SmartPtr<Cell>>::const_iterator it = cells.begin(); it != cells.end(); it++) {
            if(it != cells.begin()) out << ',';
            out << (*it)->get_formula();
        }
    }

    Row& Row::operator= (const Row& r) {
        cells = r.cells;
        table = r.table;

        return *this;
    }

}