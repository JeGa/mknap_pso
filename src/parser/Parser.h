/**
 * This class can parse files formatted like mknapcb1.txt.
 *
 * File format of the mknapcb1.txt file from the OR library:
 * (From http://people.brunel.ac.uk/~mastjjb/jeb/orlib/mknapinfo.html)
 *
    number of test problems (K)
    then for each test problem k (k=1,...,K) in turn:
    number of variables (n), number of constraints (m), optimal
    solution value (zero if unavailable)
    the coefficients p(j); j=1,...,n
    for each constraint i (i=1,...,m): the coefficients r(i,j); j=1,...,n
    the constraint right-hand sides b(i); i=1,...,m
 *
 * So the calls to parse a complete file are:
 * - parseFirstLineOfFile() => K
 * - parseFirstLineOfProblem() => n, m, solution
 * - parseProvitOfProblem() => p(j)
 * - parseConstraintsOfProblem() => r(i, j)
 * - parseCapacityOfProblem() => b(i)
 */

#ifndef PARSER_H
#define PARSER_H

#include "KnapsackProblem.h"

#include <fstream>
#include <vector>
#include <memory>

namespace mknap_pso
{

    class Parser
    {
        private:
            void parseFirstLineOfFile();
            void parseFirstLineOfProblem(KnapsackProblem *p);
            void parseProvitOfProblem(KnapsackProblem *p);
            void parseConstraintsOfProblem(KnapsackProblem *p);
            void parseCapacityOfProblem(KnapsackProblem *p);

            std::ifstream in;

            int K = 0;
            std::vector<std::shared_ptr<KnapsackProblem>> problems;

        public:
            Parser() {}
            ~Parser() {}

            void parseFile(const std::string &file);
            std::string toString();

            std::vector<std::shared_ptr<KnapsackProblem>> getProblems();
            std::vector<std::shared_ptr<KnapsackProblem>> &getProblemsReference();
    };

}

#endif
