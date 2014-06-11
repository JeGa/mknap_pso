#include "Solver.h"
#include "Parser.h"

#include <iostream>

#define FILE_NAME "../res/mknapcb1.txt"

int main(int argc, char **argv)
{
    mknap_pso::Solver solver;

    mknap_pso::Parser parser;
    parser.parseFile(FILE_NAME);

    std::cout << "Starting pso\n";

    for (auto &i : parser.getProblems()) {
        solver.solveProblem(i.get());
    }

    return 0;
}
