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
        particles.clear();
        gBest = 0;

        for (int i = 0; i < numberOfParticles; ++i) {
            Particle p;

            particles.push_back(p);
        }
    }

    void Swarm::setBestGlobalPosition(int gBest)
    {
        this->gBest = gBest;
    }

    std::vector<Particle> &Swarm::getParticles()
    {
        return particles;
    }

    int Swarm::getBestGlobalPosition()
    {
        return gBest;
    }

}
