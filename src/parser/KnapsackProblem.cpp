#include "KnapsackProblem.h"

#include <sstream>

namespace mknap_pso
{

    std::string KnapsackProblem::toString()
    {
        std::stringstream sstr;

        sstr << "Problem:" << std::endl;
        sstr << "\tNr. of Elements: " << n << std::endl;
        sstr << "\tNr. of Constraints: " << m << std::endl;
        sstr << "\tSolution: " << solution << std::endl;

        sstr << "\tProfit array size: " << profit.size() << std::endl;
        sstr << "\tConstraint array size: " << constraint.size() << std::endl;

        for (auto &i : constraint)
            sstr << "\tConstraint array element size: " << i.size() << std::endl;

        sstr << "\tCapacity array size: " << capacity.size() << std::endl;

        return sstr.str();
    }

}
