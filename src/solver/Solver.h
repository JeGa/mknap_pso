#ifndef SOLVER_H
#define SOLVER_H

#include "KnapsackProblem.h"
#include "Swarm.h"
#include "Particle.h"
#include "Parameters.h"

#include <vector>
#include <random>

namespace mknap_pso
{

    class Solver
    {
        private:
            KnapsackProblem *currentProblem = 0;

            Parameters parameters;

            Swarm swarm;

            // Random generator stuff
            std::random_device rd;
            std::default_random_engine engine;

            /**
             * sum{j=1,...,n} p(j)x(j)
             */
            int calculateProfit(Solution s);

            /**
             * Generates a solution with uniformly distributed
             * random values.
             */
            Solution getRandomSolution();

            Velocity getRandomVelocity();

            int getRandomIntegerValue(int lowerBound, int upperBound);

            double getRandomDoubleValue(double lowerBound, double upperBound);

            /**
             * Initializes every particle with a random solution.
             */
            void initializeParticles();

            void findSolution();

        public:
            Solver();
            ~Solver();

            void solveProblem(KnapsackProblem *problem);
    };

}

#endif
