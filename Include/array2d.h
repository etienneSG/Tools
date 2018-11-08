/**
 * @file array2d.h
 * @author Etienne de Saint Germain
 * @date 2014
 * @brief Implementtion of a template for dynamic array with two dimensions.
 */


#ifndef ARRAY2D_H
#define ARRAY2D_H

#include <algorithm>
#include <assert.h>
#include <iostream>
#include <string>
#include <vector>


/**
 * @brief Template for dynamic array with two dimensions.
 * @details A minimal example is given by the following code:
 * @code{cpp}
 * #include "array2d.h" // to use Array2d
 * #include <iostream>  // to stream the output
 * #include <vector>    // to use vector
 *
 * int main()
 * {
 *   // Create an array with 2 line and 3 column.
 *   // This array is filled with value 0.
 *   Array2d<int> myTab(2,3);
 * 
 *   // Insert a column between column 0 and 1.
 *   // This column is filled with value 5.
 *   myTab.insert_column(1, std::vector<int>(2,5));
 * 
 *   // Put the value 4 at line 0 and column 2
 *   myTab(0,2) = 4;
 * 
 *   // Resize the array to get an 3x3 array.
 *   // If elements new elements are created, their value is 1.
 *   myTab.resize(3,3,1);
 * 
 *   // Print the array in the standard output
 *   for (int j = 0; j < myTab.nb_rows(); j++) {
 *     for (int i = 0; i < myTab.nb_columns(); i++)
 *       std::cout << myTab(j,i) << " ";
 *     std::cout << std::endl;
 *   }
 * 
 *   return 0;
 * }
 * @endcode
 * The expected output is:
 * @code{txt}
 * 0 5 4 
 * 0 5 0 
 * 1 1 1 
 * @endcode
 *
 * @b Exception @b safety:
 * If the container size is greater than n, the function never throws exceptions (no-throw 
 * guarantee). Otherwise, the behavior is undefined.
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
  inline Array2d(int iP = 0, int iN = 0);
  
  /**
   * @brief Copy constructor
   * @param[in] iArray2d 2-dimensional array whose values will be copied
   */
  inline Array2d(Array2d & iArray2d);

  /** @brief Destructor */
  inline ~Array2d();

  /**
   * @brief Resize the array and fill it with the argument array
   * @param[in] iArray2d Array whose will must be copied
   */
  inline void copy(Array2d& iArray2d);

  /**
   * @brief Erase a column of the array
   * @param[in] iJ Index of the column to erase
   */
  inline void erase_column(int iJ);

  /**
   * @brief Erase columns of the array
   * @param[in] iBegin Index of the first column to erase
   * @param[in] iEnd Index of the last column to erase (excluded)
   */
  inline void erase_columns(int iBegin, int iEnd);

  /**
   * @brief Erase a row of the array
   * @param[in] iI Index of the row to erase
   */
  inline void erase_row(int iI);

  /**
   * @brief Erase rows of the array
   * @param[in] iBegin Index of the first row to erase
   * @param[in] iEnd Index of the last row to erase
   */
  inline void erase_rows(int iBegin, int iEnd);

  /**
   * @brief Insert a column at the position iI
   * @param[in] iI Index for insertion of the column
   * @param[in] iC Vector containing elements of the new column
   */
  inline void insert_column(int iI, const std::vector<T> & iC);

  /**
   * @brief Insert a row at the position iJ
   * @param[in] iJ Index for insertion of the row
   * @param[in] iR Vector containing elements of the new row
   */
  inline void insert_row(int iJ, const std::vector<T> & iR);

  /**
   * @brief Add a column at the end of the array
   * @param[in] iC Vector containing elements of the new column
   */
  inline void push_back_column(const std::vector<T> & iC);

  /**
   * @brief Add a row at the end of the array 
   * @param[in] iR Vector containing elements of the new row
   */
  inline void push_back_row(const std::vector<T> & iR);
  
  /**
   * @brief Change the size of the array keeping its elements
   * @param[in] iP New number of rows of the array
   * @param[in] iN New Number of columns of the array
   * @param[in] iVal Object whose content is copied to the added elements (in case that new size 
   * is greater than the current container size). If not specified, the default constructor is 
   * used instead.
   */
  inline void resize(int iP, int iN, T iVal = T());
  
  /**
   * @brief Removes all elements from the array (which are destroyed), leaving the container
   * with a size of 0.
   */
  inline void clear();

  /** @brief Exchange the values of the columns i and j */
  inline void swap_column(int i, int j);

  /** @brief Exchange the values of the rows i and j */
  inline void swap_row(int i, int j);

  /** @brief Return the number of rows of the array */
  inline int nb_rows();

  /** @brief Return the number of columns of the array */
  inline int nb_columns();

  /**
   * @brief Write access to coefficients of the array
   * @param[in] iJ Index of the row
   * @param[in] iI Index of the column
   */
  inline T& operator()(int iJ, int iI);

  /**
   * @brief Read access to coefficients of the array
   * @param[in] iJ Index of the row
   * @param[in] iI Index of the column
   */
  inline const T& operator()(int iJ, int iI)const;

  /**
   * @brief Print the array on the standard output
   * @details The method is specialized for the following type: char, unsigned char, int, short
   * int, long int, unsigned int, unsigned short int, unsigned long int, float, double, long
   * double, std::string. In the other cases, the method prints nothing.
   */
  inline void print();

  /**
   * @brief Return the dot product between this array and the argument array.
   * @param[in] A Array with the same size
   * @details The method is specialized for the following type: int, short, int, long int,
   * unsigned int, unsigned short int, unsigned long int, float, double, long, double.
   * @return The dot product of the two arrays. If T has no operator * (that is, if the method is 
   * not specialized for the type T), the method returns a default construction of T.
   */
  inline T dot_product(Array2d<T>& A);

 protected:
  std::vector< std::vector<T> > _aT; /**< @brief Array containing the values */
  
};


//==============================================================================
// Implementation of methods
//==============================================================================

template <class T>
inline Array2d<T>::Array2d(int iP, int iN)
: _aT(iP, std::vector<T>(iN, T()))
{
}

template <class T>
inline Array2d<T>::Array2d(Array2d & iArray2d)
: _aT(iArray2d._aT)
{
}

template <class T>
inline Array2d<T>::~Array2d()
{
}

template <class T>
inline void Array2d<T>::copy(Array2d& iArray2d)
{
  unsigned int nb_rows = iArray2d.nb_rows();
  unsigned int nb_cols = iArray2d.nb_columns();
  resize(nb_rows,nb_cols);
  for (unsigned int r = 0; r < nb_rows; r++) {
    for (unsigned int c = 0; c < nb_cols; c++) {
      (*this)(r,c) = iArray2d(r,c);
    }
  }
}

template <class T>
inline void Array2d<T>::erase_column(int iI)
{
  if (0 <= iI && iI < nb_columns()) {
    for (int j = 0; j < _aT.size(); j++)
      _aT[j].erase(_aT.begin()+iI);
  }
  else {
    std::cerr << "[WARNING] void Array2d<T>::erase_column(int)" << std::endl
              << "Column index out of range. No column removed." << std::endl;
    assert(false);
  }
}

template <class T>
inline void Array2d<T>::erase_columns(int iBegin, int iEnd)
{
  if (0 <= iBegin && iBegin <= iEnd && iEnd <= nb_columns()) {
    for (int j = 0; j < _aT.size(); j++)
      _aT[j].erase(_aT[j].begin()+iBegin, _aT[j].begin()+iEnd);
  }
  else {
    std::cerr << "[WARNING] void Array2d<T>::erase_columns(int,int)" << std::endl
              << "Column index out of range. No columns removed." << std::endl;
    assert(false);
  }
}

template <class T>
inline void Array2d<T>::erase_row(int iJ)
{
  if (0 <= iJ && iJ < nb_rows()) {
    _aT.erase(_aT.begin()+iJ);
  }
  else {
    std::cerr << "[WARNING] void Array2d<T>::erase_row(int)" << std::endl
              << "Row index out of range. No row removed." << std::endl;
    assert(false);
  }
}

template <class T>
inline void Array2d<T>::erase_rows(int iBegin, int iEnd)
{
  if (0 <= iBegin && iBegin <= iEnd && iEnd <= nb_rows()){
    _aT.erase(_aT.begin()+iBegin, _aT.begin()+iEnd);
  }
  else {
    std::cerr << "[WARNING] void Array2d<T>::erase_rows(int,int)" << std::endl
              << "Row index out of range. No rows removed." << std::endl;
    assert(false);
  }
}

template <class T>
inline void Array2d<T>::insert_column(int iI, const std::vector<T> & iC)
{
  if (nb_rows()==0) {
    _aT.assign(iC.size(), std::vector<T>());
  }
  if (0 <= iI && iI <= nb_columns()) {
    if (iC.size() == (unsigned int)nb_rows()) {
      for (int j = 0; j < nb_rows(); j++)
        _aT[j].insert(_aT[j].begin()+iI, iC[j]);
    }
    else {
      std::cerr << "[WARNING] void Array2d<T>::insert_column(int, const std::vector<T>&)" << std::endl
                << "New column size different from array column size. No column added." << std::endl;
      assert(false);
    }
  }
  else {
    std::cerr << "[WARNING] void Array2d<T>::insert_column(int, const std::vector<T>&)" << std::endl
              << "Column index out of range. No column added." << std::endl;
    assert(false);
  }
}


template <class T>
inline void Array2d<T>::insert_row(int iJ, const std::vector<T> & iR)
{
  if (0 <= iJ && iJ <= nb_rows()) {
    if (iR.size() == (unsigned int)nb_columns()) {
      _aT.insert(_aT.begin()+iJ, iR);
    }
    else {
      std::cerr << "[WARNING] void Array2d<T>::insert_row(int, const std::vector<T>&)" << std::endl
                << "New row size different from array row size. No row added." << std::endl;
      assert(false);
    }
  }
  else {
    std::cerr << "[WARNING] void Array2d<T>::insert_row(int, const std::vector<T>&)" << std::endl
              << "Row index out of range. No row added." << std::endl;
    assert(false);
  }
}


template <class T>
inline void Array2d<T>::resize(int iP, int iN, T iVal)
{
  _aT.resize(iP);
  for (int i = 0; i < iP; i++)
    _aT[i].resize(iN, iVal);
}


template <class T>
inline void Array2d<T>::clear()
{
  _aT.clear();
}


template <class T>
inline void Array2d<T>::push_back_column(const std::vector<T> & iC)
{
  if (nb_rows()==0) {
    _aT.assign(iC.size(), std::vector<T>());
  }
  if (iC.size() == (unsigned int)nb_rows()) {
    for (int j = 0; j < nb_rows(); j++)
      _aT[j].push_back(iC[j]);
  }
  else {
    std::cerr << "[WARNING] void Array2d<T>::push_back_column(const std::vector<T>&)" << std::endl
              << "New column size different from array column size. No column added." << std::endl;
    assert(false);
  }
}

template <class T>
inline void Array2d<T>::push_back_row(const std::vector<T> & iR)
{
  if (nb_rows()==0 || iR.size() == (unsigned int)nb_columns()) {
    _aT.push_back(iR);
  }
  else {
    std::cerr << "[WARNING] void Array2d<T>::push_back_row(const std::vector<T>&)" << std::endl
              << "New row size different from array row size. No row added." << std::endl;
    assert(false);
  }
}

template <class T>
inline void Array2d<T>::swap_column(int i, int j)
{
  if (0 <= i && i < nb_columns() && 0 <= j && j < nb_columns()) {
    for (int k = 0; k < nb_rows(); k++)
      std::swap(_aT[k][i], _aT[k][j]);
  }
  else {
    std::cerr << "[WARNING] void Array2d<T>::swap_column(int,int)" << std::endl
              << "Column index out of range. No column swapped." << std::endl;
    assert(false);
  }
}

template <class T>
inline void Array2d<T>::swap_row(int i, int j)
{
  if (0 <= i && i < nb_rows() && 0 <= j && j < nb_rows()) {
    std::swap(_aT[i], _aT[j]);
  }
  else {
    std::cerr << "[WARNING] void Array2d<T>::swap_row(int,int)" << std::endl
              << "Row index out of range. No row swapped." << std::endl;
    assert(false);
  }
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
  if (0 <= iJ && iJ < nb_rows()) {
    if (0 <= iI && iI < nb_columns()) {
      return _aT[iJ][iI];
    }
    else {
      std::cerr << "[WARNING] void Array2d<T>::operator()(int,int)" << std::endl
                << "Column index out of range." << std::endl;
      assert(false);
    }
  }
  else {
    std::cerr << "[WARNING] void Array2d<T>::operator()(int,int)" << std::endl
              << "Row index out of range." << std::endl;
    assert(false);
  }
  return _aT[0][0];
}

template <class T>
inline const T& Array2d<T>::operator()(int iJ, int iI)const
{
  if (0 <= iJ && iJ < nb_rows()) {
    if (0 <= iI && iI < nb_columns()) {
      return _aT[iJ][iI];
    }
    else {
      std::cerr << "[WARNING] void Array2d<T>::operator()(int,int)" << std::endl
                << "Column index out of range." << std::endl;
      assert(false);
    }
  }
  else {
    std::cerr << "[WARNING] void Array2d<T>::operator()(int,int)" << std::endl
              << "Row index out of range." << std::endl;
    assert(false);
  }
  return _aT[0][0];
}


template <class T>
inline void Array2d<T>::print()
{
  std::cerr << "[WARNING] void Array2d<T>::print()" << std::endl
            << "The function is not specialized for this type." << std::endl;
}



#ifndef DOXYGEN_SHOULD_SKIP_THIS  // Only Macro definitions for specialization of template

#define ARRAY2D_PRINT(T)                        \
  template<>                                    \
  inline void Array2d<T>::print()               \
  {                                             \
    for (int i = 0; i < nb_rows(); i++) {       \
      for (int j = 0; j < nb_columns(); j++)    \
        std::cout << (*this)(i,j) << "\t";      \
      std::cout << std::endl;                   \
    }                                           \
  }                     

ARRAY2D_PRINT(char)
ARRAY2D_PRINT(unsigned char)
ARRAY2D_PRINT(int)
ARRAY2D_PRINT(short int)
ARRAY2D_PRINT(long int)
ARRAY2D_PRINT(unsigned int)
ARRAY2D_PRINT(unsigned short int)
ARRAY2D_PRINT(unsigned long int)
ARRAY2D_PRINT(float)
ARRAY2D_PRINT(double)
ARRAY2D_PRINT(long double)
ARRAY2D_PRINT(std::string)

#endif // DOXYGEN_SHOULD_SKIP_THIS



template <class T>
inline T Array2d<T>::dot_product(Array2d<T>& A)
{
  std::cerr << "[WARNING] T Array2d<T>::dot_product(const Array2d<T>&)" << std::endl
            << "The function is not specialized for this type." << std::endl;
}


#ifndef DOXYGEN_SHOULD_SKIP_THIS  // Only Macro definitions for specialization of template

#define ARRAY2D_DOT_PRODUCT(T)                                          \
  template<>                                                            \
  inline T Array2d<T>::dot_product(Array2d<T>& A)                       \
  {                                                                     \
    T dot_prod = 0;                                                     \
    if (nb_columns() != A.nb_columns() || nb_rows() != A.nb_rows()) {   \
      std::cerr << "[ERROR] T Array2d<T>::dot_product(const Array2d<T>& A)" << std::endl \
                << "The two array have not the same same size." << std::endl; \
    }                                                                   \
    else {                                                              \
      for (int i = 0; i < nb_rows(); i++) {                             \
        for (int j = 0; j < nb_columns(); j++) {                        \
          dot_prod += ( (*this)(i,j) * A(i,j) );                        \
        }                                                               \
      }                                                                 \
    }                                                                   \
    return dot_prod;                                                    \
  }

ARRAY2D_DOT_PRODUCT(int)
ARRAY2D_DOT_PRODUCT(short int)
ARRAY2D_DOT_PRODUCT(long int)
ARRAY2D_DOT_PRODUCT(unsigned int)
ARRAY2D_DOT_PRODUCT(unsigned short int)
ARRAY2D_DOT_PRODUCT(unsigned long int)
ARRAY2D_DOT_PRODUCT(float)
ARRAY2D_DOT_PRODUCT(double)
ARRAY2D_DOT_PRODUCT(long double)

#endif // DOXYGEN_SHOULD_SKIP_THIS


#endif // ARRAY2D_H

