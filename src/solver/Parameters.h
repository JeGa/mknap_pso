#ifndef PARAMETERS_H
#define PARAMETERS_H

namespace mknap_pso
{

    class Parameters
    {
        private:
            int numberOfParticles;

            int constant1;
            int constant2;

            int iterations;

        public:
            Parameters();
            ~Parameters();

            static Parameters getDefaultParameters();

            void set(int numberOfParticles,
                     int constant1,
                     int constant2,
                     int iterations);

            int getNumberOfParticles() {
                return numberOfParticles;
            }

            int getConstant1() {
                return constant1;
            }

            int getConstant2() {
                return constant2;
            }

            int getIterations() {
                return iterations;
            }
    };

}

#endif
