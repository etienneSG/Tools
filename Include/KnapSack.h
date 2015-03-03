//==============================================================================
// 
// Function KnapSack:
//   Solve the Knapsack problem using dynamic programming
//
//==============================================================================


#ifndef KNAPSACK_H
#define KNAPSACK_H

#include <vector>

/**
 * Returns the maximum value that can be put in a knapsack of capacity W and the
 * binary vector of the affectation
 * @param iW:   Total weight of the knapsack
 * @param iWt:  Weight of each object
 * @param iVal: Value of each object
 * @param iN:   Number of objects
 * @param oSol: Array of the choosen elements
 *              (Warning: erase the current elements in the vector!)
 * @return: the optimal value of the knapsack
 */
int knapSack(const int iW, const std::vector<int> iWt,
             const std::vector<int> iVal, const int iN,
             std::vector<int> & oSol);


/**
 * Returns the maximum value that can be put in a knapsack of capacity W
 * @param iW:   Total weight of the knapsack
 * @param iWt:  Weight of each object
 * @param iVal: Value of each object
 * @param iN:   Number of objects
 * @return: the optimal value of the knapsack
 */
int knapSack(const int iW, const std::vector<int> iWt,
             const std::vector<int> iVal, const int iN);


#endif

