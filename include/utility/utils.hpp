#pragma once

#include <vector>
#include <string>

#include "Operation.hpp"
#include "App.hpp"

namespace e_table {
    namespace utils {
        std::vector<std::string> split(const std::string& s, char delimiter);

        std::vector<std::string> split(const std::string& s, std::string delimiter);

        std::string trim(const std::string s);

        bool is_digit(int c);

        void load_all_operations(App& app);
    }
}