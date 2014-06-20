#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <QString>

namespace mknap_pso
{

    class Parameters
    {
        private:
            int numberOfParticles;
            int iterations;

            double inertiaWeight;
            double constant1;
            double constant2;
            double vMax;

        public:
            Parameters();
            ~Parameters();

            static Parameters getDefaultParameters();

            void set(int numberOfParticles,
                     int iterations,
                     double inertiaWeight,
                     double constant1,
                     double constant2,
                     double vMax);

            int getNumberOfParticles() {
                return numberOfParticles;
            }

            double getConstant1() {
                return constant1;
            }

            double getConstant2() {
                return constant2;
            }

            int getIterations() {
                return iterations;
            }

            double getVMax() {
                return vMax;
            }

            double getInertiaWeight() {
                return inertiaWeight;
            }

            QString toString();
    };

}

#endif
