/**
 * @file tolerance.h
 * @author Cedric Gouvernet (cedric [dot] gouvernet [at] edf [dot] fr)
 * @date 2012
 * @brief Class for double comparison with tolerance.
 * @details This class was implemented by Cedric Gouvernet (cedric [dot] gouvernet [at] edf [dot] 
 * fr). The use and the modification are free but don't hesitate to suggest him some improvements.
 *
 * This version of this file was modified by Etienne de Saint Germain in 2015.
 */

#ifndef TOLERANCE_H
#define TOLERANCE_H


#include <cmath>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>


/** @brief Name of the measure unit in #Tolerance class */
typedef std::string Unite;


/**
 * @brief Class for double comparison with tolerance
 * @details Example of use of this class is given in the implementation of the function 
 * tolerance_test() in the main file.
 */
class Tolerance
{
public:
  //==============================================================================
  // Public methods
  //==============================================================================

  /**
   * @brief Constructor from an absolute and a relative tolerance
   * @param[in] atol Absolute tolerance. (0.5 denote a 0.5 Unite tolerance)
   * @param[in] rtol Relative tolerance. (0.5 denote a 50% tolerance)
   * @param[in] unite Name of the measure unite
   */
  inline Tolerance(const double& atol=1e-6, const double& rtol=1e-4, const Unite& unite=Unite());

  /**
   * @brief Destructor
   */
  inline ~Tolerance();

  /**
   * @brief Return a std::string describing the data of the class.
   */
  inline operator std::string() const;

  /**
   * @brief Return the absolute tolerance. (0.5 denote a 0.5 Unite tolerance)
   */
  inline const double& get_atol() const;

  /**
   * @brief Return the relative tolerance. (0.5 denote a 50% tolerance)
   */
  inline const double& get_rtol() const;

  /**
   * @brief Set the absolute tolerance. (0.5 denote a 0.5 Unite tolerance)
   * @param[in] atol New absolute tolerance. (0.5 denote a 0.5 Unite tolerance)
   */
  inline void set_atol(const double& atol);

  /**
   * @brief Set the relative tolerance. (0.5 denote a 50% tolerance)
   * @param[in] rtol New relative tolerance. (0.5 denote a 50% tolerance)
   */
  inline void set_rtol(const double& rtol);


	
  /**
   * @brief Decide if the number d1 is close to number d2 up to the absolute error and the 
   * relative error.
   * @param[in] d1 First number
   * @param[in] d2 Second number
   * @return True if d1 is close to d2 and false otherwise
   */
  inline bool close(const double& d1, const double& d2) const;

  /**
   * @brief Decide if the number d1 is lower but not close to the number d2 to the absolute error 
   * and the relative error.
   * @param[in] d1 First number
   * @param[in] d2 Second number
   * @return True if d1 is lower but not close to d2 and false otherwise
   */
  inline bool lower_not_close(const double& d1, const double& d2) const;

  /**
   * @brief Decide if the number d1 is lower or close to the number d2 to the absolute error and 
   * the relative error.
   * @param[in] d1 First number
   * @param[in] d2 Second number
   * @return True if d1 is lower or close to d2 and false otherwise
   */
  inline bool lower_or_close(const double& d1, const double& d2) const;

  /**
   * @brief Decide if the vector v1 is close to the vector v2 (component by component) up to the 
   * absolute error and the relative error.
   * @details If the size of the vectors are different, it only performs the comparison between 
   * the common components (up to the minimal size of the vectors).
   * @param[in] v1 First vector
   * @param[in] v2 Second vector
   * @return True if v1 is close to v2 and false otherwise
   */
  inline bool allclose(const std::vector<double>& v1, const std::vector<double>& v2) const;

  /**
   * @brief Decide if the vector v1 is close to the vector v2 (component by component) up to the 
   * absolute error and the relative error.
   * @details It uses a different tolerance (given in the vector v_tol) for each comparison.
   *
   * If the size of the vectors are different, it only performs the comparison between the 
   * common components (up to the minimal size of the vectors).
   * @param[in] v1 First vector
   * @param[in] v2 Second vector
   * @param[in] v_tol Vector of tolerance for the comparison of each component
   * @return True if v1 is close to v2 and false otherwise
   */
  inline static bool allclose(const std::vector<double >& v1,
                              const std::vector<double >& v2,
                              const std::vector<Tolerance*>& v_tol);


  /**
   * @brief Add a perturbation Epsilon to the number d in the sense of absolute and relative 
   * tolerances.
   * @param[in] d Value of the number
   * @return The value of d plus the perturbation Epsilon
   */
  inline double add_epsilon(const double& d) const;

  /**
   * @brief Subtract a perturbation Epsilon to the number d in the sense of absolute and relative 
   * tolerances.
   * @param[in] d Value of the number
   * @return The value of d minus the perturbation Epsilon
   */
  inline double substract_epsilon(const double& d) const;

  /**
   * @brief Round the number in the sense of the absolute tolerance
   * @details For example, if the absolute tolerance is 1e-2, the rounded value of 1.42365 will 
   * be 1.42
   * @param[in] d Value to round
   * @return The rounded value of d
   */
  inline double round(const double& d) const;

  /**
   * @brief Round the number in the sense of the absolute tolerance to upper value
   * @details For example, if the absolute tolerance is 1e-2, the rounded value of 1.42365 will 
   * be 1.43
   * @param[in] d Value to round
   * @return The rounded value of d
   */
  inline double round_up(const double& d) const;

  /**
   * @brief Round the number in the sense of the absolute tolerance to lower value
   * @details For example, if the absolute tolerance is 1e-2, the rounded value of 1.46871 will 
   * be 1.46
   * @param[in] d Value to round
   * @return The rounded value of d
   */
  inline double round_down(const double& d) const;

protected:
  //==============================================================================
  // Protected attributs
  //==============================================================================

  double _atol; /**< @brief Absolute tolerance */
  double _rtol; /**< @brief Relative tolerance */
  Unite _unite; /**< @brief Unite of measure */
};



//==============================================================================
// Implementation of inline methods
//==============================================================================


inline Tolerance::Tolerance(const double& atol, const double& rtol, const Unite& unite)
: _atol(atol),
  _rtol(rtol),
  _unite(unite)
{}


Tolerance::~Tolerance()
{}


inline Tolerance::operator std::string() const { 
  std::ostringstream oss;
  oss << "(atol: " << _atol << _unite;
  oss << " ; rtol: " << 100.0*_rtol << "%)";
  return oss.str();
}


inline const double& Tolerance::get_atol() const {
  return _atol;
}


inline const double& Tolerance::get_rtol() const {
  return _rtol;
}


inline void Tolerance::set_atol(const double& atol) {
  _atol = atol;
}


inline void Tolerance::set_rtol(const double& rtol) {
  _rtol = rtol;
}


inline bool Tolerance::close(const double& d1, const double& d2) const {
  const double ecart_abs = std::abs(d1-d2);
  return  (ecart_abs <= _atol) || (ecart_abs <= _rtol*std::max(std::abs(d1), std::abs(d2)));
}


inline bool Tolerance::lower_not_close(const double& d1, const double& d2) const {
  return  (d1 <= d2) && !close(d1, d2);
}


inline bool Tolerance::lower_or_close(const double& d1, const double& d2) const {
  return  (d1 <= d2) || close(d1, d2);
}


inline bool Tolerance::allclose(const std::vector<double >& v1, const std::vector<double >& v2) const {
  for (std::vector<double >::const_iterator it1=v1.begin(), it2=v2.begin(), v1_end=v1.end(), v2_end=v2.end();
       it1!=v1_end && it2!=v2_end;
       it1++, it2++){
    if (! close(*it1, *it2) ) {
      return false;
    }
  }
  return true;
}


inline bool Tolerance::allclose(const std::vector<double>& v1, const std::vector<double>& v2, const std::vector<Tolerance*>& v_tol){
  std::vector<Tolerance*>::const_iterator it_tol = v_tol.begin();
  const std::vector<Tolerance*>::const_iterator v_tol_end = v_tol.end();
  for (std::vector<double>::const_iterator it1=v1.begin(), it2=v2.begin(), v1_end=v1.end(), v2_end=v2.end();
       it1!=v1_end && it2!=v2_end && it_tol!=v_tol_end;
       it1++, it2++, it_tol++)
  {
    if (*it_tol && ! (*it_tol)->close(*it1, *it2) ) {
      return false;
    }
  }
  return true;
}


inline double Tolerance::add_epsilon(const double& d) const {
  return  d + _atol + (std::abs(d)+_atol)*_rtol;
}


inline double Tolerance::substract_epsilon(const double& d) const {
  return  d - _atol - (std::abs(d)+_atol)*_rtol;
}


inline double Tolerance::round(const double& d) const {
  const int nb_chiffres_apres_virgule = (_atol>0) ?
    std::max(0, static_cast<int>(-std::log10(_atol)+0.5)) :
    7;
  const double div = std::pow(10.0, nb_chiffres_apres_virgule);
  const double out = std::floor(d * div + 0.5) / div;
  return out;
}


inline double Tolerance::round_up(const double& d) const {
  return round(d + 0.499999999*_atol);
}


inline double Tolerance::round_down(const double& d) const {
  return round(d - 0.5*_atol);
}



#endif //TOLERANCE_H
