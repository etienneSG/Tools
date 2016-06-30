/**
 * @file time_tools.h
 * @author Etienne de Saint Germain
 * @date 2014
 * @brief Functions to get CPU and user time.
 * @details Two functions:
 * - get_wall_time() returns the user time.
 * - get_cpu_time() returns the CPU time.
 */


#ifndef TIME_TOOLS_H
#define TIME_TOOLS_H


//==============================================================================
// Declaration of functions
//==============================================================================


/** @brief Return user time */
inline double get_wall_time();

/** @brief Return CPU time */
inline double get_cpu_time();




//==============================================================================
// Implementation of functions
//==============================================================================


// Windows
#ifdef _WIN32
#include <Windows.h>


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
#include <time.h>

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



#endif // TIME_TOOLS_H

