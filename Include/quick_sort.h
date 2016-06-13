/**
 * @file quick_sort.h
 * @author Etienne de Saint Germain
 * @date 2014
 * @brief File implementing a template functor for the quick sort algorithm.
 */


#ifndef QUICK_SORT_H
#define QUICK_SORT_H

#include <algorithm>
#include <vector>


/**
 * @brief Template for quick sort algorithm.
 * @details Template function to sort on the elements of a vector in increasing
 * order. This function perform the quick sort algorithm.
 *
 * WARNING: this class DO NOT verify the validity of a range called by the user!
 */
template< class T >
class Quick_sort
{
public:
  /** @brief Constructor */
  Quick_sort();

  /** @brief Destructor */
  ~Quick_sort();

  /**
   * @brief Execute a quick sort on the element of the vector
   * @param[in] iBegin Iterator on the first element to sort in the vector
   * @param[in] iEnd Iterator on the last element to sort in the vector
   */
  void operator()(typename std::vector<T>::iterator iBegin,
		  typename std::vector<T>::iterator iEnd);

protected:
  /**
   * @brief Separate the elements lower than the first one of those greater than
   * the first one. Then, put the first one in the middle of these two sets.
   * @param[in] iBegin First element of the vector to separate
   * @param[in] iEnd Last element of the vector to separate
   * @return New index of the first element
   */
  typename std::vector<T>::iterator partition(typename std::vector<T>::iterator iBegin,
					      typename std::vector<T>::iterator iEnd);

};


//==============================================================================
// Implementation of functions
//==============================================================================

template< class T >
Quick_sort<T>::Quick_sort()
{}


template< class T >
Quick_sort<T>::~Quick_sort()
{}


template< class T >
typename std::vector<T>::iterator Quick_sort<T>::partition(typename std::vector<T>::iterator iBegin,
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
void Quick_sort<T>::operator()(typename std::vector<T>::iterator iBegin,
			       typename std::vector<T>::iterator iEnd)
{
  typename std::vector<T>::iterator pivot;
  if (iBegin < iEnd)
  {
    pivot = partition(iBegin, iEnd);
    operator()(iBegin, pivot);  
    operator()(pivot+1, iEnd);
  }
}


#endif // QUICK_SORT_H

