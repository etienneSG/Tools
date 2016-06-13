/**
 * @file n_choose_k_iterator.h
 * @author Etienne de Saint Germain
 * @date 2014
 * @brief File declaring an iterator n the set of k-combinations from a set of n elements
 */


#ifndef N_CHOOSE_K_ITERATOR_H
#define N_CHOOSE_K_ITERATOR_H

#include <vector>
#include <assert.h>

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
  N_choose_K_iterator();
  
  /**
   * @brief Constructor
   * @param[in] iN number of elements in the set
   * @param[in] iK number of elements to chose
   */
  N_choose_K_iterator(int iN,int iK);
  
  /** @brief Destructor */
  ~N_choose_K_iterator();
  
  /** @brief Iterator on the set of k-combinations from a set of n elements */
  void operator++();
  
  /**
   * @brief Return the index of the iIdx-th chosen element
   * @param[in] iIdx one of the k chosen elements
   * @return index of the iIdx-th chosen element
   */
  inline int operator()(int iIdx);

  /** @brief Print the indexes of the k current chosen elements */
  void print();
  
  /** @brief Return false while the iterator has not iterate on every element */
  inline bool is_ended();

  /**
   * @brief Reset the operator
   * @param[in] iEnd if false, do not modify the actual value returned by the
   * method IsEnded.
   */
  void reset(bool iEnd = true);
  
private:
  int _n;               /**< Number of elements in the set */
  int _k;               /**< Number of elements to chose */
  std::vector<int> _v;  /**< Vector of indexes of current chosen elements */
};


//==============================================================================
// Implementation of inline methods
//==============================================================================

inline bool N_choose_K_iterator::is_ended() {
  return _v[0] >= 0;
}

inline int N_choose_K_iterator::operator()(int iIdx) {
  assert(0 <= iIdx && iIdx < _k);
  return _v[iIdx+1];
}

#endif // N_CHOOSE_K_ITERATOR_H
