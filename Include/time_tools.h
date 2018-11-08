/**
 * @file time_tools.h
 * @author Etienne de Saint Germain
 * @date 2014
 * @brief Functions to get CPU and user time.
 * @details Three functions:
 * - get_wall_time() returns the user time.
 * - get_cpu_time() returns the CPU time.
 * - get_human_readable_time() returns a string containing the date and time information
 * in a human-readable format.
 */


#ifndef TIME_TOOLS_H
#define TIME_TOOLS_H


#include <algorithm>
#include <string>
#include <time.h>

//==============================================================================
// Declaration of functions
//==============================================================================


/** @brief Return user time */
inline double get_wall_time();

/** @brief Return CPU time */
inline double get_cpu_time();

/** @brief Return a string containing the date and time information in a human-readable format.*/
inline std::string get_human_readable_time();



//==============================================================================
// Implementation of functions
//==============================================================================


// Windows
#ifdef _WIN32
#include <windows.h>


inline double get_wall_time(){
  LARGE_INTEGER time,freq;
  if (!QueryPerformanceFrequency(&freq)){
    //  Handle error
    return 0;
  }
  if (!QueryPerformanceCounter(&time)){
    //  Handle error
    return 0;
  }
  return (double)time.QuadPart / freq.QuadPart;
}

inline double get_cpu_time(){
  FILETIME a,b,c,d;
  if (GetProcessTimes(GetCurrentProcess(),&a,&b,&c,&d) != 0){
    //  Returns total user time.
    //  Can be tweaked to include kernel times as well.
    return
    (double)(d.dwLowDateTime |
    ((unsigned long long)d.dwHighDateTime << 32)) * 0.0000001;
  }else{
    //  Handle error
    return 0;
  }
}

#endif //_WIN32



//  Posix/Linux
#ifdef __linux__
#include <sys/time.h>

inline double get_wall_time(){
  struct timeval time;
  if (gettimeofday(&time,NULL)){
    //  Handle error
    return 0;
  }
  return (double)time.tv_sec + (double)time.tv_usec * .000001;
}

inline double get_cpu_time(){
  return (double)clock() / CLOCKS_PER_SEC;
}

#endif // __linux__


inline std::string get_human_readable_time()
{
  time_t rawtime;
  struct tm * timeinfo;

  time ( &rawtime );
  timeinfo = localtime ( &rawtime );
  
  std::string date = (std::string)asctime(timeinfo);
  date.erase( std::remove( date.begin(), date.end(), '\n' ), date.end() ) ;
  date.erase( std::remove( date.begin(), date.end(), '\r' ), date.end() ) ;
  
  return date;
}



#endif // TIME_TOOLS_H

