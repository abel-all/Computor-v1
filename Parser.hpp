#pragma once
#ifndef __PARSER_H__
#define __PARSER_H__

#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <regex>

class Parser {
    private:
        std::string                 polynome;
        char                        term;
        std::vector<std::string>    rs;
        std::vector<std::string>    ls;
        std::vector<std::string>    normalizedPoly;
        std::map<int, double>       termExpByCoef;
        double                      a;
        double                      b;
        double                      c;
    public:
        Parser();
        Parser(std::string p);
        ~Parser();
        void splitTerms();
        void parseTerms();
        void matchRegex(std::vector<std::string> &vec);
};

#endif