#ifndef SCANNER_H
#define SCANNER_H

#include <ctype.h>
#include <iostream>
#include <sstream>
#include <string>
#include <list>

typedef std::list<std::string>::iterator StrIterator;

enum status
{
    Number,
    Alphabet,
    Symbol,
    Default
};

class Scanner
{
private:
    std::list<std::string> _tokens;
    status _currentState;
    status _beforeState;

    void scanStr(std::string input) {
        std::string token = "";
        _currentState = Default;
        _beforeState = Default;

        for (char c : input) {
            _currentState = getStatus(c);

            if (_beforeState != Default && _beforeState != _currentState && token != "") {
                _tokens.push_back(token);
                token = "";
                _beforeState = Default;
            }
            if (!isspace(c)) {
                if (_currentState == Symbol) {
                    std::string s(1, c);
                    _tokens.push_back(s);
                }
                else {
                    token += c;
                }
                _beforeState = _currentState;       
            }
        }
        // _tokens.push_back(token);
    }

    status getStatus(char c) {
        if (isalpha(c)) {
            return Alphabet;
        }
        if (isdigit(c) || c == '-' || c == '.') {
            return Number;
        }
        if (isSymbol(c)) {
            return Symbol;
        }
        return Default;
    }

    bool isSymbol(char c)
    {
        return !(isspace(c) || isdigit(c) || isalpha(c));
    }

public:
    Scanner(std::string input) {
        scanStr(input);
    }

    std::string nextToken() {
        if (_tokens.empty()) {
            throw(std::string) "next char doesn't exist.";
        }
        std::string token = _tokens.front();
        _tokens.pop_front();
        return token;
        // return next token.
        // throw exception std::string "next char doesn't exist." if next token not found.
    }
};
#endif