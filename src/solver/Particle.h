#ifndef PARTICLE_H
#define PARTICLE_H

#include <vector>

namespace mknap_pso
{

    typedef std::vector<bool> Solution;

    class Particle
    {
        private:
            int pBest; // Fitness value

            Solution velocity;

            Solution position;

        public:
            Particle();
            ~Particle();

            void setPosition(Solution position);
            void setVelocity(Solution velocity);
            void setBestKnownPosition(int pBest); // = Fitness value
    };

}

#endif // PARTICLE_H
