#ifndef PARTICLE_H
#define PARTICLE_H

namespace mknap_pso
{

    class Particle
    {
        private:
            int pBest;

        public:
            Particle();
            ~Particle();

            void setBestKnownPosition(int pBest);
    };

}

#endif // PARTICLE_H
