#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>

#include "Table.hpp"
#include "Row.hpp"

namespace e_table {

    void Table::add_row(const utils::SmartPtr<Row>& row) {
        if(&row->get_table() != this) throw TableException("ERROR: Trying to add row from different table");

        if(rows.size() == 0 || row->cells_cnt() > max_cells_cnt) {
            max_cells_cnt = row->cells_cnt();
        }

        rows.push_back(row);
     }

     void Table::add_row(const std::string& str) {
        utils::SmartPtr<Row> row = new Row(*this);
        std::istringstream iss(str);
        row->read(iss);

        rows.push_back(row);
     }
    
    utils::SmartPtr<const Row> Table::get_row(std::size_t indx) const {
        if(indx < 0 || indx >= rows.size()) {
            throw TableException("ERROR: rows out of range");
        }

        return rows[indx];
    }

    std::size_t Table::rows_cnt() const { return rows.size(); }

    std::string Table::get_cell_value(int row, int col) const {
        return get_row(row)->get_cell(col)->get_value();
    }

    std::string Table::get_cell_formula(int row, int col) const {
        return get_row(row)->get_cell(col)->get_formula();
    }

    void Table::edit_cell(int row, int col, std::string value) {
        rows[row]->edit_cell(col, value);
    }

    // read/write functions
    void Table::read(std::istream& in) {
        std::vector<utils::SmartPtr<Row>> old_rows = rows;
        std::size_t old_max_cells_cnt = max_cells_cnt;
        
        rows.clear();
        max_cells_cnt = 0;

        try {
            std::string line;
            while(std::getline(in, line, '\n')) {
                utils::SmartPtr<Row> row = new Row(*this);
                std::istringstream iss(line);
                row->read(iss);

                if(rows.size() == 0 || row->cells_cnt() > max_cells_cnt) {
                    max_cells_cnt = row->cells_cnt();
                }
                rows.push_back(row);
            }
        } catch(std::exception& e) {
            rows = old_rows;
            max_cells_cnt = old_max_cells_cnt;
            throw;
        }
    }
    
    void Table::write(std::ostream& out) const {
        for(const utils::SmartPtr<Row>& r : rows) {
            r->write(out);
            out << '\n';
        }
    }

    void Table::print(std::ostream& out) const {
        std::vector<std::size_t> max_cell_sizes(max_cells_cnt, 0);
        std::vector<std::string> values;
        for(std::size_t i = 0; i < rows.size(); i++) {
            for(std::size_t j = 0; j < max_cells_cnt; j++) {
                std::string new_val = (j < rows[i]->cells_cnt()) ? get_cell_value(i, j) : "";
                if(max_cell_sizes[j] < new_val.size()) {
                    max_cell_sizes[j] = new_val.size();
                }
                values.push_back(new_val);
            }
        }


        for(std::size_t i = 0; i < rows.size(); i++) {
            out << "| ";
            for(std::size_t j = 0; j < max_cells_cnt; j++) {
                out << std::left
                    << std::setw(max_cell_sizes[j])
                    << values[i * max_cells_cnt + j]
                    << " | ";
            }
            out << '\n';
        }
    }
}