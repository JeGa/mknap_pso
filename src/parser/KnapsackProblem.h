/**
    The problem to be solved is:
    Max  sum{j=1,...,n} p(j)x(j)
    st   sum{j=1,...,n} r(i,j)x(j) <= b(i) ; i=1,...,m
                        x(j)=0 or 1
 */

#ifndef KNAPSACK_PROBLEM_H
#define KNAPSACK_PROBLEM_H

#include <string>
#include <vector>

namespace mknap_pso
{
    typedef std::vector<int> Profit;
    typedef std::vector<int> ConstraintValues;
    typedef std::vector<ConstraintValues> Constraint;
    typedef std::vector<int> Capacity;

    struct KnapsackProblem {
        int n; // Nr. of elements to pack
        int m; // Nr. of constraints
        int solution;

        // Index (j) = element (count = n)
        Profit profit;

        // Index (i, j) => i=constraints ; j=elements
        Constraint constraint;

        // (count = m)
        Capacity capacity;

        std::string toString();
    };

}

#endif
