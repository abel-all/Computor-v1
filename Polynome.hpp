#pragma once

#include <string>
#include <iostream>
#include <algorithm>
#include <vector>

class Polynome {
    private:
        std::vector<std::string>    normalizedPoly;
        double                      a;
        double                      b;
        double                      c;
    public:
        Polynome();
        ~Polynome();
        void setCoefficients(double a, double b, double c);
        double getCoefficientA() const;
        double getCoefficientB() const;
        double getCoefficientC() const;
        void setNormalizedPolyValue(std::string str);
        void setVecToNormalizedPoly(std::vector<std::string> vec);
        std::vector<std::string> &getNormalizedPoly();
};
