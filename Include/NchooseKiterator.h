//==============================================================================
// 
// Class NchooseKiterator:
//   Iterator on the elements of the k-combinations from a set of n elements.
//
//==============================================================================

#ifndef NCHOOSEKITERATOR_H
#define NCHOOSEKITERATOR_H

#include <vector>
#include <assert.h>

class NchooseKiterator
{
public:
  /** Default constructor */
  NchooseKiterator();
  
  /**
   * Constructor
   * @param iN: number of elements in the set
   * @param iK: number of elements to chose
   */
  NchooseKiterator(int iN,int iK);
  
  /** Destructor */
  ~NchooseKiterator();
  
  /** Iterator on the set of k-combinations from a set of n elements */
  void operator++();
  
  /**
   * Return the index of the iIdx-th chosen element
   * @param iIdx: one of the k chosen elements
   * @return index of the iIdx-th chosen element
   */
  inline int operator()(int iIdx);

  /** Print the indexes of the k current chosen elements */
  void Print();
  
  /** Return false while the iterator has not iterate on every element */
  inline bool IsEnded();

  /**
   * Reset the operator
   * @param iEnd: if false, do not modify the actual value returned by the
   *              method IsEnded.
   */
  void Reset(bool iEnd = true);
  
private:
  int _n;               // Number of elements in the set
  int _k;               // Number of elements to chose
  std::vector<int> _v;  // Vector of indexes of current chosen elements
};


//==============================================================================
// Implementation of inline methods
//==============================================================================

inline bool NchooseKiterator::IsEnded() {
  return _v[0] >= 0;
}

inline int NchooseKiterator::operator()(int iIdx) {
  assert(0 <= iIdx && iIdx < _k);
  return _v[iIdx+1];
}

#endif
