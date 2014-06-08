#include "Particle.h"

namespace mknap_pso
{

    Particle::Particle()
    {
    }

    Particle::~Particle()
    {
    }

    void Particle::setPosition(Solution position)
    {
        this->position = position;
    }

    void Particle::setBestKnownPosition(int pBest)
    {
        this->pBest = pBest;
    }

    void Particle::setVelocity(Solution velocity)
    {
        this->velocity = velocity;
    }

}
