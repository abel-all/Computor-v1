#include "Parser.hpp"

Parser::Parser() {
}

Parser::Parser(std::string p) : polynome(p), a(0), b(0), c(0){
}

Parser::~Parser() {
}

void Parser::splitTerms() {
    // remove spaces
    polynome.erase(std::remove(polynome.begin(), polynome.end(), ' '), polynome.end());
    std::cout << "the polynome : " << polynome << std::endl;

    // tokenize the RS and LS
    size_t polynomeSize = polynome.size();
    size_t j = 0;
    size_t i = 0;
    bool isTerm = false;
    size_t equalPos = polynome.find('=');
    if (equalPos == std::string::npos) return;
    for (; i < equalPos; i++) {
        if ((polynome[i] == '-' || polynome[i] == '+') && i) {
            ls.push_back(polynome.substr(j, i - j));
            j = i;
        }

        // define Term && polynome degree
        if (!isTerm && std::isalpha(static_cast<unsigned char>(polynome[i]))) {
            term = polynome[i];
            isTerm = true;
        }
    }
    ls.push_back(polynome.substr(j, i - j));

    j = equalPos + 1;
    i = equalPos + 1;

    for (; i < polynomeSize; i++) {
        if ((polynome[i] == '-' || polynome[i] == '+') && i != (equalPos + 1)) {
            rs.push_back(polynome.substr(j, i - j));
            j = i;
        }

        // define Term && polynome degree
        if (!isTerm && std::isalpha(static_cast<unsigned char>(polynome[i]))) {
            term = polynome[i];
            isTerm = true;
        }
    }
    rs.push_back(polynome.substr(j, i - j));
}

void Parser::matchRegex(std::vector<std::string> &vec) {

    std::regex numberRe(R"(^[+-]?\d+(\.\d+)?$)");
    std::string pattern = std::string("(^([+-]?)(?:(\\d+(?:\\.\\d+)?)(?:\\*)?)?([") + term + std::string("])(?:\\^(\\d+))?$)");
    std::regex termRe(pattern);

    for (size_t i = 0; i < vec.size(); i++) {

        size_t termPos = vec[i].find(term);
        std::string coefOfTermStr;

        // don't contain Term=X
        if (termPos == std::string::npos) {
            if (!std::regex_match(vec[i], numberRe)) throw std::runtime_error("Parsing Err : " + vec[i]);
            c += std::stod(vec[i]);
        }

        // contain Term=X
        else {
            if (!std::regex_match(vec[i], termRe)) throw std::runtime_error("Parsing Err : " + vec[i]);
            
            if (vec[i][termPos - 1] == '-')
                coefOfTermStr = "-1";
            else if (vec[i][termPos - 1] == '+')
                coefOfTermStr = "+1";
            else
                coefOfTermStr = vec[i].substr(0, termPos);

            double coefOfTerm = std::stod(coefOfTermStr);

            if (vec[i][termPos + 1] == '^') {
                int exponent = std::stoi(vec[i].substr(termPos + 2));
                if (exponent > 2) throw std::runtime_error("Invalid input: degree > 2");
                if (exponent == 0) c += coefOfTerm;
                else termExpByCoef[exponent] += coefOfTerm;
            }
            else termExpByCoef[1] += coefOfTerm;
            
        }
    }
}

void Parser::parseTerms() {

    // merge LS and RS and normalize
    normalizedPoly = ls;
    for (size_t i = 0; i < rs.size(); i++) {
        if (rs[i][0] == '-' || rs[i][0] == '+') {
            if (rs[i][0] == '-') normalizedPoly.push_back("+" + rs[i].erase(0, 1));
            else normalizedPoly.push_back("-" + rs[i].erase(0, 1));
        }
        else {
            normalizedPoly.push_back("-" + rs[i]);
        }
    }

    // parse normalizedPoly and determine a,b,c and poly degree
    matchRegex(normalizedPoly);



    std::cout << "the normalizedPoly : ";
    for (size_t i = 0; i < normalizedPoly.size(); i++)
        std::cout << normalizedPoly[i];
    std::cout << "=0" << std::endl; 
    std::cout << "============" << std::endl;
    std::cout << "a is :" << c << std::endl;
    std::cout << "============" << std::endl;
    for (const auto& pair : termExpByCoef) {
        std::cout << "Key: " << pair.first << ", Value: " << pair.second << std::endl;
    }
}