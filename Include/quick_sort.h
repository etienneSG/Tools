/**
 * @file quick_sort.h
 * @author Etienne de Saint Germain
 * @date 2014
 * @brief Template for quick sort algorithm.
 * @details Template function to sort on the elements of a vector in increasing
 * order. This function perform the quick sort algorithm.
 *
 * WARNING: this class DO NOT verify the validity of a range called by the user!
 */


#ifndef QUICK_SORT_H
#define QUICK_SORT_H

#include <algorithm>
#include <vector>


/**
 * @brief Execute a quick sort ont the element of the vector
 * @param[in] iBegin Iterator on the first element to sort in the vector
 * @param[in] iEnd Iterator on the last element to sort in the vector
 */
template< class T >
void quick_sort(typename std::vector<T>::iterator iBegin,
                typename std::vector<T>::iterator iEnd);


/**
 * @brief Separate the elements lower than the first one of those greater than
 * the first one. Then, put the first one in the middle of these two sets.
 * @param[in] iBegin First element of the vector to separate
 * @param[in] iEnd Last element of the vector to separate
 * @return New index of the first element
 */
template< class T >
typename std::vector<T>::iterator partition(typename std::vector<T>::iterator iBegin,
                                            typename std::vector<T>::iterator iEnd);



//==============================================================================
// Implementation of functions
//==============================================================================

template< class T >
typename std::vector<T>::iterator partition(typename std::vector<T>::iterator iBegin,
                                            typename std::vector<T>::iterator iEnd)
{
  T x = *iBegin;
  typename std::vector<T>::iterator i = iBegin;
  typename std::vector<T>::iterator j;

  for (j = iBegin+1; j < iEnd; j++) {
    if (*j<x) {
      ++i;
      std::swap(*i, *j);
    }
  }

  std::swap(*i, *iBegin);
  return i;
}


template<class T>
void quick_sort(typename std::vector<T>::iterator iBegin,
                typename std::vector<T>::iterator iEnd)
{
  typename std::vector<T>::iterator pivot;
  if (iBegin < iEnd)
  {
    pivot = partition<T>(iBegin, iEnd);
    quick_sort<T>(iBegin, pivot);  
    quick_sort<T>(pivot+1, iEnd);
  }
}


#endif // QUICK_SORT_H

