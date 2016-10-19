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
 *   // Insert a colum between column 0 and 1.
 *   // This column is filled with value 5.
 *   myTab.insert_column(1, std::vector<int>(2,5));
 * 
 *   // Put the value 4 at line 0 and column 2
 *   myTab(0,2) = 4;
 * 
 *   // Resize the array to get an 3x3 array.
 *   // If ellements new elements are created, their value is 1.
 *   myTab.resize(3,3,1);
 * 
 *   // Print the array in the standart output
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
   * @param[in] iArray2d 2-dimensional array whose value will be copied
   */
  inline Array2d(const Array2d & iArray2d);

  /** @brief Destructor */
  inline ~Array2d();

  /**
   * @brief Erase a column of the array
   * @param[in] iJ Number of the column to erase
   */
  inline void erase_column(int iJ);

  /**
   * @brief Erase columns of the array
   * @param[in] iBegin Number of the first column to erase
   * @param[in] iEnd Number of the last column to erase (excluded)
   */
  inline void erase_columns(int iBegin, int iEnd);

  /**
   * @brief Erase a row of the array
   * @param[in] iI Number of the row to erase
   */
  inline void erase_row(int iI);

  /**
   * @brief Erase rows of the array
   * @param[in] iBegin Number of the first row to erase
   * @param[in] iEnd Number of the last row to erase
   */
  inline void erase_rows(int iBegin, int iEnd);

  /**
   * @brief Insert a column at the position iI
   * @param[in] iI position for insertion of the column
   * @param[in] iC vector containing element of the new column
   */
  inline void insert_column(int iI, const std::vector<T> & iC);

  /**
   * @brief Insert a row at the position iJ
   * @param[in] iJ position for insertion of the row
   * @param[in] iR vector containing element of the new row
   */
  inline void insert_row(int iJ, const std::vector<T> & iR);

  /**
   * @brief Add a column at the end of the array
   * @param[in] iC vector containing element of the new column
   */
  inline void push_back_column(const std::vector<T> & iC);

  /**
   * @brief Add a row at the end of the array 
   * @param[in] iR vector containing element of the new row
   */
  inline void push_back_row(const std::vector<T> & iR);
  
  /**
   * @brief Change the size of the array keeping its coefficients
   * @param[in] iP New number of rows of the array
   * @param[in] iN New Number of column of the array
   * @param[in] iVal Object whose content is copied to the added elements in case that new size 
   * is greater than the current container size. If not specified, the default constructor is 
   * used instead.
   */
  inline void resize(int iP, int iN, T iVal = T());

  /** @brief Exchange the values of the columns i and j */
  inline void swap_column(int i, int j);

  /** @brief Exchange the values of the rows i and j */
  inline void swap_row(int i, int j);

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

  /**
   * @brief Print the array on the standart output
   * @details The method is specialized for the following type: char, unsigned char, int, short
   * int, long int, unsigned int, unsigned short int, unsigned long int, float, double, long
   * double, std::string. In the other cases, the method prints nothing.
   */
  inline void print();

  /**
   * @brief Return the dot product between this array and the argument array.
   * @param[in] Array wih the same size
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
inline Array2d<T>::Array2d(const Array2d & iArray2d)
: _aT(iArray2d.nb_rows(), std::vector<T>(iArray2d.nb_columns(), T()))
{
}

template <class T>
inline Array2d<T>::~Array2d()
{
}

template <class T>
inline void Array2d<T>::erase_column(int iI)
{
  for (int j = 0; j < _aT.nb_rows(); j++)
    _aT[j].erase(_aT.begin()+iI);
}

template <class T>
inline void Array2d<T>::erase_columns(int iBegin, int iEnd)
{
  for (int j = 0; j < _aT.nb_rows(); j++)
    _aT[j].erase(_aT.begin()+iBegin, _aT.begin()+iEnd);
}

template <class T>
inline void Array2d<T>::erase_row(int iJ)
{
  if (0 <= iJ && iJ < _aT.nb_rows())
    _aT.erase(_aT.begin()+iJ);
}

template <class T>
inline void Array2d<T>::erase_rows(int iBegin, int iEnd)
{
  _aT.erase(_aT.begin()+iBegin, _aT.begin()+iEnd);
}

template <class T>
inline void Array2d<T>::insert_column(int iI, const std::vector<T> & iC)
{
  for (int j = 0; j < nb_rows(); j++)
    _aT[j].insert(_aT[j].begin()+iI, iC[j]);
}

template <class T>
inline void Array2d<T>::insert_row(int iJ, const std::vector<T> & iR)
{
  _aT.insert(_aT.begin()+iJ, iR);
}

template <class T>
inline void Array2d<T>::resize(int iP, int iN, T iVal)
{
  _aT.resize(iP);
  for (int i = 0; i < iP; i++)
    _aT[i].resize(iN, iVal);
}

template <class T>
inline void Array2d<T>::push_back_column(const std::vector<T> & iC)
{
  for (int j = 0; j < nb_rows(); j++)
    _aT[j].push_back(iC[j]);
}

template <class T>
inline void Array2d<T>::push_back_row(const std::vector<T> & iR)
{
  _aT.push_back(iR);
}

template <class T>
inline void Array2d<T>::swap_column(int i, int j)
{
  for (int k = 0; k < nb_rows(); k++)
    std::swap(_aT[k][i], _aT[k][j]);
}

template <class T>
inline void Array2d<T>::swap_row(int i, int j)
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

template <class T>
inline void Array2d<T>::print()
{
  std::cerr << "[WARNING] void Array2d<T>::print()" << std::endl
            << "The function is not specialized for this type." << std::endl;
}


#define PRINT_ARRAY2D()                         \
  for (int i = 0; i < nb_rows(); i++) {         \
    for (int j = 0; j < nb_columns(); j++)      \
      std::cout << (*this)(i,j) << "\t";        \
    std::cout << std::endl;                     \
  }                                             

template<> inline void Array2d<char>::print() { PRINT_ARRAY2D() }
template<> inline void Array2d<unsigned char>::print() { PRINT_ARRAY2D() }
template<> inline void Array2d<int>::print() { PRINT_ARRAY2D() }
template<> inline void Array2d<short int>::print() { PRINT_ARRAY2D() }
template<> inline void Array2d<long int>::print() { PRINT_ARRAY2D() }
template<> inline void Array2d<unsigned int>::print() { PRINT_ARRAY2D() }
template<> inline void Array2d<unsigned short int>::print() { PRINT_ARRAY2D() }
template<> inline void Array2d<unsigned long int>::print() { PRINT_ARRAY2D() }
template<> inline void Array2d<float>::print() { PRINT_ARRAY2D() }
template<> inline void Array2d<double>::print() { PRINT_ARRAY2D() }
template<> inline void Array2d<long double>::print() { PRINT_ARRAY2D() }
template<> inline void Array2d<std::string>::print() { PRINT_ARRAY2D() }


template <class T>
inline T Array2d<T>::dot_product(Array2d<T>& A)
{
  std::cerr << "[WARNING] T Array2d<T>::dot_product(const Array2d<T>&)" << std::endl
            << "The function is not specialized for this type." << std::endl;
}


#define ARRAY2D_DOT_PRODUCT(T,A)                                                        \
  T dot_prod = 0;                                                                       \
  if (nb_columns() != A.nb_columns() || nb_rows() != A.nb_rows()) {                     \
    std::cerr << "[ERROR] T Array2d<T>::dot_product(const Array2d<T>& A)" << std::endl  \
              << "The two array have not the same same size." << std::endl;             \
  }                                                                                     \
  else {                                                                                \
    for (int i = 0; i < nb_rows(); i++) {                                               \
      for (int j = 0; j < nb_columns(); j++) {                                          \
        dot_prod += ( (*this)(i,j) * A(i,j) );                                          \
      }                                                                                 \
    }                                                                                   \
  }                                                                                     \
  return dot_prod;


template<> inline int Array2d<int>::dot_product(Array2d<int>& A) { ARRAY2D_DOT_PRODUCT(int,A) }
template<> inline short int Array2d<short int>::dot_product(Array2d<short int>& A) { ARRAY2D_DOT_PRODUCT(short int,A) }
template<> inline long int Array2d<long int>::dot_product(Array2d<long int>& A) { ARRAY2D_DOT_PRODUCT(long int,A) }
template<> inline unsigned int Array2d<unsigned int>::dot_product(Array2d<unsigned int>& A) { ARRAY2D_DOT_PRODUCT(unsigned int,A) }
template<> inline unsigned short int Array2d<unsigned short int>::dot_product(Array2d<unsigned short int>& A) { ARRAY2D_DOT_PRODUCT(unsigned short int,A) }
template<> inline unsigned long int Array2d<unsigned long int>::dot_product(Array2d<unsigned long int>& A) { ARRAY2D_DOT_PRODUCT(unsigned long int,A) }
template<> inline float Array2d<float>::dot_product(Array2d<float>& A) { ARRAY2D_DOT_PRODUCT(float,A) }
template<> inline double Array2d<double>::dot_product(Array2d<double>& A) { ARRAY2D_DOT_PRODUCT(double,A) }
template<> inline long double Array2d<long double>::dot_product(Array2d<long double>& A) { ARRAY2D_DOT_PRODUCT(long double,A) }

#endif // ARRAY2D_H

