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


/** @brief Return user time */
double get_wall_time();

/** @brief Return CPU time */
double get_cpu_time();


#endif // TIME_TOOLS_H



