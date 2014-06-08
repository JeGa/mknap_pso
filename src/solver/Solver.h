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
            Parameters parameters;
            Swarm swarm;

            /**
             * sum{j=1,...,n} p(j)x(j)
             */
            int calculateProfit(Solution s, Profit profits);
            Solution getRandomSolution(int size);

        public:
            Solver();
            ~Solver();
    };

}

#endif
