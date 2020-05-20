#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>

#include "Table.hpp"
#include "Row.hpp"

namespace e_table {

    const std::vector<Row::Ptr>& Table::get_rows() const { return rows; }

    void Table::add_row(Row::Ptr& row) {
        if(&row->get_table() != this) throw TableException("ERROR: Trying to add row from different table");

        if(rows.size() == 0) {
            cells_count = row->cells_cnt();
        } else if(row->cells_cnt() != cells_count) {
            std::stringstream ss;
            ss << "ERROR: Missing cell in row " << rows.size() + 1;
            throw TableException(ss.str());
        }

        rows.push_back(row);
     }
    
    Row::Ptr& Table::get_row(std::size_t row) {
        if(row < 1 || row > rows.size()) {
                throw TableException("ERROR: rows out of range");
            }

        return rows[row - 1];
    }

    // read/write functions
    void Table::read(std::istream& in) {
        std::vector<Row::Ptr> rows;
        std::size_t cells_count = 0;

        std::string line;
        while(std::getline(in, line, '\n')) {
            Row::Ptr row = new Row(*this);
            std::istringstream iss(line);
            row->read(iss);

            if(rows.size() == 0 || row->cells_cnt() > cells_count) {
                cells_count = row->cells_cnt();
            }
            rows.push_back(row);
        }

        this->rows = rows;
        this->cells_count = cells_count;
    }
    
    void Table::write(std::ostream& out) const {
        for(const Row::Ptr& r : rows) {
            r->write(out);
            out << '\n';
        }
    }

    void Table::print(std::ostream& out) const {
        std::vector<std::size_t> max_cell_sizes(cells_count, 0);
        std::vector<std::string> values;
        for(std::size_t i = 0; i < rows.size(); i++) {
            const std::vector<Cell::Ptr>& cells = rows[i]->get_cells();
            for(std::size_t j = 0; j < cells_count; j++) {
                std::string new_val = (j < rows[i]->cells_cnt()) ? cells[j]->get_value() : "";
                if(max_cell_sizes[j] < new_val.size()) {
                    max_cell_sizes[j] = new_val.size();
                }
                values.push_back(new_val);
            }
        }


        for(std::size_t i = 0; i < rows.size(); i++) {
            out << "| ";
            for(std::size_t j = 0; j < cells_count; j++) {
                out << std::left
                    << std::setw(max_cell_sizes[j])
                    << values[i * cells_count + j]
                    << " | ";
            }
            out << '\n';
        }
    }
}