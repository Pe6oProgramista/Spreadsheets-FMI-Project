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

    Cell::Ptr Row::read_cell(const std::string& data) {
        if(utils::trim(data) == "") return new StringCell(*this, "\"\"");

        try {
            return new IntCell(*this, data);
        } catch(CellException& e){};

        try {
            return new DoubleCell(*this, data);
        } catch(CellException& e){};

        try {
            return new StringCell(*this, data);
        } catch(CellException& e){};

        try {
            return new FormulaCell(*this, data);
        } catch(CellException& e){};
        
        throw RowException("ERROR: Unknown data type"); // Error: row 2, col 5, 123.123.123 is unknown data type
    }
    
    Table& Row::get_table() const { return table; }

    const std::vector<Cell::Ptr>& Row::get_cells() const { return cells; }

    std::size_t Row::cells_cnt() const { return cells.size(); }

    void Row::add_cell(const Cell::Ptr& cell) {
        if(&cell->get_row() != this) throw RowException("ERROR: Trying to add cell from different row");
        cells.push_back(cell);
    }

     Cell::Ptr& Row::get_cell(std::size_t col) {
        if(col < 1 || col > cells.size()) {
            throw RowException("ERROR: cells out of range");
        }

        return cells[col - 1];
     }

    void Row::edit_cell(std::size_t col, const std::string& value) {
        get_cell(col) = read_cell(value);
    }

    void Row::read(std::istream& in) {
        std::vector<Cell::Ptr> new_cells;

        std::string cell_data;
        while(std::getline(in, cell_data, ',')) {
            Cell::Ptr cell = read_cell(cell_data);
            new_cells.push_back(cell);
        }

        cells = new_cells;
    }

    void Row::write(std::ostream& out) const {
        for(std::vector<Cell::Ptr>::const_iterator it = cells.begin(); it != cells.end(); it++) {
            if(it != cells.begin()) out << ',';
            out << (*it)->get_formula();
        }
    }

    Row Row::operator= (const Row& r) {
        cells = r.cells;
        table = r.table;

        return *this;
    }

}