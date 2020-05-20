#include <sstream>
#include <string>
#include <string.h>
#include <vector>

#include "utility/utils.hpp"

#include "App.hpp"
#include "Operation.hpp"
#include "operations/OpenOperation.hpp"


#include <iostream>
namespace e_table {
    namespace utils {
        std::vector<std::string> split(const std::string& s, char delimiter) {
            std::vector<std::string> tokens;
            std::string token;
            std::istringstream tokenStream(s);
            while (std::getline(tokenStream, token, delimiter)) {
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
            if(c < '0' || c > '9') return false;
            return true;
        }

        // App load_app(std::string filename) {

        // }

        std::vector<Operation*> generate_operations(App& app) {
            std::vector<Operation*> ops;

            ops.push_back(new OpenOperation(app));
            // ops.push_back(new CloseOperation(app));
            // ops.push_back(new SaveOperation(app));
            // ops.push_back(new SaveAsOperation(app));
            // ops.push_back(new HelpOperation(app));
            // ops.push_back(new ExitOperation(app));

            return ops;
        }
    }
}