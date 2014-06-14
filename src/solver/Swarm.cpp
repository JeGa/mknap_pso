#include "Swarm.h"

namespace mknap_pso
{

    void Swarm::initializeSwarm(int numberOfParticles)
    {
        gBest = 0;
        gBestPosition.clear();
        gBestInitialized = false;

        particles.clear();

        for (int i = 0; i < numberOfParticles; ++i) {
            particles.emplace_back();
        }
    }

    void Swarm::setBestPositionAndValue(Solution gBestPosition, int gBest)
    {
        this->gBest = gBest;
        this->gBestPosition = gBestPosition;

        gBestInitialized = true;
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

    bool Swarm::isGBestInitialized()
    {
        return gBestInitialized;
    }

}
