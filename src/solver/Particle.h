#ifndef PARTICLE_H
#define PARTICLE_H

#include <vector>

namespace mknap_pso
{
    /**
     * A solution is described as 0/1 vector.
     * x(j) = 1, Element is packed
     * x(j) = 0, Element is not packed
     */
    typedef std::vector<bool> Solution;

    /**
     * The probability, that a Solution bit is 1.
     */
    typedef std::vector<double> Velocity;

    class Particle
    {
        private:
            int pBest = 0; // Fitness value
            Solution pBestPosition;

            Solution position;
            Velocity velocity;

        public:
            Particle() {}
            ~Particle() {}

            Solution &getPosition();
            Velocity &getVelocity();
            Solution &getBestPosition();
            int getBestValue();

            void setPosition(Solution position);
            void setVelocity(Velocity velocity);
            void setBestPositionAndValue(Solution pBestPosition, int pBest); // = Fitness value
    };

}

#endif // PARTICLE_H
