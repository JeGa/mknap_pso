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

        p.numberOfParticles = 20;
        p.iterations = 50;
        p.inertiaWeight = 1.0;
        p.constant1 = 1.0;
        p.constant2 = 1.3;
        p.vMax = 5.0;

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
