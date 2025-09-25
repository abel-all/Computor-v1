#pragma once
#ifndef __POLYNOME_H__
#define __POLYNOME_H__

#include <string>
#include <iostream>
#include <algorithm>
#include <vector>

class polynome {
    private:
        std::vector<std::string>    normalizedPoly;
        double                      a;
        double                      b;
        double                      c;
    public:
        polynome();
        ~polynome();
        void setCoefficients(double a, double b, double c);
        double getCoefficientA() const;
        double getCoefficientB() const;
        double getCoefficientC() const;
        void setNormalizedPolyValue(std::string str);
        void setVecToNormalizedPoly(std::vector<std::string> vec);
        std::vector<std::string> getNormalizedPoly();
};

#endif