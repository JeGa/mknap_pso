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
        p.iterations = 500;
        p.inertiaWeight = 1.0;
        p.constant1 = 10.0;
        p.constant2 = 1.0;
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

    QString Parameters::toString()
    {
        QString str;

        str = QString::number(numberOfParticles) + " " + QString::number(iterations) + " " +
              QString::number(inertiaWeight) + " " + QString::number(constant1) + " " +
              QString::number(constant2) + " " +   QString::number(vMax);

        return str;
    }

}
