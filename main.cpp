#include "KnapSack.h"
#include <iostream>
#include <vector>

using namespace std;


int KnapSackTest1()
{
  cout << "***** Knapsack test 1 *****" << endl;
  int myVal[] = {100, 60, 120, 50};
  int myWt[]= {20, 20, 30, 10};
  int n = sizeof(myVal)/sizeof(int);
  vector<int> val(myVal, myVal + n);
  vector<int> wt(myWt, myWt + n);
  int  W = 50;
  vector<int> Solution;
  int opt = knapSack(W, wt, val, n, Solution);
  cout << "Optimal value of the knapsack: " << opt << endl;
  cout << "Affectation of the knapsack: ";
  for (unsigned int i = 0; i < Solution.size(); i++)
    cout << Solution[i] << " ";
  cout << endl;

  int fail = 0;
  if (opt!=220
      || Solution.size()!=(unsigned int)n
      || Solution[0]!=1
      || Solution[1]!=0
      || Solution[2]!=1
      || Solution[3]!=0)
  {
    fail++;
  }
  return fail;
}


int KnapSackTest2()
{
  cout << "***** Knapsack test 2 *****" << endl;
  int myVal[] = {100, 60, 120, 70};
  int myWt[]= {20, 20, 30, 10};
  int n = sizeof(myVal)/sizeof(int);
  vector<int> val(myVal, myVal + n);
  vector<int> wt(myWt, myWt + n);
  int  W = 50;
  int opt = knapSack(W, wt, val, n);
  cout << "Optimal value of the knapsack: " << opt << endl;

  int fail = 0;
  if (opt!=230)
  {
    fail++;
  }
  return fail;
}


int main()
{
  int NbOfFailure = 0;
  NbOfFailure += KnapSackTest1();
  NbOfFailure += KnapSackTest2();

  cout << "***************************" << endl;
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
