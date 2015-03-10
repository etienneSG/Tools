#include "Array2d.h"
#include "HcubeIterator.h"
#include "KnapSack.h"
#include "NchooseKiterator.h"
#include "QuickSort.h"
#include "RandomIterator.h"
#include "TimeTools.h"

#include <algorithm>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <vector>

using namespace std;


int Array2dTest()
{
  cout << "********* Array2d test **********" << endl;
  int fail = 0;

  int p = 3; int n = 4;
  Array2d<int> tab(p,n);
  for (int j = 0; j < tab.P(); j++)
    tab(j,0) = j+1;
  for (int i = 0; i < tab.N(); i++)
    tab(1,i) = i+2;
  tab.resize(4,2);
  tab.push_back_column(vector<int>(4,9));
  tab.insertRow(0, vector<int>(3,6));
  tab.insertColumn(1, vector<int>(5,7));
  for (int j = 0; j < tab.P(); j++) {
    for (int i = 0; i < tab.N(); i++)
      cout << tab(j,i) << " ";
    cout << endl;
  }

  if (tab.P()!=5 || tab.N()!=4
      || tab(0,0)!=6 || tab(0,1)!=7 || tab(0,2)!=6 || tab(0,3)!=6
      || tab(1,0)!=1 || tab(1,1)!=7 || tab(1,2)!=0 || tab(1,3)!=9
      || tab(2,0)!=2 || tab(2,1)!=7 || tab(2,2)!=3 || tab(2,3)!=9
      || tab(3,0)!=3 || tab(3,1)!=7 || tab(3,2)!=0 || tab(3,3)!=9
      || tab(4,0)!=0 || tab(4,1)!=7 || tab(4,2)!=0 || tab(4,3)!=9)
  {
    fail++;
    cout << "===> FAIL <===" << endl;
  }
  return fail;
}


int HcubeIteratorTest()
{
  cout << "****** HcubeIterator test *******" << endl;
  int n = 2;
  int k = 3;
  HcubeIterator myIt(n,k);

  vector< vector<int> > Solution(9, vector<int>(k,0));
  Solution[0][0] = 0; Solution[0][1] = 0;
  Solution[1][0] = 0; Solution[1][1] = 1;
  Solution[2][0] = 0; Solution[2][1] = 2;
  Solution[3][0] = 2; Solution[3][1] = 2;
  Solution[4][0] = 2; Solution[4][1] = 1;
  Solution[5][0] = 2; Solution[5][1] = 0;
  Solution[6][0] = 1; Solution[6][1] = 0;
  Solution[7][0] = 1; Solution[7][1] = 1;
  Solution[8][0] = 1; Solution[8][1] = 2;

  while (!myIt.IsEnded())
  {
    myIt.Print();
    unsigned int i;
    for (i = 0; i < Solution.size(); i++)
    {
      if (Solution[i][0]==myIt(0) && Solution[i][1]==myIt(1))
      {
        Solution.erase(Solution.begin()+i);
        break;
      }
    }
    ++myIt;
  }

  if (Solution.size()!=0)
  {
    cout << "===> FAIL <===" << endl;
    return 1;
  }
  else
    return 0;
}


int KnapSackTest1()
{
  cout << "******** Knapsack test 1 ********" << endl;
  int fail = 0;

  int myVal[] = {100, 60, 120, 50};
  int myWt[]= {20, 20, 30, 10};
  int n = sizeof(myVal)/sizeof(int);
  vector<int> val(myVal, myVal + n);
  vector<int> wt(myWt, myWt + n);
  int  W = 50;
  vector<int> Solution;
  int opt = knapSack<int>(W, wt, val, n, Solution);
  cout << "Optimal value of the knapsack: " << opt << endl;
  cout << "Affectation of the knapsack: ";
  for (unsigned int i = 0; i < Solution.size(); i++)
    cout << Solution[i] << " ";
  cout << endl;

  if (opt!=220
      || Solution.size()!=(unsigned int)n
      || Solution[0]!=1
      || Solution[1]!=0
      || Solution[2]!=1
      || Solution[3]!=0)
  {
    fail++;
    cout << "===> FAIL <===" << endl;
  }
  return fail;
}


int KnapSackTest2()
{
  cout << "******** Knapsack test 2 ********" << endl;
  int fail = 0;

  int myVal[] = {100, 60, 120, 70};
  int myWt[]= {20, 20, 30, 10};
  int n = sizeof(myVal)/sizeof(int);
  vector<int> val(myVal, myVal + n);
  vector<int> wt(myWt, myWt + n);
  int  W = 50;
  int opt = knapSack<int>(W, wt, val, n);
  cout << "Optimal value of the knapsack: " << opt << endl;

  if (opt!=230)
  {
    fail++;
    cout << "===> FAIL <===" << endl;
  }
  return fail;
}


int KnapSackTest3()
{
  cout << "******** Knapsack test 3 ********" << endl;
  int fail = 0;

  double myVal[] = {-12.7, 31.5, 40.8, 15.7};
  int myWt[]= {20, 10, 30, 20};
  int n = sizeof(myVal)/sizeof(double);
  vector<double> val(myVal, myVal + n);
  vector<int> wt(myWt, myWt + n);
  int  W = 50;
  vector<int> Solution;
  double opt = knapSack<double>(W, wt, val, n, Solution);
  cout << "Optimal value of the knapsack: " << opt << endl;
  cout << "Affectation of the knapsack: ";
  for (unsigned int i = 0; i < Solution.size(); i++)
    cout << Solution[i] << " ";
  cout << endl;

  if (fabs(opt-72.3) > 1E-9
      || Solution.size()!=(unsigned int)n
      || Solution[0]!=0
      || Solution[1]!=1
      || Solution[2]!=1
      || Solution[3]!=0)
  {
    fail++;
    cout << "===> FAIL <===" << endl;
  }
  return fail;
}


int NchooseKiteratorTest()
{
  cout << "***** NchooseKiterator test *****" << endl;

  int n = 5;
  int k = 2;
  NchooseKiterator myIt(n,k);

  vector< vector<int> > Solution(10, vector<int>(k,0));
  Solution[0][0] = 0; Solution[0][1] = 1;
  Solution[1][0] = 0; Solution[1][1] = 2;
  Solution[2][0] = 0; Solution[2][1] = 3;
  Solution[3][0] = 0; Solution[3][1] = 4;
  Solution[4][0] = 2; Solution[4][1] = 3;
  Solution[5][0] = 2; Solution[5][1] = 4;
  Solution[6][0] = 3; Solution[6][1] = 4;
  Solution[7][0] = 1; Solution[7][1] = 2;
  Solution[8][0] = 1; Solution[8][1] = 3;
  Solution[9][0] = 1; Solution[9][1] = 4;

  while (!myIt.IsEnded())
  {
    myIt.Print();
    unsigned int i;
    for (i = 0; i < Solution.size(); i++)
    {
      if (Solution[i][0]==myIt(0) && Solution[i][1]==myIt(1))
      {
        Solution.erase(Solution.begin()+i);
        break;
      }
    }
    ++myIt;
  }

  if (Solution.size()!=0)
  {
    cout << "===> FAIL <===" << endl;
    return 1;
  }
  else
    return 0;
}


int QuickSortTest()
{
  cout << "******* QuickSort test 1 ********" << endl;

  unsigned int n = 10;
  vector<int> tab(n, 0);
  for (unsigned int i = 0; i < tab.size(); i++)
    tab[i] = i;
  random_shuffle(tab.begin(), tab.end());

  cout << "Shuffle vector: ";
  for (unsigned int i = 0; i < tab.size(); i++)
    cout << tab[i] << " ";
  cout << endl;

  quickSort<int>(tab.begin(), tab.end());

  cout << "Sorted  vector: ";
  for (unsigned int i = 0; i < tab.size(); i++)
    cout << tab[i] << " ";
  cout << endl;

  if (tab.size()!=n)
  {
    cout << "===> FAIL <===" << endl;
    return 1;
  }
  for (unsigned int i = 0; i < n; i++)
    if (tab[i]!=(int)i)
    {
      cout << "===> FAIL <===" << endl;
      return 1;
    }
  return 0;
}


struct Point2d
{
  int _i;
  int _j;
  Point2d(int i=0, int j=0): _i(i), _j(j) {};
  bool operator<(Point2d & P)
    {
      if (_i < P._i)
        return true;
      else if (P._i < _i)
        return false;
      else
        return (_j < P._j ? true : false);
    };
  void Print() { cout << "(" << _i << "," << _j << ")" << endl; };
};


int QuickSortTest2()
{
  cout << "******* QuickSort test 2 ********" << endl;
  int fail = 0;

  unsigned int n = 6;
  vector<Point2d> tab(n, 0);
  for (unsigned int i = 0; i < tab.size(); i++)
  {
    tab[i]._i = i/3, tab[i]._j = i%3;
  }
  random_shuffle(tab.begin(), tab.end());

  cout << "Shuffle vector:" << endl;
  for (unsigned int i = 0; i < tab.size(); i++)
    tab[i].Print();

  quickSort<Point2d>(tab.begin(), tab.end());

  cout << "Sorted vector:" << endl;
  for (unsigned int i = 0; i < tab.size(); i++)
    tab[i].Print();

  if (tab.size()!=n)
  {
    fail= 1;
  }
  for (int i = 0; i < (int)n; i++)
    if (tab[i]._i != i/3 || tab[i]._j != i%3)
    {
      fail = 1;
    }

  if (fail>0)
    cout << "===> FAIL <===" << endl;
  return fail;
}


int RandomIteratorTest()
{
  cout << "****** RandomIterator test ******" << endl;
  int total = 0;

  int N = 5;
  RandomIterator myIt(N);
  while (!myIt.IsEnded())
  {
    cout << myIt() << " ";
    total += myIt();
    ++myIt;
  }
  cout << endl;

  if (total!=N*(N-1)/2)
  {
    cout << "===> FAIL <===" << endl;
    return 1;
  }
  else
    return 0;
}


int TimeToolsTest()
{
  cout << "******** TimeTools test *********" << endl;
  int fail = 0;

  try
  {
    cout << "CPU time:  " << get_cpu_time() << " s." << endl;
    cout << "Wall time: " << get_wall_time() << "s." << endl;
  }
  catch (...)
  {
    cout << "===> FAIL <===" << endl;
    fail++;
  }

  return fail;    
}


int main()
{
  /* initialize random seed: */
  srand (time(NULL));

  int NbOfFailure = 0;
  NbOfFailure += Array2dTest();
  NbOfFailure += HcubeIteratorTest();
  NbOfFailure += KnapSackTest1();
  NbOfFailure += KnapSackTest2();
  NbOfFailure += KnapSackTest3();
  NbOfFailure += NchooseKiteratorTest();
  NbOfFailure += QuickSortTest();
  NbOfFailure += QuickSortTest2();
  NbOfFailure += RandomIteratorTest();
  NbOfFailure += TimeToolsTest();

  cout << "*********************************" << endl;
  switch (NbOfFailure)
  {
  case 0:
    cout << "No failure. Well done!" << endl;
    break;
  case 1:
    cout << NbOfFailure << " test failed." << endl;
    break;
  default:
    cout << NbOfFailure << " tests failed." << endl;
    break;
  }
  return 0;
}  
