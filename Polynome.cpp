#include "Polynome.hpp"

Polynome::Polynome() {

}

Polynome::~Polynome() {

}

void Polynome::setCoefficients(double CoefA, double CoefB, double CoefC) {
    this->a = CoefA;
    this->b = CoefB;
    this->c = CoefC;
}

double Polynome::getCoefficientA() const {
    return a;
}

double Polynome::getCoefficientB() const {
    return b;
}

double Polynome::getCoefficientC() const {
    return c;
}

void Polynome::setNormalizedPolyValue(std::string str) {
    this->normalizedPoly.push_back(str);
}

void Polynome::setVecToNormalizedPoly(std::vector<std::string> vec) {
    this->normalizedPoly = vec;
}

std::vector<std::string> &Polynome::getNormalizedPoly() {
    return this->normalizedPoly;
}

std::string Polynome::getReducedForm() const {
    std::string reducedForm;
    std::map<size_t, std::string> termMap;
    std::map<int, double> coefByDegree;
    coefByDegree[0] = this->c;
    coefByDegree[1] = this->b;
    coefByDegree[2] = this->a;

    for (size_t i = 0; i < normalizedPoly.size(); i++) {

        std::cout << "normalizedPoly[" << i << "] = " << normalizedPoly[i] << std::endl;
        size_t xPos = normalizedPoly[i].find("X");
        if (xPos != std::string::npos) {
            size_t degree = std::stoi(normalizedPoly[i].substr(xPos + 2));
            termMap[degree] = normalizedPoly[i].substr(xPos);
        }
        // reducedForm += normalizedPoly[i];
        // if (i != normalizedPoly.size() - 1)
        //     reducedForm += " ";
    }

    for (int deg = 2; deg >= 0; deg--) {
        if (termMap.find(deg) != termMap.end()) {
            if (!reducedForm.empty() && termMap[deg][0] != '-') {
                reducedForm += " + ";
            }
            reducedForm += std::to_string(coefByDegree[deg]) + termMap[deg];
        }
    }
    reducedForm += " = 0";
    return reducedForm;
}
