#include "Parser.h"

#include <iostream>

#define FILE_NAME "../res/mknapcb1.txt"

int main(int argc, char **argv)
{
    mknap_pso::Parser parser;

    parser.parseFile(FILE_NAME);

    std::cout << parser.toString();

    return 0;
}
