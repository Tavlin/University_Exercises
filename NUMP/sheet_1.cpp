#include <iostream>
#include <fstream>
#include <math.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

float floating_point_calc(int s, int* m, int* e){
  
  int b = 7;
  float sum_m = 0;
  int sum_e = 0;
  
  for(int n = 0; n < 3; n++){
  
    sum_m += m[n]*pow(2.,-(n+1));
    //cout << sum_m << endl;
  }
  
  for(int i = 0; i <= 3; i++){
    
    sum_e += e[3-i]*pow(2.,i);
    
  }
  return (pow(-1.,s)*(1+sum_m)*pow(2.,sum_e-b));
  
}

float smallest_float_number(void){

  float x,y;
  for(int i = 0; y > 0; i--){
  
    y = 1.*pow(2.,i);
    x = 1.*pow(2.,i+1);
  }
  return x;
}

double smallest_double_number(void){

  double x,y;
  for(int i = 0; y > 0; i--){
  
    y = 1.*pow(2.,i);
    x = 1.*pow(2.,i+1);
  }
  return x;
}


float fib_float(int n){

  if(n == 0){
    return 0;
  }
  
  else if(n == 1){
    return 1;
  }
  
  else if(n > 1){
    return fib_float(n-1) + fib_float(n-2);
  }
  
  else{
    cout << "Error, n must be positive" << endl;
    exit(1);
  }
  
}

double fib_double(int n){

  if(n == 0){
    return 0;
  }
  
  else if(n == 1){
    return 1;
  }
  
  else if(n > 1){
    return fib_double(n-1) + fib_double(n-2);
  }
  
  else{
    cout << "Error, n must be positive" << endl;
    exit(1);
  }
  
}

float fib_float_delta(int n){

  float goldenratio_f = (1+sqrt(5))/2;
  
  return fib_float(n)/fib_float(n-1)-goldenratio_f;
}

float fib_double_delta(int n){

  double goldenratio_d = (1+sqrt(5))/2;
  
  return fib_double(n)/fib_double(n-1)-goldenratio_d;
}

float phi_float_it_p(int n){
  if(n == 0){
    return 1;
  }

  else if(n == 1){
    return (-1.+sqrt(5.))/2.;
  }
  
  else if( n > 1){
    return phi_float_it_p(n-2) - phi_float_it_p(n-1);
  }
  
  else{
    cout << "error" << endl;
    exit(2);
  }
}

float phi_float_it_m(int n){
  if(n == 0){
    return 1.;
  }

  else if(n == 1){
    return (-1. - sqrt(5.))/2.;
  }
  
  else if( n > 1){
    return phi_float_it_m(n-2) - phi_float_it_m(n-1);
  }
  
  else{
    cout << "error" << endl;
    exit(2);
  }
}

double phi_double_it_p(int n){
  if(n == 0){
    return 1.;
  }

  else if(n == 1){
    return (-1.+sqrt(5.))/2.;
  }
  
  else if( n > 1){
    return phi_double_it_p(n-2) - phi_double_it_p(n-1);
  }
  
  else{
    cout << "error" << endl;
    exit(2);
  }
}

double phi_double_it_m(int n){
  if(n == 0){
    return 1;
  }

  else if(n == 1){
    return (-1. - sqrt(5.))/2.;
  }
  
  else if( n > 1){
    return phi_double_it_m(n-2) - phi_double_it_m(n-1);
  }
  
  else{
    cout << "error" << endl;
    exit(2);
  }
}

float phi_float_direct_p(int n){
  return pow((-1. + sqrt(5.))/2.,n);
}

float phi_float_direct_m(int n){
  return pow((-1. - sqrt(5.))/2.,n);
}


double phi_double_direct_p(int n){
  return pow((-1. + sqrt(5.))/2.,n);
}

double phi_double_direct_m(int n){
  return pow((-1. - sqrt(5.))/2.,n);
}

int main (void){
  
  //which number is represented by the bit string 10111000?
  // -16384
  int m[3] = {1,1,1};
  int e[4] = {1,1,1,1};
  int s = 0;
  float f_min = smallest_float_number();
  double d_min = smallest_double_number();
  
  cout << floating_point_calc(s, m, e) << " is represented by the bit string 10111000" << endl;
  
  cout << (35./32. - 33./32.) << " and " << (37./32.-35./32.) << endl << endl;
  

  cout << "The smallest float number should be: " << endl;
  cout << f_min << endl;
  
  cout << "The smallest double number should be: " << endl;
  cout << d_min << endl;
  
  // calculating the deltas of fibnumers and print them in .txt for root.
  /*
  int a = 2;
  int b = 2;

  
  ofstream myfile;

  myfile.open("fib_float.txt");
  
  do{
      myfile << a << "\t" << fib_float_delta(a) << endl;
      a++;
    
  }while(a <= 41);
  
  
  myfile.close();
  
  ofstream myfile2;
  myfile2.open("fib_double.txt");
  
  do{
      myfile2 << b << "\t"  << fib_double_delta(b) << endl;
      b++;
    
  }while(b <= 41);
  
  myfile2.close();
  */
  
  
  for(int i = 0; i <= 20; i++){
    
    cout << "phi_float_it_p(" << i << ") = " << phi_float_it_p(i) << endl;
    cout << "phi_float_it_m(" << i << ") = " << phi_float_it_m(i) << endl;
    cout << "phi_double_it_p(" << i << ") = " << phi_double_it_p(i) << endl;
    cout << "phi_double_it_m(" << i << ") = " << phi_double_it_m(i) << endl;
    cout << "phi_float_direct_p(" << i << ") = " << phi_float_direct_p(i) << endl;
    cout << "phi_float_direct_m(" << i << ") = " << phi_float_direct_m(i) << endl;
    cout << "phi_double_direct_p(" << i << ") = " << phi_double_direct_p(i) << endl;
    cout << "phi_double_direct_m(" << i << ") = " << phi_double_direct_m(i) << endl;
    
  }
  
  
  return 0;
}
