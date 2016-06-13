/**
 * @file hcube_iterator.cpp
 * @author Etienne de Saint Germain
 * @date 2014
 * @brief File implementing hcube_iterator.h
 */


#include "hcube_iterator.h"
#include <iostream>

Hcube_iterator::Hcube_iterator():
  _n(0),
  _k(0)
{
}


Hcube_iterator::Hcube_iterator(int iN, int iK):
  _n(iN),
  _k(iK),
  _v(iN+1, 0)
{
  _v[0]=-1;
}


Hcube_iterator::~Hcube_iterator()
{
}


void Hcube_iterator::operator++()
{
  int l=_n;
  _v[l]++;
  while (l > 0 && _v[l] >= _k )
  {
    _v[l-1]++;
    _v[l]=0;
    l--;
  }
}

void Hcube_iterator::print()
{
  unsigned int i;
  for(i = 1; i < _v.size(); i++)
    std::cout << _v[i] << " ";
  std::cout << std::endl;   
}

void Hcube_iterator::reset()
{
  _v[0]=-1;
  unsigned int i;
  for(i = 1; i < _v.size(); i++)
    _v[i] = 0;
}

