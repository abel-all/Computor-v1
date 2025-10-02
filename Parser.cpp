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
    std::cout << "the polynome : " << this->polynome << std::endl;

    // tokenize the RS and LS
    size_t polynomeSize = this->polynome.size();
    size_t j = 0;
    size_t i = 0;
    bool isTerm = false;
    size_t equalPos = this->polynome.find('=');
    if (equalPos == std::string::npos) throw std::runtime_error("Parsing Err : Equal not exist");
    for (; i < equalPos; i++) {
        if ((this->polynome[i] == '-' || this->polynome[i] == '+') && i) {
            ls.push_back(this->polynome.substr(j, i - j));
            j = i;
        }

        // define Term && polynome degree
        if (!isTerm && std::isalpha(static_cast<unsigned char>(this->polynome[i]))) {
            term = this->polynome[i];
            isTerm = true;
        }
    }
    ls.push_back(this->polynome.substr(j, i - j));

    j = equalPos + 1;
    i = equalPos + 1;

    for (; i < polynomeSize; i++) {
        if ((this->polynome[i] == '-' || this->polynome[i] == '+') && i != (equalPos + 1)) {
            rs.push_back(this->polynome.substr(j, i - j));
            j = i;
        }

        // define Term && polynome degree
        if (!isTerm && std::isalpha(static_cast<unsigned char>(this->polynome[i]))) {
            term = this->polynome[i];
            isTerm = true;
        }
    }
    rs.push_back(this->polynome.substr(j, i - j));
}

void Parser::matchRegexAndDefinePolyDegree(std::vector<std::string> &vec) {

    std::regex numberRe(R"(^[+-]?\d+(\.\d+)?$)");
    std::string pattern = std::string("(^([+-]?)(?:(\\d+(?:\\.\\d+)?)(?:\\*)?)?([") + this->term + std::string("])(?:\\^(\\d+))?$)");
    std::regex termRe(pattern);

    for (size_t i = 0; i < vec.size(); i++) {

        size_t termPos = vec[i].find(this->term);
        std::string coefOfTermStr;

        // don't contain Term=X
        if (termPos == std::string::npos) {
            if (!std::regex_match(vec[i], numberRe)) throw std::runtime_error("Parsing Err : " + vec[i]);
            this->termExpByCoef[0] += std::stod(vec[i]);
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
                this->termExpByCoef[exponent] += coefOfTerm;
            }
            else this->termExpByCoef[1] += coefOfTerm;
            
        }
    }

}

void Parser::parseTerms(Polynome &poly) {
    
    // merge LS and RS and normalize
    poly.setVecToNormalizedPoly(ls);
    for (size_t i = 0; i < rs.size(); i++) {
        if (rs[i][0] == '-' || rs[i][0] == '+') {
            if (rs[i][0] == '-') poly.setNormalizedPolyValue("+" + rs[i].erase(0, 1));
            else poly.setNormalizedPolyValue("-" + rs[i].erase(0, 1));
        }
        else {
            poly.setNormalizedPolyValue("-" + rs[i]);
        }
    }
    
    // parse normalizedPoly and determine a,b,c and poly degree
    matchRegexAndDefinePolyDegree(poly.getNormalizedPoly());
    
    poly.setCoefficients(this->termExpByCoef[2], this->termExpByCoef[1], this->termExpByCoef[0]);

    std::cout << "the normalizedPoly : ";
    std::vector<std::string> normalizedPoly = poly.getNormalizedPoly();
    for (size_t i = 0; i < normalizedPoly.size(); i++)
        std::cout << normalizedPoly[i];
    std::cout << "=0" << std::endl; 
}