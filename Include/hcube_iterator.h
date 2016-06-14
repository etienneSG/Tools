/**
 * @file hcube_iterator.h
 * @author Etienne de Saint Germain
 * @date 2014
 * @brief File declaring an iterator on the subdivision of an hypercube.
 */



#ifndef HCUBEITERATOR_H
#define HCUBEITERATOR_H

#include <assert.h>
#include <iostream>
#include <vector>


/**
 * @brief Iterator on the subdivision of an hypercube.
 * @details The subdivision is characterized by two value:
 * - n which is his dimension.
 * - k which is the number on subdivision along a dimension.
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
  Hcube_iterator(unsigned int iN, unsigned int iK);
  
  /** @brief Destructor */
  ~Hcube_iterator();
  
  /** @brief Iterator on the set of k-combinations from a set of n elements */
  void operator++();
  
  /**
   * @brief Return the iIdx-th coordinate of the current iterated element
   * @param[in] iIdx one of the k chosen elements
   * @return index of the iIdx-th chosen element
   */
  inline unsigned int operator()(unsigned int iIdx);

  /** @brief Print the indexes of the k current chosen elements */
  void print();
  
  /** @brief Return false while the iterator has not iterate on every element */
  inline bool is_ended();
  
  /** @brief Reset the iterator at the begining */
  void reset();
  
private:
  unsigned int _n;               /**< dimension of the hypercube */
  unsigned int _k;               /**< number of subdivision of the hypercube */
  std::vector<unsigned int> _v;  /**< Vector of indexes of current vertex */
};


//==============================================================================
// Implementation of inline methods
//==============================================================================


Hcube_iterator::Hcube_iterator():
  _n(0),
  _k(0)
{
}


Hcube_iterator::Hcube_iterator(unsigned int iN, unsigned int iK):
  _n(iN),
  _k(iK),
  _v(iN+1, 1)
{
  _v[0]=0;
}


Hcube_iterator::~Hcube_iterator()
{
}


void Hcube_iterator::operator++()
{
  int l=_n;
  _v[l]++;
  while (l > 0 && _v[l] >= _k+1 )
  {
    _v[l-1]++;
    _v[l]=1;
    l--;
  }
}


void Hcube_iterator::print()
{
  for(unsigned int i = 0; i < _n; i++)
    std::cout << operator()(i) << " ";
  std::cout << std::endl;   
}


void Hcube_iterator::reset()
{
  _v.assign(_n+1,1);
  _v[0]=0;
}


inline bool Hcube_iterator::is_ended() {
  return _v[0] > 0;
}


inline unsigned int Hcube_iterator::operator()(unsigned int iIdx) {
  assert(iIdx < _n+1);
  return _v[iIdx+1]-1;
}

#endif
