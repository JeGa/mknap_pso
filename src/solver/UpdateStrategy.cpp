#include "UpdateStrategy.h"

#include <cmath>

namespace mknap_pso
{

    double UpdateStrategy::getRandomDoubleValue(double lowerBound, double upperBound)
    {
        double randomVariable = (double) std::rand() / RAND_MAX;

        return lowerBound + randomVariable * (upperBound - lowerBound);
    }

    int UpdateStrategyStandard::updatePosition(int currentPosition, double velocity)
    {
        // Logistic transformation
        velocity = 1.0 / (1.0 + exp(-velocity));
        //velocity = velocity / (1.0 + abs(velocity));

        // Calculate new position
        double randomValue = getRandomDoubleValue(0.0, 1.0);

        int newPositionD;
        if (randomValue < velocity)
            newPositionD = 1;
        else
            newPositionD = 0;

        return newPositionD;
    }

    int UpdateStrategyStandardUpdated::updatePosition(int currentPosition, double velocity)
    {
        // Logistic transformation
        velocity = 1.0 / (1.0 + exp(-velocity));
        //velocity = velocity / (1.0 + abs(velocity));

        int newPositionD;

        double alpha = 0.5;//getRandomDoubleValue(0.0, 1.0);
        if (velocity <= alpha)
            newPositionD = currentPosition;
        else if (velocity <= (1 + alpha) / 2)
            newPositionD = 1;
        else
            newPositionD = 0;

        return newPositionD;
    }

    int UpdateStrategyNovelBased::updatePosition(int currentPosition, double velocity)
    {
        double Rmax = 1000.0;
        double Rmin = -1000.0;

        double newPositionD_tmp = currentPosition + velocity;
        newPositionD_tmp = (newPositionD_tmp - Rmin) / (Rmax - Rmin); // L(x)

        int newPositionD;
        double randomValue = getRandomDoubleValue(0.0, 1.0);
        if (randomValue <= newPositionD_tmp)
            newPositionD = 1;
        else
            newPositionD = 0;

        return newPositionD;
    }

}
