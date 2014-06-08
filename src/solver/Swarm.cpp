#include "Swarm.h"

namespace mknap_pso
{

    Swarm::Swarm()
    {

    }

    Swarm::~Swarm()
    {
    }

    void Swarm::initializeSwarm(int numberOfParticles)
    {
        for (int i = 0; i < numberOfParticles; ++i) {
            Particle p;

            particles.push_back(p);
        }
    }

}
