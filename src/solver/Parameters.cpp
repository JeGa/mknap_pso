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

        return p;
    }

}

