#include "Solver.h"

#include <random>
#include <iostream>
#include <stdexcept>

#include <cstdlib>

// Faster with abs than with exp
#define sig(x) (1 / (1 + abs(-x)))

namespace mknap_pso
{

    Solver::Solver() : engine(rd())
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

        for (int i = 0; i < parameters.getIterations(); ++i)
            findSolution();

        int finalSolution = swarm.getBestValue();

        std::cout << "==============================\n";
        std::cout << "Solution value: " << finalSolution << std::endl;
        std::cout << "==============================\n";

        currentProblem = 0;
    }

    void Solver::initializeParticles()
    {
        for (auto i : swarm.getParticles()) {
            std::cin.ignore();

            Solution position = getRandomSolution();

            std::cin.ignore();

            Velocity velocity = getRandomVelocity();

            i.setPosition(position);
            i.setVelocity(velocity);

            // Fitness value / Profit of the solution/position.
            int profit = calculateProfit(position);
            i.setBestPositionAndValue(position, profit);

            // Check if this solution is better than the global solution.
            if (profit > swarm.getBestValue())
                swarm.setBestPositionAndValue(position, profit);

            /*for (auto i : position) {
                std::cout << i;
            }*/
            std::cout << "\n====\n";
        }
    }

    void Solver::findSolution()
    {
        for (auto i : swarm.getParticles()) {
            std::cin.ignore();

            int randomParticleNumber = getRandomIntegerValue(0, 1);
            int randomGlobalNumber = getRandomIntegerValue(0, 1);

            std::cin.ignore();

            Velocity newVelocity;
            Solution newPosition;

            /**
             * Iterate through all dimensions of a Solution/position
             * to calculate the new velocity and update the position.
             *
             * j = dimension
             */
            for (int j = 0; j < currentProblem->n; ++j) {

                int currentPositionD = i.getPosition().at(j);
                double currentVelocityD = i.getVelocity().at(j);

                int pBestD = i.getBestPosition().at(j);
                int gBestD = swarm.getBestPosition().at(j);

                // TODO: At parameter omega (inertia weight)
                double newVelocityD = currentVelocityD +
                                      parameters.getConstant1() * randomParticleNumber * (pBestD - currentPositionD) +
                                      parameters.getConstant2() * randomGlobalNumber * (gBestD - currentPositionD);

                // TODO: Limit velocity with Vmax

                // Logistic transformation
                newVelocityD = sig(newVelocityD);

                // Calculate new position
                // TODO: Updated formular from Qi
                double randomValue = getRandomDoubleValue(0.0, 1.0);
                int newPositionD;
                if (randomValue < newVelocityD)
                    newPositionD = 1;
                else
                    newPositionD = 0;

                newVelocity.push_back(newVelocityD);
                newPosition.push_back(newPositionD);
            }

            i.setVelocity(newVelocity);
            i.setPosition(newPosition);

            // Update pBest and gBest position/solution
            int pBestTmp = calculateProfit(i.getPosition());

            if (pBestTmp > i.getBestValue()) {
                i.setBestPositionAndValue(i.getPosition(), pBestTmp);

                if (pBestTmp > swarm.getBestValue())
                    swarm.setBestPositionAndValue(i.getPosition(), pBestTmp);
            }
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

        for (int i = 0; i < currentProblem->n; ++i) {
            int randomVariable = getRandomIntegerValue(0, 1);

            std::cout << randomVariable;

            solution.push_back(static_cast<bool>(randomVariable));
        }

        return solution;
    }

    Velocity Solver::getRandomVelocity()
    {
        Velocity velocity;

        for (int i = 0; i < currentProblem->n; ++i) {
            int randomVariable = getRandomDoubleValue(0.0, 1.0);

            std::cout << randomVariable;

            velocity.push_back(randomVariable);
        }

        return velocity;
    }

    int Solver::getRandomIntegerValue(int lowerBound, int upperBound)
    {
        /*std::random_device rd;

        std::default_random_engine engine(rd());*/
        std::uniform_int_distribution<int> uniform_dist(lowerBound, upperBound);

        return 0;//uniform_dist(engine);
    }

    double Solver::getRandomDoubleValue(double lowerBound, double upperBound)
    {
        /*std::random_device rd;

        std::default_random_engine engine(rd());*/
        std::uniform_real_distribution<double> uniform_dist(lowerBound, upperBound);

        return 0;//uniform_dist(engine);
    }

}
