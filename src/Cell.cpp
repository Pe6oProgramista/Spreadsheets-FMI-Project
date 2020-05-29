#include "Cell.hpp"

#include "Row.hpp"
#include "utility/utils.hpp"

namespace e_table {
    
    Cell::Cell(Row& row, int indx, std::string type, std::string formula)
        : type(type), row(row), indx(indx), formula(formula) {}

    std::string Cell::get_type() const { return type; }
    
    const Row& Cell::get_row() const { return row; }
    
    int Cell::get_indx() const { return indx; }

    std::string Cell::get_formula() const { return formula; }
    
    void Cell::set_formula(const std::string& formula) { 
        this->formula = valid(formula);
    }
    
}