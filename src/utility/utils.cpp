#include <sstream>
#include <string>
#include <string.h>
#include <vector>

#include "utility/utils.hpp"

#include "App.hpp"
#include "Operation.hpp"
#include "operations/OpenOperation.hpp"
#include "operations/CloseOperation.hpp"
#include "operations/SaveOperation.hpp"
#include "operations/SaveAsOperation.hpp"
#include "operations/HelpOperation.hpp"
#include "operations/ExitOperation.hpp"

#include "operations/PrintOperation.hpp"
#include "operations/EditOperation.hpp"


namespace e_table {
    namespace utils {
        std::vector<std::string> split(const std::string& s, char delimiter) {
            std::vector<std::string> tokens;
            std::string token;
            std::istringstream tokenStream(s);
            while (std::getline(tokenStream, token, delimiter)) {
                token = trim(token);
                if(token == "") continue;
                tokens.push_back(token);
            }
            return tokens;
        }

        std::vector<std::string> split(const std::string& s, std::string delimiter) {
            std::vector<std::string> tokens;
            char token;
            std::string curr_str;
            std::istringstream tokenStream(s);
            while (tokenStream.get(token)) {
                if(delimiter.find(token)) {
                    curr_str = trim(curr_str);
                    if(curr_str == "") continue;
                    tokens.push_back(curr_str);
                    curr_str.clear();
                } else {
                    curr_str.push_back(token);
                }
            }

            return tokens;
        }

        std::string trim(std::string s) {
            std::size_t startpos = s.find_first_not_of(" \t");
            std::size_t endpos = s.find_last_not_of(" \t");

            if(startpos == std::string::npos || endpos == std::string::npos) {
                return "";
            }

            s = s.substr(startpos, endpos - startpos + 1);

            return s;
        }

        bool is_digit(int c) {
            return c >= '0' && c <= '9';
        }

        void load_all_operations(App& app) {
            // default operations
            app.add_operation(new e_table::OpenOperation(app));
            app.add_operation(new e_table::CloseOperation(app));
            app.add_operation(new e_table::SaveOperation(app));
            app.add_operation(new e_table::SaveAsOperation(app));
            app.add_operation(new e_table::HelpOperation(app));
            app.add_operation(new e_table::ExitOperation(app));

            // additional operations
            app.add_operation(new e_table::PrintOperation(app));
            app.add_operation(new e_table::EditOperation(app));
        }
    }
}