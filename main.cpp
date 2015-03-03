#include "KnapSack.h"
#include "NchooseKiterator.h"

#include <iostream>
#include <vector>

using namespace std;


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
  int opt = knapSack(W, wt, val, n, Solution);
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
  int opt = knapSack(W, wt, val, n);
  cout << "Optimal value of the knapsack: " << opt << endl;

  if (opt!=230)
  {
    fail++;
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

  return (Solution.size()==0 ? 0 : 1);
}


int main()
{
  int NbOfFailure = 0;
  NbOfFailure += KnapSackTest1();
  NbOfFailure += KnapSackTest2();
  NbOfFailure += NchooseKiteratorTest();

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
