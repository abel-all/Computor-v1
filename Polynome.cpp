#include "Polynome.hpp"

Polynome::polynome() {

}

Polynome::~polynome() {

}

void Polynome::setCoefficients(double CoefA, double CoefB, double CoefC) {
    this->a = CoefA;
    this->b = Coefb;
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

std::vector<std::string> Polynome::getNormalizedPoly() {
    return this->normalizedPoly;
}
