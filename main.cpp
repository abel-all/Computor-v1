#include "Parser.hpp"
#include "Polynome.hpp"
#include "Solver.hpp"

int main(int ac, char **av) {
    
    if (ac < 2) return (std::cerr << "Not Arg Enough!" << std::endl, 1);

    Parser parser(av[1]);
    Polynome poly;
    Solver solver;

    try {
        parser.splitTerms();
        parser.parseTerms(poly);
        solver.solveAndPrint(poly);

    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

}