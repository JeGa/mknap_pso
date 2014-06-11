#include "Particle.h"

namespace mknap_pso
{

    void Particle::setPosition(Solution position)
    {
        this->position = position;
    }

    void Particle::setBestPositionAndValue(Solution pBestPosition, int pBest)
    {
        this->pBest = pBest;
        this->pBestPosition = pBestPosition;
    }

    void Particle::setVelocity(Velocity velocity)
    {
        this->velocity = velocity;
    }

    Solution &Particle::getPosition()
    {
        return position;
    }

    Velocity &Particle::getVelocity()
    {
        return velocity;
    }

    Solution &Particle::getBestPosition()
    {
        return pBestPosition;
    }

    int Particle::getBestValue()
    {
        return pBest;
    }

}
