#ifndef TERMINAL_H
#define TERMINAL_H
#include <string>
#include <regex>

std::string regString = "((Rectangle +\\([0-9]+\\.?[0-9]?\\, *[0-9]+\\.?[0-9]?\\)) +|(Ellipse +\\([0-9]+\\.?[0-9]?\\, *[0-9]+\\.?[0-9]?\\)) +|Triangle *\\((\\[\\-?[0-9]\\, *\\-?[0-9]\\],* *)+\\) +)+((area)|(perimeter)) +((inc)|(dec))";
class Terminal {
public:
    Terminal(std::string input): _input(input){
        if (checkInput(input)) {

        }
        else {
            throw std::string("invalid input");
        }
    }
private:
    std::string const _input;
    bool checkInput(std::string input) {
        std::regex reg(regString);
        return std::regex_match(input, reg);
    }
};
#endif
