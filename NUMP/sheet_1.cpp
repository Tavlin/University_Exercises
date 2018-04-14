#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

float floating_point_calc(int s, int* m, int* e){
  
  int b = 7;
  float sum_m = 0;
  int sum_e = 0;
  
  for(int n = 0; n < 3; n++){
  
    sum_m += m[n]*pow(2.,-n);
    //cout << sum_m << endl;
  }
  
  for(int i = 0; i <= 3; i++){
    
    sum_e += 3*e[3-i]*pow(2.,i)-b;
    
  }
  return (pow(-1.,s)*(1+sum_m)*pow(2.,sum_e));
  
}

float smallest_float_number(void){

  float x,y;
  for(int i = 0; y > 0; i--){
  
    y = 1.*pow(10.,i);
    x = 1.*pow(10.,i+1);
  }
  return x;
}

double smallest_double_number(void){

  double x,y;
  for(int i = 0; y > 0; i--){
  
    y = 1.*pow(10.,i);
    x = 1.*pow(10.,i+1);
  }
  return x;
}


int main (void){
  
  //which number is represented by the bit string 10111000?
  // -16384
  int m[3] = {0,0,0};
  int e[4] = {1,1,1,0};
  int s = 0;
  float f_min = smallest_float_number();
  double d_min = smallest_double_number();
  
  cout << floating_point_calc(s, m, e) << " is represented by the bit string 10111000" << endl;
  
  cout << (35./32. - 33./32.) << " and " << (37./32.-35./32.) << endl << endl;
  
  cout << "The smallest float number should be: " << endl;
  cout << f_min << endl;
  
  cout << "The smallest double number should be: " << endl;
  cout << d_min << endl;
  return 0;
}
