#include "array2d.h"
#include "hcube_iterator.h"
#include "knapsack.h"
#include "n_choose_k_iterator.h"
#include "quick_sort.h"
#include "random_iterator.h"
#include "time_tools.h"
#include "tolerance.h"

#include <algorithm>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <vector>

using namespace std;


int array2d_test()
{
  cout << "************* Array2d test *************" << endl;
  int fail = 0;

  int p = 3; int n = 4;
  Array2d<int> tab(p,n);
  for (int j = 0; j < tab.nb_rows(); j++)
    tab(j,0) = j+1;
  for (int i = 0; i < tab.nb_columns(); i++)
    tab(1,i) = i+2;

  tab.resize(4,2);
  tab.push_back_column(vector<int>(4,9));
  tab.insert_row(0, vector<int>(3,6));
  tab.insert_column(1, vector<int>(5,7));
  tab.resize(5,5);
  tab.resize(6,5,1);
  tab.print();

  if (tab.nb_rows()!=6 || tab.nb_columns()!=5
      || tab(0,0)!=6 || tab(0,1)!=7 || tab(0,2)!=6 || tab(0,3)!=6 || tab(0,4)!=0
      || tab(1,0)!=1 || tab(1,1)!=7 || tab(1,2)!=0 || tab(1,3)!=9 || tab(1,4)!=0
      || tab(2,0)!=2 || tab(2,1)!=7 || tab(2,2)!=3 || tab(2,3)!=9 || tab(2,4)!=0
      || tab(3,0)!=3 || tab(3,1)!=7 || tab(3,2)!=0 || tab(3,3)!=9 || tab(3,4)!=0
      || tab(4,0)!=0 || tab(4,1)!=7 || tab(4,2)!=0 || tab(4,3)!=9 || tab(4,4)!=0
      || tab(5,0)!=1 || tab(5,1)!=1 || tab(5,2)!=1 || tab(5,3)!=1 || tab(5,4)!=1 )
  {
    fail++;
  }
  
  Array2d<short> tab_1(2,3);
  tab_1(0,0) = 0; tab_1(0,1) = 2; tab_1(0,2) = 0;
  tab_1(1,0) = 3; tab_1(1,1) = 0; tab_1(1,2) = 1;
  Array2d<short> tab_2(2,3);
  tab_2(0,0) = 1; tab_2(0,1) = 1; tab_2(0,2) = 3;
  tab_2(1,0) = 5; tab_2(1,1) = 0; tab_2(1,2) = -4;
  short dot_prod = tab_1.dot_product(tab_2);

  if (dot_prod != 13)
    fail++;

  Array2d<short> tab_3(tab_1);
  if (tab_1.nb_rows() != tab_3.nb_rows() || tab_1.nb_columns() != tab_3.nb_columns()) {
    fail++;
  }
  else {
    for (int j = 0; j < tab_3.nb_rows(); j++) {
      for (int i = 0; i < tab_3.nb_columns(); i++) {
        if (tab_1(j,i) != tab_3(j,i))
          fail++;
      }
    }
  }

  Array2d<short> tab_4;
  tab_4.push_back_column(vector<short>(3,1));
  if (tab_4.nb_rows()!=3 || tab_4.nb_columns()!=1
    || tab_4(0,0)!=1 || tab_4(1,0)!=1 || tab_4(2,0)!=1 )
  {
    fail++;
  }

  Array2d<short> tab_5;
  tab_5.push_back_row(vector<short>(3,1));
  if (tab_5.nb_rows()!=1 || tab_5.nb_columns()!=3
    || tab_5(0,0)!=1 || tab_5(0,1)!=1 || tab_5(0,2)!=1 )
  {
    fail++;
  }
  
  if (fail > 0) {
    cout << "===> FAIL <===" << endl;
  }
  
  return fail;
}


int hcube_iterator_test()
{
  cout << "********* Hcube_iterator test **********" << endl;
  unsigned int n = 2;
  unsigned int k = 3;
  Hcube_iterator myIt(n,k);

  vector< vector<unsigned int> > Solution(9, vector<unsigned int>(k,0));
  Solution[0][0] = 0; Solution[0][1] = 0;
  Solution[1][0] = 0; Solution[1][1] = 1;
  Solution[2][0] = 0; Solution[2][1] = 2;
  Solution[3][0] = 2; Solution[3][1] = 2;
  Solution[4][0] = 2; Solution[4][1] = 1;
  Solution[5][0] = 2; Solution[5][1] = 0;
  Solution[6][0] = 1; Solution[6][1] = 0;
  Solution[7][0] = 1; Solution[7][1] = 1;
  Solution[8][0] = 1; Solution[8][1] = 2;

  while (!myIt.is_ended())
  {
    myIt.print();
    for (unsigned int i = 0; i < Solution.size(); i++)
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


int KnapSack_test1()
{
  cout << "*********** Knapsack test 1 ************" << endl;
  int fail = 0;

  // Input of the knapsack
  int myVal[] = {100, 60, 120, 50};
  unsigned int myWt[]= {20, 20, 30, 10};
  int n = sizeof(myVal)/sizeof(int);
  vector<int> val(myVal, myVal + n);
  vector<unsigned int> wt(myWt, myWt + n);
  unsigned int  W = 50;


  Knapsack<int> knapsack(W, wt, val);     // Create the knapsack problem
  int opt = knapsack();                   // Solve the knapsack problem
  vector<bool> Solution;                  // 
  knapsack.get_chosen_objects(Solution);  // Get the list of chosen objects


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


int KnapSack_test2()
{
  cout << "*********** Knapsack test 2 ************" << endl;
  int fail = 0;

  // Input of the knapsack
  int myVal[] = {100, 60, 120, 70};
  unsigned int myWt[]= {20, 20, 30, 10};
  int n = sizeof(myVal)/sizeof(int);
  vector<int> val(myVal, myVal + n);
  vector<unsigned int> wt(myWt, myWt + n);
  unsigned int  W = 50;


  Knapsack<int> knapsack;          // Create the knapsack problem
  int opt = knapsack(W, wt, val);  // Solve the knapsack problem

  cout << "Optimal value of the knapsack: " << opt << endl;

  if (opt!=230)
  {
    fail++;
    cout << "===> FAIL <===" << endl;
  }
  return fail;
}


int KnapSack_test3()
{
  cout << "*********** Knapsack test 3 ************" << endl;
  int fail = 0;

  // Input of the knapsack at his creation
  double myVal1[] = {5, 12.6, 8, 9.7, 7};
  unsigned int myWt1[]= {10, 80, 53, 10, 24};
  int n1 = sizeof(myVal1)/sizeof(double);
  vector<double> val1(myVal1, myVal1 + n1);
  vector<unsigned int> wt1(myWt1, myWt1 + n1);
  unsigned int  W1 = 64;

  // Create the knapsack problem
  Knapsack<double> knapsack(W1, wt1, val1);

  // Input of the knapsack for resolution
  double myVal2[] = {-12.7, 31.5, 40.8, 15.7};
  unsigned int myWt2[]= {20, 10, 30, 20};
  int n2 = sizeof(myVal2)/sizeof(double);
  vector<double> val2(myVal2, myVal2 + n2);
  vector<unsigned int> wt2(myWt2, myWt2 + n2);
  unsigned int  W2 = 50;


  knapsack(W2, wt2, val2);                    // Solve the knapsack problem
  double opt = knapsack.get_optimal_value();  // Get the optimal vallue of the knapsack
  vector<bool> Solution;                      // Get the list of chosen objects
  knapsack.get_chosen_objects(Solution);      // Get the list of chosen objects

  cout << "Optimal value of the knapsack: " << opt << endl;
  cout << "Affectation of the knapsack: ";
  for (unsigned int i = 0; i < Solution.size(); i++)
    cout << Solution[i] << " ";
  cout << endl;

  if (fabs(opt-72.3) > 1E-9
      || Solution.size()!=(unsigned int)n2
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


int n_choose_k_iterator_test()
{
  cout << "******* N_choose_K_iterator test *******" << endl;

  unsigned int n = 5;
  unsigned int k = 2;
  N_choose_K_iterator myIt(n,k);

  vector< vector<unsigned int> > Solution(10, vector<unsigned int>(k,0));
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

  while (!myIt.is_ended())
  {
    myIt.print();
    for (unsigned int i = 0; i < Solution.size(); i++)
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


int quick_sort_test()
{
  cout << "********** Quick_sort test 1 ***********" << endl;

  unsigned int n = 10;
  vector<int> tab(n, 0);
  for (unsigned int i = 0; i < tab.size(); i++)
    tab[i] = i;
  random_shuffle(tab.begin(), tab.end());

  cout << "Shuffle vector: ";
  for (unsigned int i = 0; i < tab.size(); i++)
    cout << tab[i] << " ";
  cout << endl;

  Quick_sort<int> quick_sort;
  quick_sort(tab.begin(), tab.end());

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


int quick_sort_test2()
{
  cout << "********** Quick_sort test 2 ***********" << endl;
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

  Quick_sort<Point2d> quick_sort;
  quick_sort(tab.begin(), tab.end());

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


int random_iterator_test()
{
  cout << "********* Random_iterator test *********" << endl;
  int total = 0;

  int N = 5;
  Random_iterator myIt(N);
  while (!myIt.is_ended())
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


int time_tools_test()
{
  cout << "*********** Time tools test ************" << endl;
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


/**
 * @brief Test the class #Tolerance
 */
int tolerance_test()
{
  cout << "************ Tolerance test ************" << endl;
  int error_code = 0;

  Tolerance myTol1(1e-3, 1e-2);
  
  std::cout << "Absolute and relative difference        " << std::flush;
  double a = 3.6;
  double b = 12.4;
  if ( !myTol1.close(a, b) && myTol1.lower_not_close(a,b) && myTol1.lower_or_close(a,b) )
    std::cout << "OK" << std::endl;
  else
  {
    error_code++;
    std::cout << "failed (return code: 1)" << std::endl;
  }

  std::cout << "Absolute difference and relative close  " << std::flush;
  a = 3.;
  b = 3.002 ;
  if ( myTol1.close(a, b) && !myTol1.lower_not_close(a,b) && myTol1.lower_or_close(a,b) )
    std::cout << "OK" << std::endl;
  else
  {
    error_code++;
    std::cout << "failed (return code: 1)" << std::endl;
  }

  Tolerance myTol2(1., 1e-2);
  std::cout << "Absolute close and relative difference  " << std::flush;
  a = 3.;
  b = 3.1 ;
  if ( myTol2.close(a, b) && !myTol2.lower_not_close(a,b) && myTol2.lower_or_close(a,b) )
    std::cout << "OK" << std::endl;
  else
  {
    error_code++;
    std::cout << "failed (return code: 1)" << std::endl;
  }

  std::cout << "Absolute and relative close             " << std::flush;
  a = 3.;
  b = 3.001;
  if ( myTol2.close(a, b) && !myTol2.lower_not_close(a,b) && myTol2.lower_or_close(a,b) )
    std::cout << "OK" << std::endl;
  else
  {
    error_code++;
    std::cout << "failed (return code: 1)" << std::endl;
  }
  
  return error_code;
}



int main()
{
  /* initialize random seed: */
  srand (time(NULL));

  int nb_failure = 0;
  nb_failure += array2d_test();
  std::cout << std::endl;

  nb_failure += hcube_iterator_test();
  std::cout << std::endl;

  nb_failure += KnapSack_test1();
  std::cout << std::endl;

  nb_failure += KnapSack_test2();
  std::cout << std::endl;

  nb_failure += KnapSack_test3();
  std::cout << std::endl;

  nb_failure += n_choose_k_iterator_test();
  std::cout << std::endl;

  nb_failure += quick_sort_test();
  std::cout << std::endl;

  nb_failure += quick_sort_test2();
  std::cout << std::endl;

  nb_failure += random_iterator_test();
  std::cout << std::endl;

  nb_failure += time_tools_test();
  std::cout << std::endl;

  nb_failure += tolerance_test();
  std::cout << std::endl;

  cout << "*********************************" << endl;
  switch (nb_failure)
  {
  case 0:
    cout << "No failure. Well done!" << endl;
    break;
  case 1:
    cout << nb_failure << " test failed." << endl;
    break;
  default:
    cout << nb_failure << " tests failed." << endl;
    break;
  }
  return nb_failure;
}  
