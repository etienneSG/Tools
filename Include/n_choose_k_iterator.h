/**
 * @file n_choose_k_iterator.h
 * @author Etienne de Saint Germain
 * @date 2014
 * @brief File declaring an iterator n the set of k-combinations from a set of n elements
 */


#ifndef N_CHOOSE_K_ITERATOR_H
#define N_CHOOSE_K_ITERATOR_H

#include <assert.h>
#include <iostream>
#include <vector>

/**
 * @brief File declaring an iterator n the set of k-combinations from a set of n elements

 * @details For example, if n=4 and k=2, there are 6 iterated points:
 * <table>
 *   <tr><td>(0,1)<td>(0,2)<td>(0,3)
 *   <tr><td>     <td>(1,2)<td>(1,3)
 *   <tr><td>     <td>     <td>(2,3)
 * </table>
 */
class N_choose_K_iterator
{
public:
  /** @brief Default constructor */
  inline N_choose_K_iterator();
  
  /**
   * @brief Constructor
   * @param[in] iN number of elements in the set
   * @param[in] iK number of elements to chose
   */
  inline N_choose_K_iterator(unsigned int iN, unsigned int iK);
  
  /** @brief Destructor */
  inline ~N_choose_K_iterator();
  
  /** @brief Iterator on the set of k-combinations from a set of n elements */
  inline void operator++();
  
  /**
   * @brief Return the index of the iIdx-th chosen element
   * @param[in] iIdx one of the k chosen elements
   * @return index of the iIdx-th chosen element
   */
  inline unsigned int operator()(unsigned int iIdx);

  /** @brief Print the indexes of the k current chosen elements */
  inline void print();
  
  /** @brief Return false while the iterator has not iterate on every element */
  inline bool is_ended();

  /**
   * @brief Reset the operator
   * @param[in] iEnd if false, do not modify the actual value returned by the
   * method IsEnded.
   */
  inline void reset(bool iEnd = true);
  
private:
  unsigned int _n;               /**< Number of elements in the set */
  unsigned int _k;               /**< Number of elements to chose */
  std::vector<unsigned int> _v;  /**< Vector of indexes of current chosen elements */
};


//==============================================================================
// Implementation of methods
//==============================================================================


inline N_choose_K_iterator::N_choose_K_iterator():
  _n(0),
  _k(0)
{
}


inline N_choose_K_iterator::N_choose_K_iterator(unsigned int iN, unsigned int iK):
  _n(iN),
  _k(iK),
  _v(iK+1,iN+1)
{
  for (unsigned int i = 0; i < iK+1; i++)
    _v[i]=i;
}


inline N_choose_K_iterator::~N_choose_K_iterator()
{
}


inline void N_choose_K_iterator::operator++()
{
  unsigned int l=_k;
  _v[l]++;
  while (l > 0 && _v[l] >= (_n+l+1-_k) )
  {
    _v[l-1]++;
    _v[l]=1;
    l--;
  }
  for (unsigned int i = 1 ; i < _v.size(); i++)
  {
    if (_v[i]<=_v[i-1])
      _v[i]=_v[i-1]+1;
  }
}


inline unsigned int N_choose_K_iterator::operator()(unsigned int iIdx) {
  assert(iIdx < _k);
  return _v[iIdx+1]-1;
}


inline void N_choose_K_iterator::print()
{
  for(unsigned int i = 0; i < _k; i++)
    std::cout << operator()(i) << " ";
  std::cout << std::endl;   
}


inline bool N_choose_K_iterator::is_ended() {
  return _v[0] > 0;
}


inline void N_choose_K_iterator::reset(bool iEnd)
{
  _v[0] = iEnd ? -1 : 0;
  for (unsigned int i = 1; i < _k+1; i++)
    _v[i]=i;
}


#endif // N_CHOOSE_K_ITERATOR_H
