#ifndef UPDATE_STRATEGY_H
#define UPDATE_STRATEGY_H

#include <ctime>
#include <cstdlib>

namespace mknap_pso
{

    class UpdateStrategy
    {
        protected:
            double getRandomDoubleValue(double lowerBound, double upperBound);

        public:
            UpdateStrategy() {
                std::srand(std::time(0));
            }
            virtual ~UpdateStrategy() {}

            virtual int updatePosition(int currentPosition, double velocity) = 0;
    };

    /* K. and E. */
    class UpdateStrategyStandard : public UpdateStrategy
    {
        public:
            UpdateStrategyStandard() : UpdateStrategy() {}
            virtual ~UpdateStrategyStandard() {}

            virtual int updatePosition(int currentPosition, double velocity);
    };

    /* Updated formula from Qi Shen */
    class UpdateStrategyStandardUpdated : public UpdateStrategy
    {
        public:
            UpdateStrategyStandardUpdated() {}
            virtual ~UpdateStrategyStandardUpdated() {}

            virtual int updatePosition(int currentPosition, double velocity);
    };

    /* Novel based */
    class UpdateStrategyNovelBased : public UpdateStrategy
    {
        public:
            UpdateStrategyNovelBased() {}
            virtual ~UpdateStrategyNovelBased() {}

            virtual int updatePosition(int currentPosition, double velocity);
    };

}

#endif
