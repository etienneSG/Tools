/**
 * @file hcube_iterator.h
 * @author Etienne de Saint Germain
 * @date 2014
 * @brief File declaring an iterator on the subdivision of an hypercube.
 */



#ifndef HCUBEITERATOR_H
#define HCUBEITERATOR_H

#include <vector>
#include <assert.h>


/**
 * @brief Iterator on the subdivision of an hypercube.
 * @details The subdivision is characterized by two value:
 * - n which is is dimension.
 * - k which is the number  on subdivision along a dimension.
 *
 * For example, if n=2 and k=3, there are k^n=9 iterated points:
 * <table>
 *   <tr><td>(0,0)<td>(0,1)<td>(0,2)
 *   <tr><td>(1,0)<td>(1,1)<td>(1,2)
 *   <tr><td>(2,0)<td>(2,1)<td>(2,2)
 * </table>
 */
class Hcube_iterator
{
public:
  /** @brief Default constructor */
  Hcube_iterator();
  
  /**
   * @brief Constructor
   * @param[in] iN dimension of the hypercube
   * @param[in] iK number of subdivision of the hypercube
   */
  Hcube_iterator(int iN,int iK);
  
  /** @brief Destructor */
  ~Hcube_iterator();
  
  /** @brief Iterator on the set of k-combinations from a set of n elements */
  void operator++();
  
  /**
   * @brief Return the iIdx-th coordinate of the current iterated element
   * @param[in] iIdx one of the k chosen elements
   * @return index of the iIdx-th chosen element
   */
  inline int operator()(int iIdx);

  /** @brief Print the indexes of the k current chosen elements */
  void print();
  
  /** @brief Return false while the iterator has not iterate on every element */
  inline bool is_ended();
  
  /** @brief Reset the iterator at the begining */
  void reset();
  
private:
  int _n;               /**< dimension of the hypercube */
  int _k;               /**< number of subdivision of the hypercube */
  std::vector<int> _v;  /**< Vector of indexes of current vertex */
};


//==============================================================================
// Implementation of inline methods
//==============================================================================

inline bool Hcube_iterator::is_ended() {
  return _v[0] >= 0;
}

inline int Hcube_iterator::operator()(int iIdx) {
  assert(0 <= iIdx && iIdx < _n);
  return _v[iIdx+1];
}

#endif
