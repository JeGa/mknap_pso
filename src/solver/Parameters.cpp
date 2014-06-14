#include "Parameters.h"

namespace mknap_pso
{

    Parameters::Parameters()
    {
    }

    Parameters::~Parameters()
    {
    }

    Parameters Parameters::getDefaultParameters()
    {
        Parameters p;

        p.numberOfParticles = 10;
        p.iterations = 10;
        p.inertiaWeight = 0.8;
        p.constant1 = 2.0;
        p.constant2 = 2.0;
        p.vMax = 6.0;

        return p;
    }

    void Parameters::set(int numberOfParticles,
                         int iterations,
                         double inertiaWeight,
                         double constant1,
                         double constant2,
                         double vMax)
    {
        this->numberOfParticles = numberOfParticles;
        this->iterations = iterations;
        this->inertiaWeight = inertiaWeight;
        this->constant1 = constant1;
        this->constant2 = constant2;
        this->vMax = vMax;
    }

}
