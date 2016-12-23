/**
 * @file knapsack.h
 * @author Etienne de Saint Germain
 * @date 2014
 * @brief Template function to solve the Knapsack problem using dynamic programming.
 */

#ifndef KNAPSACK_H
#define KNAPSACK_H

#include <vector>
#include <algorithm>
#include <stdio.h>


/**
 * @brief Template functor to solve the Knapsack problem using dynamic programming.
 * @details WARNING! T must be a class with:
 * - a default constructor
 * - an operator +
 * - an operator <

 * A minimal example is given by the following code:
 * @code{cpp}
 * #include "knapsack.h" // Knapsack class
 * #include <iostream>   // Streaming output
 * #include <vector>     // Vector class
 * 
 * int main()
 * {
 *   std::vector<int> val(4,0);                    // Values of the items
 *   val[0]=100; val[1]=60; val[2]=120; val[3]=50; //
 *   std::vector<unsigned int> wt(4,0);            // Weights of the items
 *   wt[0]=20;   wt[1]=20;  wt[2]=30;   wt[3]=10;  //
 *   unsigned int  W = 50;                         // Weight limit of the knapsack
 * 
 *   Knapsack<int> knapsack(W, wt, val);     // Create the knapsack problem
 *   int opt = knapsack();                   // Solve the knapsack problem
 *   std::vector<bool> Solution;             // 
 *   knapsack.get_chosen_objects(Solution);  // Get the list of chosen item
 * 
 *   std::cout << "Optimal value of the knapsack: " << opt << std::endl;
 *   std::cout << "Affectation in the knapsack: ";
 *   for (unsigned int i = 0; i < Solution.size(); i++)
 *     std::cout << Solution[i] << " ";
 *   std::cout << std::endl;
 * 
 *   return 0;
 * }
 * @endcode
 * The expected output is:
 * @code{txt}
 * Optimal value of the knapsack: 220
 * Affectation in the knapsack: 1 0 1 0 
 * @endcode
 *
 */
template< class T >
class Knapsack
{
public:
  /**
   * @brief Default constructor
   */
  inline Knapsack();

  /**
   * @brief Constructor
   * @param[in] iW Weight limit of the knapsack
   * @param[in] iWt Vector of weights of the items
   * @param[in] iVal Vector of values of the items
   */
  inline Knapsack(const unsigned int iW, const std::vector<unsigned int> iWt, const typename std::vector<T> iVal);

  /**
   * @brief Destructor
   */
  inline ~Knapsack();

  /**
   * @brief Solve the knapsack problem with the parameters stored in the attribute of the fonctor
   * @return Optimal value of the knapsack
   */
  inline T operator()();

  /**
   * @brief Solve the knapsack problem with the parameters in argument
   * @details This method modifies the attribute of the fonctor
   * @param[in] iW Weight limit of the knapsack
   * @param[in] iWt Vector of weights of the items
   * @param[in] iVal Vector of values of the items
   * @return Optimal value of the knapsack
   */
  inline T operator()(const unsigned int iW, const std::vector<unsigned int> iWt, const typename std::vector<T> iVal);

  /**
   * @brief Return the optimal value of the knapsack
   * @warning The user must solve the knapsack calling the operator operator()()
   */
  inline T get_optimal_value();

  /**
   * @brief Return a vector representing the chosen elements
   * @details This method modifies the vector passed in argument
   * @param[out] oSolution Vector representing the chosen elements. If coordinate i is true,
   * the i-th element is chosen, otherwise, it is not.
   * @warning The user must solve the knapsack calling the operator operator()()
   */
  inline void get_chosen_objects(std::vector<bool> & oSolution);

protected:
  /**
   * @brief Solve the knapsack problem with the parameters stored in the attribute of the fonctor
   */
  inline void solve();

  unsigned int _W; /**< @brief [input] Total weight of the knapsack */
  std::vector<unsigned int> _Wt; /**< @brief [input] Vector of object's weights */
  typename std::vector<T> _Val; /**< @brief [input] Vector of object's values */

  T _opt_value; /**< @brief [output] Optimal value of the knapsack */
  std::vector<bool> _Solution; /**< @brief [output] Array of the choosen elements */
};


//==============================================================================
// Implementation of methods
//==============================================================================


template< class T >
inline Knapsack<T>::Knapsack()
: _W(0),
  _Wt(),
  _Val(),
  _opt_value(),
  _Solution()
{}


template< class T >
inline Knapsack<T>::Knapsack(const unsigned int iW, const std::vector<unsigned int> iWt, const typename std::vector<T> iVal)
: _W(iW),
  _Wt(iWt),
  _Val(iVal),
  _opt_value(),
  _Solution()
{
  // Assert that the sizes are equal
  size_t nb_objects = std::min(iWt.size(), iVal.size());
  _Wt.resize(nb_objects);
  _Val.resize(nb_objects);
  _Solution.assign(nb_objects, 0);
}



template< class T >
inline Knapsack<T>::~Knapsack()
{
}



template< class T >
inline T Knapsack<T>::operator()()
{
  solve();
  return _opt_value;
}



template< class T >
inline T Knapsack<T>::operator()(const unsigned int iW, const std::vector<unsigned int> iWt, const typename std::vector<T> iVal)
{
  // Reassignment
  _W = iW;
  _Wt.assign(iWt.begin(), iWt.end());
  _Val.assign(iVal.begin(), iVal.end());

  // Assert that the sizes are equal
  size_t nb_objects = std::min(iWt.size(), iVal.size());
  _Wt.resize(nb_objects);
  _Val.resize(nb_objects);
  _Solution.assign(nb_objects, false);

  // Solve the knapsack
  solve();
  return _opt_value;
}


template <class T>
inline T Knapsack<T>::get_optimal_value() {
  return _opt_value;
}


template< class T >
inline void Knapsack<T>::get_chosen_objects(std::vector<bool> & oSolution)
{
  oSolution.assign(_Solution.begin(),_Solution.end());
}


template< class T >
inline void Knapsack<T>::solve()
{
  size_t nb_obj = _Wt.size(); // number of objects
  std::vector< std::vector<T> > K(nb_obj+1, std::vector<T>(_W+1,0));
 
  // Build table K[][] in bottom up mainner
  for (size_t i = 0; i <= nb_obj; i++)
  {
    for (unsigned int w = 0; w <= _W; w++)
    {
      if (i==0 || w==0)
        K[i][w] = 0;
      else if (_Wt[i-1] <= w)
        K[i][w] = std::max(_Val[i-1]+K[i-1][w-_Wt[i-1]],  K[i-1][w]);
      else
        K[i][w] = K[i-1][w];
    }
  }
  _opt_value = K[nb_obj][_W];

  // Create the object list
  size_t i = nb_obj; unsigned int w = _W;
  while (w > 0 && K[i][w]==K[i][w-1])
    w--;
  while (w > 0)
  {
    while (i > 0 && K[i][w]==K[i-1][w]) {
      _Solution[i-1] = false;
      i--;
    }
    w -= _Wt[i-1];
    _Solution[i-1] = true;
    i--;
  }
}



#endif // KNAPSACK_H

