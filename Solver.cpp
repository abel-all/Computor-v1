#include "Solver.hpp"

Solver::Solver(): x1(0), x2(0), typeOfSolution(""){
}

Solver::~Solver() {
}

void Solver::solveAndPrint(Polynome &polynome) {
    std::cout << "============" << std::endl;
    std::cout << "A is :" << polynome.getCoefficientA() << std::endl;
    std::cout << "B is :" << polynome.getCoefficientB() << std::endl;
    std::cout << "C is :" << polynome.getCoefficientC() << std::endl;

    // solve the polynome:
    double a = polynome.getCoefficientA();
    double b = polynome.getCoefficientB();
    double c = polynome.getCoefficientC();

    if (a != 0) {

        double discriminant = std::pow(b, 2) - 4*a*c;
        double discriminantSqrt = std::sqrt(discriminant);
        std::cout << "============" << std::endl;
        std::cout << "discriminant is :" << discriminant << std::endl;

        if (discriminant > 0) {
            this->x1 = (b+discriminantSqrt)*-1/(2*a);
            this->x2 = (discriminantSqrt-b)/(2*a);
            this->typeOfSolution = "Bigger than zero";
            std::cout << "============" << std::endl;
            std::cout << "X1 is :" << this->x1 << std::endl;
            std::cout << "X2 is :" << this->x2 << std::endl;
        } else if (discriminant == 0) {
            this->x1 = -b/(2*a);
            this->typeOfSolution = "Equal to zero";
            std::cout << "============" << std::endl;
            std::cout << "X1 is :" << this->x1 << std::endl;
        } else {
            discriminantSqrt = std::sqrt(std::abs(discriminant));
            // using namespace std::literals::complex_literals;
            std::complex<double> z1((-b/(2*a)), (discriminantSqrt/(2*a))*-1);
            std::complex<double> z2((-b/(2*a)), (discriminantSqrt/(2*a)));
            this->typeOfSolution = "Younger than zero";
            std::cout << "============" << std::endl;
            std::cout << "Z1 is :" << z1 << std::endl;
            std::cout << "Z2 is :" << z2 << std::endl;
        }

    } else {

    }

}