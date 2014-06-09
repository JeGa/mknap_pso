#include "Solver.h"

#include <random>
#include <iostream>
#include <stdexcept>

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

    void Solver::initializeParticles()
    {
        for (auto i : swarm.getParticles()) {
            Solution position = getRandomSolution();
            Solution velocity = getRandomSolution();

            i.setPosition(position);
            i.setVelocity(velocity); // TODO

            // Fitness value / Profit of the solution/position.
            int profit = calculateProfit(position);
            i.setBestKnownPosition(profit);

            // Check if this solution is better than the global solution.
            if (profit > swarm.getBestGlobalPosition())
                swarm.setBestGlobalPosition(profit);

            /*for (auto i : position) {
                std::cout << i;
            }*/
            std::cout << "\n====\n";
        }

        std::cerr << std::endl << "GBEST: " << swarm.getBestGlobalPosition() << std::endl;
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

    int Solver::calculateProfit(Solution solution)
    {
        if (solution.size() != currentProblem->profit.size())
            throw std::invalid_argument("Size of the arguments is not equal.");

        int sum = 0;

        for (unsigned int i = 0; i < solution.size(); ++i)
            sum += (static_cast<int>(solution.at(i)) *currentProblem->profit.at(i));

        return sum;
    }

    Solution Solver::getRandomSolution()
    {
        Solution solution;

        std::random_device rd;

        std::default_random_engine engine(rd());
        std::uniform_int_distribution<int> uniform_dist(0, 5);

        for (int i = 0; i < currentProblem->n; ++i) {
            int randomVariable = uniform_dist(engine);

            std::cout << randomVariable;

            solution.push_back(static_cast<bool>(randomVariable));
        }

        return solution;
    }

}
