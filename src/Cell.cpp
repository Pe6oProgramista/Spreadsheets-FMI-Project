#include "Cell.hpp"

#include "Row.hpp"
#include "utility/utils.hpp"

namespace e_table {
    
    Cell::Cell(Row& row, std::string type, std::string formula)
        : type(type), formula(formula), row(row) {
            col = row.cells_cnt() + 1;
        }

    std::string Cell::get_type() const { return type; }
    
    Row& Cell::get_row() const { return row; }
    
    int Cell::get_col() const { return col; }

    std::string Cell::get_formula() const { return formula; }
    
    void Cell::set_formula(const std::string& formula) { 
        this->formula = valid(formula);
    }
    
}