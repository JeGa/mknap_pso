#ifndef SOLVER_H
#define SOLVER_H

#include "KnapsackProblem.h"
#include "Swarm.h"
#include "Particle.h"
#include "Parameters.h"

#include <vector>
#include <memory>

namespace mknap_pso
{

    class Solver
    {
        private:
            std::shared_ptr<KnapsackProblem> currentProblem = 0;
            bool solving = false;

            Parameters parameters;

            Swarm swarm;

            /**
             * sum{j=1,...,n} p(j)x(j)
             */
            int calculateProfit(Solution &s);

            int calculatePenalty(Solution &newPosition, int pBestTmp);

            /**
             * Calculates the ressource value of the given constraint
             * in the given solution.
             *
             * @param position The solution to be checked
             * @param index_m The constraint (index) to be checked to
             *
             * sum{j=1,...,n} r(i,j)x(j) <= b(i) ; i=1,...,m
             *
             * => index_m = i
             *
             * @return The ressource sum value of the given ressource.
             */
            int getConstraintValue(Solution &position, int index_m);

            /**
             * @retval 0 Constraint is not violated
             * @retval >0 The distance (difference) value
             */
            int checkConstraint(Solution &position, int index_m);

            int getTotalOfAllWeights(int index_m);

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

            int updateStrategy_novelBased(int currentPositionD, double newVelocityD);

            int updateStrategy_standard(int currentPositionD, double newVelocityD);

            int updateStrategy_standardUpdated(int currentPositionD, double newVelocityD);

        public:
            Solver();
            ~Solver();

            void solveProblem(std::shared_ptr<KnapsackProblem> problem);

            void setParameters(Parameters parameters);

            /**
             * The following functions are for manual usage.
             * (Do the steps manually from outside).
             */
            void startSolveProblem(std::shared_ptr<KnapsackProblem> problem);
            int solveProblemIteration();
            int stopSolveProblem();

            Swarm &getSwarmReference();
            bool isSolving();
    };

}

#endif
