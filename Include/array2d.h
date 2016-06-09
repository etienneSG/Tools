/**
 * @file array2d.h
 * @author Etienne de Saint Germain
 * @date 2014
 * @brief Template for dynamic array with two dimensions.
 * @details WARNING: this class DO NOT verify the validity of a range called by the user!
 */


#ifndef ARRAY2D_H
#define ARRAY2D_H

#include <algorithm>
#include <assert.h>
#include <iostream>
#include <vector>


/**
 * @brief Template for dynamic array with two dimensions.
 */
template <class T>
class Array2d
{
 public:
  /**
   * @brief Constructor
   * @param[in] iP Number of rows of the array
   * @param[in] iN Number of columns of the array
   */
  Array2d(int iP = 0, int iN = 0);
  
  /**
   * @brief Copy constructor
   * @param[in] iArray2d 2-dimensional array whose value will be copied
   */
  Array2d(const Array2d & iArray2d);

  /** @brief Destructor */
  ~Array2d();

  /**
   * @brief Erase a column of the array
   * @param[in] iJ Number of the column to erase
   */
  void erase_column(int iJ);

  /**
   * @brief Erase columns of the array
   * @param[in] iBegin Number of the first column to erase
   * @param[in] iEnd Number of the last column to erase (excluded)
   */
  void erase_columns(int iBegin, int iEnd);

  /**
   * @brief Erase a row of the array
   * @param[in] iI Number of the row to erase
   */
  void erase_row(int iI);

  /**
   * @brief Erase rows of the array
   * @param[in] iBegin Number of the first row to erase
   * @param[in] iEnd Number of the last row to erase
   */
  void erase_rows(int iBegin, int iEnd);

  /**
   * @brief Insert a column at the position iI
   * @param[in] iI position for insertion of the column
   * @param[in] iC vector containing element of the new column
   */
  void insert_column(int iI, const std::vector<T> & iC);

  /**
   * @brief Insert a row at the position iJ
   * @param[in] iJ position for insertion of the row
   * @param[in] iR vector containing element of the new row
   */
  void insert_row(int iJ, const std::vector<T> & iR);

  /**
   * @brief Add a column at the end of the array
   * @param[in] iC vector containing element of the new column
   */
  void push_back_column(const std::vector<T> & iC);

  /**
   * @brief Add a row at the end of the array 
   * @param[in] iR vector containing element of the new row
   */
  void push_back_row(const std::vector<T> & iR);
  
  /**
   * @brief Change the size of the array keeping its coefficients
   * @param[in] iP New number of rows of the array
   * @param[in] iN New Number of column of the array
   */
  void resize(int iP, int iN);

  /** @brief Exchange the values of the columns i and j */
  void swap_column(int i, int j);

  /** @brief Exchange the values of the rows i and j */
  void swap_row(int i, int j);

  /** @brief Return the number of rows of the array */
  inline int nb_rows();

  /** @brief Return the number of columns of the array */
  inline int nb_columns();

  /**
   * @brief Write acces to coefficients of the array
   * @param[in] iJ Index of the row
   * @param[in] iI Index of the column
   */
  inline T& operator()(int iJ, int iI);

  /**
   * @brief Read acces to coefficients of the array
   * @param[in] iJ Index of the row
   * @param[in] iI Index of the column
   */
  inline const T& operator()(int iJ, int iI)const;

 protected:
  std::vector< std::vector<T> > _aT; /**< @brief Array containing the values */
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
: _aT(iArray2d.nb_rows(), std::vector<T>(iArray2d.nb_columns(), T()))
{
}

template <class T>
Array2d<T>::~Array2d()
{
}

template <class T>
void Array2d<T>::erase_column(int iI)
{
  for (int j = 0; j < _aT.nb_rows(); j++)
    _aT[j].erase(_aT.begin()+iI);
}

template <class T>
void Array2d<T>::erase_columns(int iBegin, int iEnd)
{
  for (int j = 0; j < _aT.nb_rows(); j++)
    _aT[j].erase(_aT.begin()+iBegin, _aT.begin()+iEnd);
}

template <class T>
void Array2d<T>::erase_row(int iJ)
{
  if (0 <= iJ && iJ < _aT.nb_rows())
    _aT.erase(_aT.begin()+iJ);
}

template <class T>
void Array2d<T>::erase_rows(int iBegin, int iEnd)
{
  _aT.erase(_aT.begin()+iBegin, _aT.begin()+iEnd);
}

template <class T>
void Array2d<T>::insert_column(int iI, const std::vector<T> & iC)
{
  for (int j = 0; j < nb_rows(); j++)
    _aT[j].insert(_aT[j].begin()+iI, iC[j]);
}

template <class T>
void Array2d<T>::insert_row(int iJ, const std::vector<T> & iR)
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
  for (int j = 0; j < nb_rows(); j++)
    _aT[j].push_back(iC[j]);
}

template <class T>
void Array2d<T>::push_back_row(const std::vector<T> & iR)
{
  _aT.push_back(iR);
}

template <class T>
void Array2d<T>::swap_column(int i, int j)
{
  for (int k = 0; k < nb_rows(); k++)
    std::swap(_aT[k][i], _aT[k][j]);
}

template <class T>
void Array2d<T>::swap_row(int i, int j)
{
  std::swap(_aT[i], _aT[j]);
}

template <class T>
inline int Array2d<T>::nb_rows()
{
  return _aT.size();
}

template <class T>
inline int Array2d<T>::nb_columns()
{
  return (nb_rows() ? _aT[0].size() : 0);
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


#endif // ARRAY2D_H

