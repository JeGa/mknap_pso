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
            std::vector<Particle> particles;

        public:
            Swarm();
            ~Swarm();

            void initializeSwarm(int numberOfParticles);
            void setBestGlobalPosition(int gBest);

            std::vector<Particle> &getParticles();
            int getBestGlobalPosition();
    };

}

#endif
