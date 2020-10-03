#ifndef TERMINAL_H
#define TERMINAL_H
#include <string>

class Terminal {
public:
    Terminal(std::string input): _input(input){

    }
    // INC（递增）DEC（递减）
private:
    std::string const _input;
};
#endif
