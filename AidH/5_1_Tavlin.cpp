#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <fstream>

using namespace std;

const int n_iter = 1.e3; // number of Collisions
const double sigma = 6.; // 60 mb = 6 fm²
const double d = sqrt(sigma/M_PI); // max distance in xy plane between to collinding nuclei
const double r = 7.; //radii of the nuclei

class Nukleon{
  public:
    double radius, x_position, y_position;
    Nukleon(double r){
      radius = r;
      double x_position  = ((double)rand()/RAND_MAX)*2*r;
      double y_position  = ((double)rand()/RAND_MAX)*2*r;
    }

};

// Nukleon::__init__(void){
//   Nukleon.x_position = ((double)rand()/RAND_MAX)*2*r;
//   Nukleon.y_position = ((double)rand()/RAND_MAX)*2*r;
// }

class Kern{
  public:
    double radius, x_lenght, y_lenght;
    int A,Z;
    Nukleon* nuklei;
    Kern(int A, double r){ //Uniform initialization?
      radius = r;
      x_lenght = 2*radius;
      y_lenght = 2*radius;

      for (int i = 0; i < A; i++) {
        nuklei[i] = Nukleon nukleon (radius);
      }
    }

};



int main(void){

  srand(time(NULL)); //seed rand with time!

  int N_coll[n_iter]; //initialize N_coll
  int A = 208;

  for(int b = 0; b <= 8; b += 4){
    for (int i = 0; i < n_iter; i++) {
      Kern Pb_1(A, r);
      Kern Pb_2(A, r);
      N_coll[i] = 0;

      // change y coords so the nuclei have a difference of b between their centers
      for (int j = 0; j < A; j++) {
        Pb_1.nuklei[j].y_position += b/2.;
        Pb_2.nuklei[j].y_position -= b/2.;
      }
      for (int k = 0; k < A; k++) {
        for (int l = 0; l < A; l++) {
          // calculate the distance between one Nuclei of Pb_1 and one Nuclei of Pb_2
          double x_abs, y_abs;
          x_abs = Pb_1.nuklei[k].x_position - Pb_2.nuklei[l].x_position;
          y_abs = Pb_1.nuklei[k].y_position - Pb_2.nuklei[l].y_position;
          if(sqrt(x_abs*x_abs + y_abs*y_abs) <= d){
            N_coll[i] += 1; // one collision
          }
        }
      }
    }
    int N_coll_mean = 0;
    for (int m = 0; m < n_iter; m++) {
      N_coll_mean += N_coll[m];
    }
    N_coll_mean /= n_iter;

    cout << "for b = " << b << " :" << endl;
    cout << "<N_coll> = " << N_coll_mean << endl;
  }
  return 0;
}
