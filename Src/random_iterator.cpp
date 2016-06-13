/**
 * @file random_iterator.cpp
 * @author Etienne de Saint Germain
 * @date 2014
 * @brief File implementing random_iterator.h
 */


#include "random_iterator.h"
#include <iostream>
#include <algorithm>


Random_iterator::Random_iterator(int iN):
  _n(iN),
  _v(iN, 0),
  _it(_v.begin())
{
  for (int i = 0; i < _n; i++)
    _v[i] = i;
  std::random_shuffle(_v.begin(), _v.end());
}


Random_iterator::~Random_iterator()
{
}


void Random_iterator::reset()
{
  std::random_shuffle(_v.begin(), _v.end());
  _it = _v.begin();
}

