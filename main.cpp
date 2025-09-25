#include "Parser.hpp"

int main(int ac, char **av) {
    
    if (ac < 2) return (std::cerr << "Not Arg Enough!" << std::endl, 1);

    Parser parser(av[1]);

    try {
        parser.splitTerms();
        parser.parseTerms();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

}