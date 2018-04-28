#include<iostream>

using namespace std;

long int fib(int n){
  if(n == 0){
    return 0;
  }

  else if(n == 1){
    return 1;
  }
  else{
    return fib(n-1)+fib(n-2);
  }
}

int main(void){
  for (int i = 0; i < 16; i++) {
    cout << "fib(" << i << ") = " << fib(i) << endl;
  }
}
