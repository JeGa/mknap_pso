#ifndef SWARM_H
#define SWARM_H

#include "Particle.h"

#include <vector>

namespace mknap_pso
{

    class Swarm
    {
        private:
            int gBest = 0; // Fitness value
            Solution gBestPosition;

            std::vector<Particle> particles;

        public:
            Swarm() {}
            ~Swarm() {}

            void initializeSwarm(int numberOfParticles);
            void setBestPositionAndValue(Solution gBestPosition, int gBest);

            std::vector<Particle> &getParticles();

            /**
             * @return The fitness value of the best global position.
             */
            int getBestValue();
            Solution &getBestPosition();
    };

}

#endif
