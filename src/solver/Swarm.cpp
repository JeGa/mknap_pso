#include "Swarm.h"

namespace mknap_pso
{

    void Swarm::initializeSwarm(int numberOfParticles)
    {
        gBest = 0;
        gBestPosition.clear();

        particles.clear();

        for (int i = 0; i < numberOfParticles; ++i) {
            Particle p; // TODO: emplace_back ?
            particles.push_back(p);
        }
    }

    void Swarm::setBestPositionAndValue(Solution gBestPosition, int gBest)
    {
        this->gBest = gBest;
        this->gBestPosition = gBestPosition;
    }

    std::vector<Particle> &Swarm::getParticles()
    {
        return particles;
    }

    int Swarm::getBestValue()
    {
        return gBest;
    }

    Solution &Swarm::getBestPosition()
    {
        return gBestPosition;
    }

}
