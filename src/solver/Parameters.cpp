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
        p.constant1 = 2;
        p.constant2 = 2;
        p.iterations = 10;

        return p;
    }

    void Parameters::set(int numberOfParticles,
                         int constant1,
                         int constant2,
                         int iterations)
    {
        this->numberOfParticles = numberOfParticles;
        this->constant1 = constant1;
        this->constant2 = constant2;
        this->iterations = iterations;
    }

}
