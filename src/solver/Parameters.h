#ifndef PARAMETERS_H
#define PARAMETERS_H

namespace mknap_pso
{

    class Parameters
    {
        private:
            int numberOfParticles;

        public:
            Parameters();
            ~Parameters();

            static Parameters getDefaultParameters();

            int getNumberOfParticles() { return numberOfParticles; }
    };

}

#endif
