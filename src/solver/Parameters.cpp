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

}

