/**
 * @file random_iterator.h
 * @author Etienne de Saint Germain
 * @date 2014
 * @brief File declaring a random iterator on the integer of an intervalle [0, N[
 */

#ifndef RANDOMITERATOR_H
#define RANDOMITERATOR_H

#include <algorithm>
#include <iostream>
#include <vector>


/**
 * @brief Random iterator on the integer of an intervalle [0, N[
 * @details N represent the number of element of the intervalle.
 *
 * WARNING! Random must be initialize in the main function!
 */
class Random_iterator
{
public:
  /**
   * @brief Constructor
   * @param[in] iN Number of elements in the set. (Default value: 0)
   */
  Random_iterator(unsigned int iN = 0);
  
  /** @brief Destructor */
  ~Random_iterator();
  
  /** @brief Reset the operator */
  void reset();
  
  /** @brief Increment the iterator on the elements */
  inline void operator++();
  
  /** @brief Return false while the iterator has not iterate on every element */
  inline bool is_ended();
  
  /** Return current random integer of [0, N[ */
  inline int operator()();
  
protected:
  unsigned int _n;                         /**< @brief Number of elements (N) */
  std::vector<unsigned int> _v;            /**< @brief Vector of N elements */
  std::vector<unsigned int>::iterator _it; /**< @brief Iterator on the elements of the vector */
};


//==============================================================================
// Implementation of methods
//==============================================================================


Random_iterator::Random_iterator(unsigned int iN):
  _n(iN),
  _v(iN, 0),
  _it(_v.begin())
{
  for (unsigned int i = 0; i < _n; i++)
    _v[i] = i;
  std::random_shuffle(_v.begin(), _v.end());
}


Random_iterator::~Random_iterator()
{
}


void Random_iterator::reset()
{
  std::random_shuffle(_v.begin(), _v.end());
  _it = _v.begin();
}


inline void Random_iterator::operator++() {
  ++_it;
}


inline bool Random_iterator::is_ended() {
  return (_it == _v.end());
}


inline int Random_iterator::operator()() {
  return *_it;
}

#endif


