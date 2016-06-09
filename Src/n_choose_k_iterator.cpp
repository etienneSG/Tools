/**
 * @file n_choose_k_iterator.cpp
 * @author Etienne de Saint Germain
 * @date 2016
 * @brief File implementing n_choose_k_iterator.h
 */


#include "n_choose_k_iterator.h"

#include <iostream>

N_choose_K_iterator::N_choose_K_iterator():
  _n(0),
  _k(0)
{
}


N_choose_K_iterator::N_choose_K_iterator(int iN, int iK):
  _n(iN),
  _k(iK),
  _v(iK+1,iN)
{
  for (int i = 0; i < iK+1; i++)
    _v[i]=i-1;
}


N_choose_K_iterator::~N_choose_K_iterator()
{
}


void N_choose_K_iterator::operator++()
{
  int l=_k;
  _v[l]++;
  while (l > 0 && _v[l] >= (_n+l-_k) )
  {
    _v[l-1]++;
    _v[l]=0;
    l--;
  }
  unsigned int i;
  for (i = 1 ; i < _v.size(); i++)
  {
    if (_v[i]<=_v[i-1])
      _v[i]=_v[i-1]+1;
  }
}


void N_choose_K_iterator::print()
{
  unsigned int i;
  for(i = 1; i < _v.size(); i++)
    std::cout << _v[i] << " ";
  std::cout << std::endl;   
}


void N_choose_K_iterator::reset(bool iEnd)
{
  _v[0] = iEnd ? -1 : 0;
  for (int i = 1; i < _k+1; i++)
    _v[i]=i-1;
}

