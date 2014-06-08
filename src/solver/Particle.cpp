#include "Particle.h"

namespace mknap_pso
{

    Particle::Particle()
    {
    }

    Particle::~Particle()
    {
    }

    void Particle::setBestKnownPosition(int pBest)
    {
        this->pBest = pBest;
    }

}
