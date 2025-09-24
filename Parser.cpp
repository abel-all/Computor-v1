#include "Parser.hpp"

Parser::Parser() {
}

Parser::Parser(std::string p) : polynome(p){
}

Parser::~Parser() {
}

void Parser::splitTerms() {
    // remove spaces
    polynome.erase(std::remove(polynome.begin(), polynome.end(), ' '), polynome.end());
    std::cout << "the str : " << polynome << std::endl;

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

    std::cout << "term is : " << term << std::endl;

    std::cout << "-----------" << std::endl;
    for (size_t i = 0; i < ls.size(); i++)
        std::cout << "the LS : " << ls[i] << std::endl;
    std::cout << "-----------" << std::endl;
    for (size_t i = 0; i < rs.size(); i++)
        std::cout << "the RS : " << rs[i] << std::endl;
}

// void Parser::matchRegex(std::vector<std::string> &vec, bool isLs) {

//     std::regex numberRe(R"(^[+-]?\d+(\.\d+)?$)");
//     std::regex termRe(R"(^([+-]?)(?:(\d+(?:\.\d+)?)(?:\*)?)?([Xx])(?:\^(\d+))?$)");

//     for (size_t i = 0; i < vec.size(); i++) {
//         // don't contain Term=X
//         if (vec[i].find(term) == std::string::npos) {
//             if (!std::regex_match(vec[i], numberRe)) throw std::string("Parsing Err : " + vec[i]);
//             else std::cout << "Parsed successfuly : " << vec[i] << std::endl;
//         }

//         // contain Term=X
//         else {
//             if (!std::regex_match(vec[i], termRe)) throw std::string("Parsing Err : " + vec[i]);
//             else std::cout << "Parsed successfuly : " << vec[i] << std::endl;
//         }

//         // detect the a, b and c && polynome degree
//         for (size_t j = 0; i < vec[i].size(); j++) {
            
//         }
//     }
// }

void Parser::parseTerms() {

    // merge LS and RS and normalize
    normalizedPoly = ls;

    for (size_t i = 0; i < rs.size(); i++) {
        if (rs[i][0] == '-' || rs[i][0] == '+') {
            std::string ff = rs[i].erase(0);
            std::cout << "the string is : " << ff << "and rs[i] is : " << rs[i] << std::endl;
            if (rs[i][0] == '-') normalizedPoly.push_back("+o" + ff);
            else normalizedPoly.push_back("-" + ff);
        }
        else {
            normalizedPoly.push_back("-" + rs[i]);
        }
    }

    std::cout << "-----------" << std::endl;
    for (size_t i = 0; i < normalizedPoly.size(); i++)
        std::cout << "the merged vec elem inedx " << i << " : " << normalizedPoly[i] << std::endl;
    // parse LS
    // matchRegex(ls, true);

    // // parse RS
    // matchRegex(rs, false);
}