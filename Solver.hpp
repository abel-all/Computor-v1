#pragma once

#include <string>
#include <iostream>
#include <cmath>
#include <complex>
#include <numeric>
#include "Polynome.hpp"

class Solver {
    private:
        double                  x1;
        double                  x2;
        std::string             typeOfSolution;
        std::complex<double>    z1;
        std::complex<double>    z2;
    public:
        Solver();
        ~Solver();
        void solveAndPrint(Polynome &polynome);
};
