#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

float floating_point_calc(int s, int* m, int* e){
  
  int b = 7;
  int sum_m = 0;
  int sum_e = 0;
  
  for(int n = 0; n < 3; n++){
  
    sum_m += m[n]*pow(2.,-n);
    
  }
  
  for(int i = 0; i <= 3; i++){
    
    sum_e += 3*e[3-i]*pow(2.,i)-b;
    
  }
  return (pow(-1.,s)*(1+sum_m)*pow(2.,sum_e));
  
}

int main (void){
  
  //which number is represented by the bit string 10111000?
  // -16384
  int m[3] = {0,0,0};
  int e[4] = {1,1,1,0};
  int s = 1;
  
  cout << floating_point_calc(s, m, e) << " is represented by the bit string 10111000" << endl;
  
  return 0;
}
