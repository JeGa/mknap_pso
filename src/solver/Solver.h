#ifndef SOLVER_H
#define SOLVER_H

#include "KnapsackProblem.h"
#include "Swarm.h"
#include "Particle.h"
#include "Parameters.h"

#include <vector>

namespace mknap_pso
{

    /**
     * A solution is described as 0/1 vector.
     * x(j) = 1, Element is packed
     * x(j) = 0, Element is not packed
     */
    typedef std::vector<bool> Solution;

    class Solver
    {
        private:
            KnapsackProblem *currentProblem = 0;

            Parameters parameters;
            Swarm swarm;

            /**
             * sum{j=1,...,n} p(j)x(j)
             */
            int calculateProfit(Solution s);

            /**
             * Generates a solution with uniformly distributed
             * random values.
             */
            Solution getRandomSolution();

            void initializeParticles();

            void findSolution();

        public:
            Solver();
            ~Solver();

            void solveProblem(KnapsackProblem *problem);
    };

}

#endif
