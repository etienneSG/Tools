//==============================================================================
// 
// Class Array2d:
//   Template for dynamic array with two dimensions.
// The array has p rows and n columns.
//
// WARNING : this class DO NOT verify the validity of a range called by the
// user!
//
//==============================================================================

#ifndef ARRAY2D_H
#define ARRAY2D_H

#include <algorithm>
#include <assert.h>
#include <iostream>
#include <vector>

template <class T>
class Array2d
{
public:
  /**
   * Constructor
   * @param iP: Number of rows of the array
   * @param iN: Number of columns of the array
   */
  Array2d(int iP = 0, int iN = 0);
  
  /** Copy constructor */
  Array2d(const Array2d & iArray2d);

  /** Destructor */
  ~Array2d();

  /**
   * Erase a column of the array
   * @param iN: Number of the row to erase
   */
  void eraseColumn(int iJ);

  /**
   * Erase columns of the array
   * @param iBegin: Number of the first row to erase
   * @param iEnd:   Number of the last row to erase
   */
  void eraseColumns(int iBegin, int iEnd);

  /**
   * Erase a row of the array
   * @param iP: Number of the row to erase
   */
  void eraseRow(int iI);

  /**
   * Erase rows of the array
   * @param iBegin: Number of the first row to erase
   * @param iEnd:   Number of the last row to erase
   */
  void eraseRows(int iBegin, int iEnd);

  /** Insert a column at the position iI */
  void insertColumn(int iI, const std::vector<T> & iC);

  /** Insert a row at the position iJ */
  void insertRow(int iJ, const std::vector<T> & iR);

  /** Add a column at the end of the array */
  void push_back_column(const std::vector<T> & iC);

  /** Add a row at the end of the array */
  void push_back_row(const std::vector<T> & iR);
  
  /**
   * Change the size of the array keeping its coefficients
   * @param iP: New number of rows of the array
   * @param iN: New Number of column of the array
   */
  void resize(int iP, int iN);

  /** Exchange the values of the columns i and j */
  void swapColumn(int i, int j);

  /** Exchange the values of the rows i and j */
  void swapRow(int i, int j);

  /** Return the number of rows of the array */
  inline int P();

  /** Return the number of columns of the array */
  inline int N();

  /**
   * Reading and writing acces to coefficients of the array
   * @param iJ: Index of the row
   * @param iI: Index of the column
   */
  inline T& operator()(int iJ, int iI);
  inline const T& operator()(int iJ, int iI)const;

protected:
  std::vector< std::vector<T> > _aT; // Array containing the values
};


//==============================================================================
// Implementation of methods
//==============================================================================

template <class T>
Array2d<T>::Array2d(int iP, int iN)
: _aT(iP, std::vector<T>(iN, T()))
{
}

template <class T>
Array2d<T>::Array2d(const Array2d & iArray2d)
: _aT(iArray2d.P(), std::vector<T>(iArray2d.N(), T()))
{
}

template <class T>
Array2d<T>::~Array2d()
{
}

template <class T>
void Array2d<T>::eraseColumn(int iI)
{
  for (int j = 0; j < _aT.P(); j++)
    _aT[j].erase(_aT.begin()+iI);
}

template <class T>
void Array2d<T>::eraseColumns(int iBegin, int iEnd)
{
  for (int j = 0; j < _aT.P(); j++)
    _aT[j].erase(_aT.begin()+iBegin, _aT.begin()+iEnd);
}

template <class T>
void Array2d<T>::eraseRow(int iJ)
{
  if (0 <= iJ && iJ < _aT.P())
    _aT.erase(_aT.begin()+iJ);
}

template <class T>
void Array2d<T>::eraseRows(int iBegin, int iEnd)
{
  _aT.erase(_aT.begin()+iBegin, _aT.begin()+iEnd);
}

template <class T>
void Array2d<T>::insertColumn(int iI, const std::vector<T> & iC)
{
  for (int j = 0; j < P(); j++)
    _aT[j].insert(_aT[j].begin()+iI, iC[j]);
}

template <class T>
void Array2d<T>::insertRow(int iJ, const std::vector<T> & iR)
{
  _aT.insert(_aT.begin()+iJ, iR);
}

template <class T>
void Array2d<T>::resize(int iP, int iN)
{
  _aT.resize(iP);
  for (int i = 0; i < iP; i++)
    _aT[i].resize(iN);
}

template <class T>
void Array2d<T>::push_back_column(const std::vector<T> & iC)
{
  for (int j = 0; j < P(); j++)
    _aT[j].push_back(iC[j]);
}

template <class T>
void Array2d<T>::push_back_row(const std::vector<T> & iR)
{
  _aT.push_back(iR);
}

template <class T>
void Array2d<T>::swapColumn(int i, int j)
{
  for (int k = 0; k < P(); k++)
    std::swap(_aT[k][i], _aT[k][j]);
}

template <class T>
void Array2d<T>::swapRow(int i, int j)
{
  std::swap(_aT[i], _aT[j]);
}

template <class T>
inline int Array2d<T>::P()
{
  return _aT.size();
}

template <class T>
inline int Array2d<T>::N()
{
  return (P() ? _aT[0].size() : 0);
}

template <class T>
inline T& Array2d<T>::operator()(int iJ, int iI)
{
  return _aT[iJ][iI];
}

template <class T>
inline const T& Array2d<T>::operator()(int iJ, int iI)const
{
  return _aT[iJ][iI];
}


#endif

