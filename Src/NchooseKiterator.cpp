#include "NchooseKiterator.h"

#include <iostream>

NchooseKiterator::NchooseKiterator():
  _n(0),
  _k(0)
{
}


NchooseKiterator::NchooseKiterator(int iN, int iK):
  _n(iN),
  _k(iK),
  _v(iK+1,iN)
{
  for (int i = 0; i < iK+1; i++)
    _v[i]=i-1;
}


NchooseKiterator::~NchooseKiterator()
{
}


void NchooseKiterator::operator++()
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


void NchooseKiterator::Print()
{
  unsigned int i;
  for(i = 1; i < _v.size(); i++)
    std::cout << _v[i] << " ";
  std::cout << std::endl;   
}


void NchooseKiterator::Reset(bool iEnd)
{
  _v[0] = iEnd ? -1 : 0;
  for (int i = 1; i < _k+1; i++)
    _v[i]=i-1;
}

