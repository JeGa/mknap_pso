#include "Solver.h"

#include <iostream>
#include <stdexcept>

#include <cstdlib>
#include <ctime>
#include <cmath>

namespace mknap_pso
{

    Solver::Solver()
    {
        parameters = Parameters::getDefaultParameters();
        std::srand(std::time(0));
    }

    Solver::~Solver()
    {
    }

    void Solver::setParameters(Parameters parameters)
    {
        this->parameters = parameters;
    }

    void Solver::startSolveProblem(std::shared_ptr<KnapsackProblem> problem)
    {
        currentProblem = problem;

        swarm.initializeSwarm(parameters.getNumberOfParticles());
        initializeParticles();
    }

    int Solver::solveProblemIteration()
    {
        if (currentProblem == 0)
            throw std::domain_error("Call startSolveProblem() first.");

        findSolution();

        return swarm.getBestValue();
    }

    int Solver::stopSolveProblem()
    {
        if (currentProblem == 0)
            throw std::domain_error("Call startSolveProblem() first.");

        currentProblem = 0;

        return swarm.getBestValue();
    }

    void Solver::solveProblem(std::shared_ptr<KnapsackProblem> problem)
    {
        currentProblem = problem;

        std::cout << "==============================\n";
        std::cout << "Solving problem: " << std::endl;
        std::cout << "Nr. of elements: " << currentProblem->n << std::endl;
        std::cout << "Nr. of constraints: " << currentProblem->m << std::endl;
        std::cout << "==============================\n";

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
        // Initialize the swarms best position with the lowest value.

        for (auto &i : swarm.getParticles()) {
            Solution position = getRandomSolution();
            Velocity velocity = getRandomVelocity();

            i.setPosition(position);
            i.setVelocity(velocity);

            // Fitness value / Profit of the solution/position.
            int profit = calculateProfit(position);
            profit -= calculatePenalty(position, profit);

            i.setBestPositionAndValue(position, profit);

            // Check if this solution is better than the global solution.
            if (!swarm.isGBestInitialized())
                swarm.setBestPositionAndValue(position, profit);
            else if (profit > swarm.getBestValue())
                swarm.setBestPositionAndValue(position, profit);
        }
    }

    void Solver::findSolution()
    {
        for (auto &i : swarm.getParticles()) {
            int randomParticleNumber = getRandomIntegerValue(0, 1);
            int randomGlobalNumber = getRandomIntegerValue(0, 1);

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

                double newVelocityD = parameters.getInertiaWeight() * currentVelocityD +
                                      parameters.getConstant1() * randomParticleNumber * (pBestD - currentPositionD) +
                                      parameters.getConstant2() * randomGlobalNumber * (gBestD - currentPositionD);

                if (newVelocityD > parameters.getVMax())
                    newVelocityD = parameters.getVMax();

                // Logistic transformation
                //newVelocityD = 1.0 / (1.0 + exp(-newVelocityD));
                newVelocityD = newVelocityD / (1.0 + abs(newVelocityD));

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

            int pBestTmp = calculateProfit(i.getPosition());
            pBestTmp -= calculatePenalty(i.getPosition(), pBestTmp);

            // Update pBest and gBest position/solution
            if (pBestTmp > i.getBestValue()) {
                i.setBestPositionAndValue(i.getPosition(), pBestTmp);

                if (pBestTmp > swarm.getBestValue())
                    swarm.setBestPositionAndValue(i.getPosition(), pBestTmp);
            }
        }
    }

    int Solver::calculateProfit(Solution &solution)
    {
        if (solution.size() != currentProblem->profit.size())
            throw std::invalid_argument("Size of the arguments is not equal.");

        int sum = 0;

        for (unsigned int i = 0; i < solution.size(); ++i)
            sum += (static_cast<int>(solution.at(i)) * currentProblem->profit.at(i));

        return sum;
    }

    int Solver::calculatePenalty(Solution &newPosition, int pBestTmp)
    {
        int penaltyValue = 0;

        // Penalty function if constraint is violated
        for (int i = 0; i < currentProblem->m; ++i) {

            // Check constraint i
            int dist = checkConstraint(newPosition, i);

            if (dist) {
                // Constraint violated

                // Get total of all weights (TW)
                int diff = std::min(currentProblem->capacity.at(i),
                                    abs(getTotalOfAllWeights(i) - currentProblem->capacity.at(i)));

                // Penalty function
                int penalty = (int) (pBestTmp * (((double) dist) / (double) diff));

                // Sum up with penalty function
                penaltyValue += penalty;
            }
        }

        return penaltyValue;
    }

    int Solver::checkConstraint(Solution &position, int index_m)
    {
        int constraintValue = getConstraintValue(position, index_m);
        int capacity = currentProblem->capacity.at(index_m);

        if (constraintValue > capacity)
            return constraintValue - capacity;
        return 0;
    }

    int Solver::getConstraintValue(Solution &position, int index_m)
    {
        int sum = 0;

        for (int i = 0; i < currentProblem->n; ++i)
            sum += static_cast<int>(position.at(i)) * currentProblem->constraint.at(index_m).at(i);

        return sum;
    }

    int Solver::getTotalOfAllWeights(int index_m)
    {
        int sum = 0;

        for (auto &i : currentProblem->constraint.at(index_m))
            sum += i;

        return sum;
    }

    Solution Solver::getRandomSolution()
    {
        Solution solution;

        for (int i = 0; i < currentProblem->n; ++i) {
            int randomVariable = getRandomIntegerValue(0, 1);

            solution.push_back(static_cast<bool>(randomVariable));
        }

        return solution;
    }

    Velocity Solver::getRandomVelocity()
    {
        Velocity velocity;

        for (int i = 0; i < currentProblem->n; ++i) {
            double randomVariable = getRandomDoubleValue(0.0, 1.0);

            velocity.push_back(randomVariable);
        }

        return velocity;
    }

    int Solver::getRandomIntegerValue(int lowerBound, int upperBound)
    {
        int randomVariable = lowerBound + (std::rand() % (upperBound - lowerBound + 1));

        return randomVariable;
    }

    double Solver::getRandomDoubleValue(double lowerBound, double upperBound)
    {
        double randomVariable = (double) std::rand() / RAND_MAX;

        return lowerBound + randomVariable * (upperBound - lowerBound);
    }

    Swarm &Solver::getSwarmReference()
    {
        return swarm;
    }

}
