#include "Solver.hpp"

Solver::Solver(): x1(0), x2(0), typeOfSolution(""){
}

Solver::~Solver() {
}

long long gcd_ll(long long x, long long y) {
    return std::gcd(std::llabs(x), std::llabs(y));
}

void Solver::solveAndPrint(Polynome &polynome) {

    double a = polynome.getCoefficientA();
    double b = polynome.getCoefficientB();
    double c = polynome.getCoefficientC();

    // print the reduced form:
    std::cout << "Reduced form: " ;
    std::cout << polynome.getReducedForm() << std::endl;


    // std::cout << "Polynomial degree: " << polynome.getDegree() << std::endl;

    // solve the polynome:

    if (a != 0) {

        double discriminant = std::pow(b, 2) - 4*a*c;
        double discriminantSqrt = std::sqrt(discriminant);
        double denominator = 2 * a;

        if (discriminant > 0) {
            this->x1 = (b+discriminantSqrt)*-1/denominator;
            this->x2 = (discriminantSqrt-b)/denominator;
            this->typeOfSolution = "Bigger than zero";
            std::cout << "============" << std::endl;
            std::cout << "X1 is :" << this->x1 << std::endl;
            std::cout << "X2 is :" << this->x2 << std::endl;
        } else if (discriminant == 0) {
            this->x1 = -b/denominator;
            this->typeOfSolution = "Equal to zero";
            std::cout << "============" << std::endl;
            std::cout << "X1 is :" << this->x1 << std::endl;
        } else {
            discriminantSqrt = std::sqrt(std::abs(discriminant));
            long long gcd_one = gcd_ll(b, denominator);
            long long gcd_two = gcd_ll(discriminantSqrt, denominator);
            
            this->typeOfSolution = "Younger than zero";
            std::cout << "============" << std::endl;
            if (denominator < 0) {
                std::cout << "Z1 is :" << -(b/gcd_one) << "/" << (denominator/gcd_one) 
                << " - " << (discriminantSqrt/gcd_two) << "i" << "/" << std::abs(denominator/gcd_two) << std::endl;
                std::cout << "Z2 is :" << -(b/gcd_one) << "/" << (denominator/gcd_one)  
                << " + " << (discriminantSqrt/gcd_two) << "i" << "/" << std::abs(denominator/gcd_two) << std::endl;
            } else {
                std::cout << "Z1 is :" << -(b/gcd_one) << "/" << (denominator/gcd_one) 
                << " + " << (discriminantSqrt/gcd_two) << "i" << "/" << (denominator/gcd_two) << std::endl;
                std::cout << "Z2 is :" << -(b/gcd_one) << "/" << (denominator/gcd_one)  
                << " - " << (discriminantSqrt/gcd_two) << "i" << "/" << (denominator/gcd_two) << std::endl;
            }
        }

    } else {
        if (b != 0) {

            double x = -c/b;
            std::cout << "============" << std::endl;
            std::cout << "x is :" << x << std::endl;


        } else {
            if (c == 0) {
                std::cout << "============" << std::endl;
                std::cout << "Any real number is a solution." << std::endl;
            } else {
                std::cout << "============" << std::endl;
                std::cout << "No solution." << std::endl;
            }
        }

    }

}