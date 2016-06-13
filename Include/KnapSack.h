/**
 * @file KnapSack.h
 * @author Etienne de Saint Germain
 * @date 2014
 * @brief Template function to solve the Knapsack problem using dynamic programming.
 * @details WARNING: T must be a class with an operator + and an operator <
 */

#ifndef KNAPSACK_H
#define KNAPSACK_H

#include <vector>
#include <algorithm>
#include <stdio.h>


/**
 * @brief Returns the maximum value that can be put in a knapsack of capacity W
 * and the binary vector of the affectation
 * @param[in] iW Total weight of the knapsack
 * @param[in] iWt Vector of object's weights
 * @param[in] iVal Vector of object's values
 * @param[in] iN Number of objects
 * @param[out] oSol Array of the choosen elements
 *                  (Warning: erase the current elements in the vector!)
 * @return the optimal value of the knapsack
 */
template<class T>
T knapSack(const int iW, const std::vector<int> iWt,
           const typename std::vector<T> iVal, const int iN,
           std::vector<int> & oSol);

/**
 * @brief Return the maximum value that can be put in a knapsack of capacity W
 * @param[in] iW Total weight of the knapsack
 * @param[in] iWt Vector of object's weights
 * @param[in] iVal Vector of object's values
 * @param[in] iN Number of objects
 * @return the optimal value of the knapsack
 */
template<class T>
T knapSack(const int iW, const std::vector<int> iWt,
           const typename std::vector<T> iVal, const int iN);



//==============================================================================
// Implementation of functions
//==============================================================================

/**
 * @brief Fill the array of used by dynamic programming to solve the knapsack problem
 * @param[in] iW Total weight of the knapsack
 * @param[in] iWt Vector of object's weights
 * @param[in] iVal Vector of object's values
 * @param[in] iN Number of objects
 * @param[in] K Table storing the optimal value of the knapsack for each etap of the dynamic programming
 * @return the optimal value of the knapsack
 */
template<class T>
T fill_dynamic_programming_array_of_knapsack(const int iW, const std::vector<int> iWt,
                                             const typename std::vector<T> iVal, const int iN,
                                             std::vector<typename std::vector<T> > & K)
{
  int i, w;
  // Build table K[][] in bottom up mainner
  for (i = 0; i <= iN; i++)
  {
    for (w = 0; w <= iW; w++)
    {
      if (i==0 || w==0)
        K[i][w] = 0;
      else if (iWt[i-1] <= w)
        K[i][w] = std::max(iVal[i-1]+K[i-1][w-iWt[i-1]],  K[i-1][w]);
      else
        K[i][w] = K[i-1][w];
    }
  }
  return K[iN][iW];
}


template<class T>
T knapSack(const int iW, const std::vector<int> iWt,
           const typename std::vector<T> iVal, const int iN,
           std::vector<int> & oSol)
{
  std::vector< std::vector<T> > K(iN+1, std::vector<T>(iW+1,0));
 
  fill_dynamic_programming_array_of_knapsack<T>(iW, iWt, iVal, iN, K);

  // Creation of the object list
  oSol.assign(iN,0);
  int i = iN; int w = iW;
  while (K[i][w]==K[i][w-1])
    w--;
  while (w > 0)
  {
    while (i > 0 && K[i][w]==K[i-1][w]) {
      oSol[i-1] = 0;
      i--;
    }
    w -= iWt[i-1];
    oSol[i-1] = 1;
    i--;
  }

  return K[iN][iW];
}


template<class T>
T knapSack(const int iW, const std::vector<int> iWt,
           const typename std::vector<T> iVal, const int iN)
{
  std::vector< std::vector<T> > K(iN+1, std::vector<T>(iW+1,0));
  return fill_dynamic_programming_array_of_knapsack<T>(iW, iWt, iVal, iN, K);
}




#endif // KNAPSACK_H

