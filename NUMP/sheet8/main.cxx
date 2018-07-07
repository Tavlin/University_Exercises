#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

double dx = 0.1;
vector<double> X = {1.,2.,3.,4.,5.,6.,7.,8.,9.,10.,};
vector<double> V = {+6.33713107215e-02,+1.44577642493e-01, +2.51824506692e-01,
                    +3.31545011750e-01, +3.98582892282e-01, +4.59482949153e-01,
                    +5.15538066799e-01, +5.68026108073e-01, +6.17446547869e-01,
                    +6.65424320744e-01};

double lagrange_pol(double x,int j, vector<double> a){
  double val = 1;
  int size = a.size();
  for (int i = 0; i < size; i++) {
    if(i != j){
      val *= (x - a[i])/(a[j]-a[i]);
    }
  }
  return val;
}

double g_x(double x, vector<double> v){
  double val = 0;
  int size = v.size();
  for (int i = 2; i < size; i++) {
    val += v[i]*lagrange_pol(x,i,X);
  }
  return val;
}

int main(void){
  ofstream output;
  output.open("lagrange_pol.txt");
  for (int i = 30; i < 100; i++) {
    output << i*dx << "\t" << g_x((double)i*dx,V) << endl;
  }
  output.close();
  return 0;
}
