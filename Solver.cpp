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

    // print the polynomial degree:
    size_t degree = polynome.getDegree();

    if (degree > 2) {
        std::cout << "Polynomial degree: " << degree << std::endl;
        std::cout << "The polynomial degree is strictly greater than 2, I can't solve." << std::endl;
        return;
    }


    // std::cout << "Polynomial degree: " << polynome.getDegree() << std::endl;

    // solve the polynome:

    if (a != 0) {

        std::cout << "Polynomial degree: " << degree << std::endl;

        double discriminant = std::pow(b, 2) - 4*a*c;
        double discriminantSqrt = std::sqrt(discriminant);
        double denominator = 2 * a;

        if (discriminant > 0) {
            this->x1 = (b+discriminantSqrt)*-1/denominator;
            this->x2 = (discriminantSqrt-b)/denominator;
            std::cout << "Discriminant is strictly positive, the two solutions are:" << std::endl;
            std::cout << this->x1 << std::endl;
            std::cout << this->x2 << std::endl;
        } else if (discriminant == 0) {
            this->x1 = -b/denominator;
            std::cout << "The solution is: " << std::endl;
            std::cout << this->x1 << std::endl;
        } else {
            discriminantSqrt = std::sqrt(std::abs(discriminant));
            long long gcd_one = gcd_ll(b, denominator);
            long long gcd_two = gcd_ll(discriminantSqrt, denominator);
            
            std::cout << "Discriminant is strictly negative, the two complex solutions are:" << std::endl;
            if (denominator < 0) {
                std::cout << -(b/gcd_one) << "/" << (denominator/gcd_one) 
                << " - " << (discriminantSqrt/gcd_two) << "i" << "/" << std::abs(denominator/gcd_two) << std::endl;
                std::cout << -(b/gcd_one) << "/" << (denominator/gcd_one)  
                << " + " << (discriminantSqrt/gcd_two) << "i" << "/" << std::abs(denominator/gcd_two) << std::endl;
            } else {
                std::cout << -(b/gcd_one) << "/" << (denominator/gcd_one) 
                << " + " << (discriminantSqrt/gcd_two) << "i" << "/" << (denominator/gcd_two) << std::endl;
                std::cout << -(b/gcd_one) << "/" << (denominator/gcd_one)  
                << " - " << (discriminantSqrt/gcd_two) << "i" << "/" << (denominator/gcd_two) << std::endl;
            }
        }

    } else {
        if (b != 0) {

            std::cout << "Polynomial degree: " << degree << std::endl;
            double x = -c/b;
            std::cout << "The solution is: " << std::endl;
            std::cout << x << std::endl;


        } else {
            if (c == 0) {
                std::cout << "Any real number is a solution." << std::endl;
            } else {
                std::cout << "No solution." << std::endl;
            }
        }

    }

}