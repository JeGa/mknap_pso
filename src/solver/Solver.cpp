#include "Solver.h"

#include <cstdlib>
#include <ctime>

namespace mknap_pso
{

    Solver::Solver()
    {
        parameters = Parameters::getDefaultParameters();

        swarm.initializeSwarm(parameters.getNumberOfParticles());
    }

    ~Solver::Solver()
    {

    }

    int Solver::calculateProfit(Solution solution, Profit profits)
    {
        if (solution.size() != profits.size())
            throw std::invalid_argument("Size of the arguments is not equal.");

        int sum = 0;

        for (int i = 0; i < s.size(); ++i)
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
