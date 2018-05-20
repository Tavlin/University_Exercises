#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <iostream>

int main(void){

  long unsigned int n = 1e9; //number of times thrown at the quader
  double x,y; //Koordinates where the throw lands
  double r = 1; //radius of the circle
  long unsigned int h = 0; // number of hits
  double pi_calc = 0;


  srand (time(NULL)); //seeding rand with the time
  for (long unsigned int i = 0; i < n; i++) {

    x = (double) rand()/(double) RAND_MAX; //random x-coordinate
    y = (double) rand()/(double) RAND_MAX; //random y-coordiante
    if(sqrt(x*x+y*y) <= r){ //check if you hit the quadracircle
      h++; //add one hit
    }
  }

  // the area relation of 1x1 square to a 4th segment of a circle is pi/4
  pi_calc = (double)h/(double)n;
  std::cout << "calculated pi/4 = " << pi_calc << std::endl;

  pi_calc *= 4;
  std::cout << "calculated pi = " << pi_calc << std::endl;

  return 0;
}
