#include "Parser.hpp"

int main(int ac, char **av) {
    
    if (ac < 2) return (std::cerr << "Not Arg Enough!" << std::endl, 1);

    Parser parser(av[1]);

    try {
        parser.splitTerms();
        parser.parseTerms();
    } catch (const std::string& errorMessage) {
        std::cerr << errorMessage << std::endl;
    }

}