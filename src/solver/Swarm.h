#ifndef SWARM_H
#define SWARM_H

#include "Particle.h"

#include <vector>

namespace mknap_pso
{

    class Swarm
    {
        private:
            int gBest;

            std::vector<Particle> particles;

        public:
            Swarm();
            ~Swarm();

            void initializeSwarm(int numberOfParticles);
    };

}

#endif
