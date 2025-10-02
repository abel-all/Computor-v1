#pragma once

#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <regex>
#include "Polynome.hpp"

class Parser {
    private:
        std::string                 polynome;
        char                        term;
        std::vector<std::string>    rs;
        std::vector<std::string>    ls;
        std::map<int, double>       termExpByCoef;
    public:
        Parser();
        Parser(std::string p);
        ~Parser();
        void splitTerms();
        void parseTerms(Polynome &poly);
        void matchRegexAndDefinePolyDegree(std::vector<std::string> &vec);
};
