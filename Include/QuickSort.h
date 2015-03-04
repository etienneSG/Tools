//==============================================================================
// 
// Function quickSort:
//   Template function to sort on the elements of a vector in increasing order.
// This function perform the quick sort algorithm.
//
// WARNING ! If the object T is a pointeur, quickSort compare the pointers and
// not the pointed values.
//
//==============================================================================

#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <algorithm>
#include <vector>


/**
 * Execute a quick sort ont the element of the vector
 * @param iBegin: Iterator on the first element to sort in the vector
 * @param iEnd:   Iterator on the last element to sort in the vector
 */
template<class T>
void quickSort(typename std::vector<T>::iterator iBegin,
               typename std::vector<T>::iterator iEnd);


/**
 * Separate the elements lower than the first one of those greater than the first
 * one. Then, put the first one in the middle of these two sets.
 * @param iBegin: First element of the vector to separate
 * @param iEnd:   Last element of the vector to separate
 * @return: New index of the first element
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
void quickSort(typename std::vector<T>::iterator iBegin,
               typename std::vector<T>::iterator iEnd)
{
  typename std::vector<T>::iterator pivot;
  if (iBegin < iEnd)
  {
    pivot = partition<T>(iBegin, iEnd);
    quickSort<T>(iBegin, pivot);  
    quickSort<T>(pivot+1, iEnd);
  }
}


#endif

