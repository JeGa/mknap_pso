#include "Solver.h"

#include <cstdlib>
#include <ctime>

namespace mknap_pso
{

    Solver::Solver()
    {
        parameters = Parameters::getDefaultParameters();
    }

    Solver::~Solver()
    {

    }

    void Solver::solveProblem(KnapsackProblem *problem)
    {
        currentProblem = problem;

        swarm.initializeSwarm(parameters.getNumberOfParticles());
        initializeParticles();

        currentProblem = 0;
    }

    void Solver::findSolution()
    {
        for (auto i : swarm.getParticles()) {
            // Update the velocity

            // Update the position/solution

            // Update pBest position/solution

            // Update gBest position/solution

        }
    }

    void Solver::initializeParticles()
    {
        for (auto i : swarm.getParticles()) {
            Solution position = getRandomSolution(currentProblem->n);
            Solution velocity = getRandomSolution(currentProblem->n);

            i.setPosition(position);
            i.setVelocity(velocity); // TODO

            // Fitness value / Profit of the solutio/position.
            int profit = calculateProfit(position, currentProblem->profit);
            i.setBestKnownPosition(profit);

            // Check if this solution is better than the global solution.
            if (profit > swarm.getBestGlobalPosition())
                swarm.setBestGlobalPosition(profit);
        }
    }

    int Solver::calculateProfit(Solution solution, Profit profits)
    {
        if (solution.size() != profits.size())
            throw std::invalid_argument("Size of the arguments is not equal.");

        int sum = 0;

        for (unsigned int i = 0; i < solution.size(); ++i)
            sum += (static_cast<int>(solution.at(i)) * profits.at(i));

        return sum;
    }

    Solution Solver::getRandomSolution(int size)
    {
        Solution solution;

        std::srand(std::time(0));

        for (int i = 0; i < size; ++i) {
            int randomVariable = std::rand();
            solution.push_back(static_cast<bool>(randomVariable % 2));
        }

        return solution;
    }

}
