#include "Parser.h"

#include <stdexcept>
#include <string>
#include <sstream>
#include <iostream>

namespace mknap_pso
{

    void Parser::parseFile(const std::string &file)
    {
        in.open(file);

        if (in.fail())
            throw std::invalid_argument("Could not open file.");

        std::cerr << "Parsing " << file << std::endl;

        problems.clear();

        parseFirstLineOfFile();

        for (int i = 0; i < K; ++i) {
            auto p = std::make_shared<KnapsackProblem>();

            parseFirstLineOfProblem(p.get());
            parseProvitOfProblem(p.get());
            parseConstraintsOfProblem(p.get());
            parseCapacityOfProblem(p.get());

            problems.push_back(p);
        }

        in.close();
    }

    void Parser::parseFirstLineOfFile()
    {
        in >> K;
    }

    void Parser::parseFirstLineOfProblem(KnapsackProblem *p)
    {
        in >> p->n;
        in >> p->m;
        in >> p->solution;
    }

    void Parser::parseProvitOfProblem(KnapsackProblem* p)
    {
        for (int i = 0; i < p->n; ++i) {
            int profitValue;

            in >> profitValue;
            p->profit.push_back(profitValue);
        }
    }

    void Parser::parseConstraintsOfProblem(KnapsackProblem* p)
    {
        for (int i = 0; i < p->m; ++i) {
            ConstraintValues constraintValues;
            p->constraint.push_back(constraintValues);

            for (int j = 0; j < p->n; ++j) {
                int constraintValue;

                in >> constraintValue;
                p->constraint.at(i).push_back(constraintValue);
            }
        }
    }

    void Parser::parseCapacityOfProblem(KnapsackProblem* p)
    {
        for (int i = 0; i < p->m; ++i) {
            int capacity;

            in >> capacity;
            p->capacity.push_back(capacity);
        }
    }

    std::vector<std::shared_ptr<KnapsackProblem>> Parser::getProblems()
    {
        return problems;
    }

    std::vector<std::shared_ptr<KnapsackProblem>> &Parser::getProblemsReference()
    {
        return problems;
    }

    std::string Parser::toString()
    {
        std::stringstream sstr;

        sstr << "Nr. of Problems: " << K << std::endl;

        for (auto &i : problems)
            sstr << i->toString();

        sstr << std::endl;

        return sstr.str();
    }

}
