#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <random>

using namespace std;

const int n_iter = 1.e3; // number of Collisions
const double sigma = 6.; // 60 mb = 6 fm²
const double d = sqrt(sigma/M_PI); // max distance in xy plane between to collinding nuclei
const double thick = 0.64; // fm thickness of the wood saxon
const double r = 6.62; //radii of the nuclei in fm
const int N = 1000; // how many discrete steps are taken in the wood saxon
double p[N];


double wood_saxon(double x){
  return 1./ (1. + exp((x-r)/(thick)));
}

class Nukleon{
  public:
    double radius, x_position, y_position;
    Nukleon(double r){
      radius = r;
      x_position  = ((double)rand()/RAND_MAX)*2*r;
      y_position  = ((double)rand()/RAND_MAX)*2*r;
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
    std::vector<Nukleon*> nuklei;
    Kern(int A, double r){ //Uniform initialization?
      radius = r;
      x_lenght = 2*radius;
      y_lenght = 2*radius;

      for (int i = 0; i < A; i++) {
        nuklei.push_back(new Nukleon(radius));
      }
    }

};



int main(void){
  std::default_random_engine generator;
  for (int i = 0; i < N; i++) {
    p[i] = wood_saxon(i*r/(double)N);
  }
  std::discrete_distribution<double> distribution p;

  srand(time(NULL)); //seed rand with time!

  int N_coll[n_iter]; //initialize N_coll
  int A = 208;

  for(int b = 0; b <= 8; b += 4){

    for (int i = 0; i < n_iter; i++) {
      Kern *Pb_1 = new Kern(A, r);
      Kern *Pb_2 = new Kern(A, r);
      N_coll[i] = 0;

      // change y coords so the nuclei have a difference of b between their centers
      for (int j = 0; j < A; j++) {
        Pb_1->nuklei[j]->x_position = b;
        Pb_1->nuklei[j]->y_position = b;
        Pb_2->nuklei[j]->x_position = b;
        Pb_2->nuklei[j]->y_position = b;

      }
      for (int k = 0; k < A; k++) {
        for (int l = 0; l < A; l++) {
          // calculate the distance between one Nuclei of Pb_1 and one Nuclei of Pb_2
          double x_abs, y_abs;
          x_abs = Pb_1->nuklei[k]->x_position - Pb_2->nuklei[l]->x_position;
          y_abs = Pb_1->nuklei[k]->y_position - Pb_2->nuklei[l]->y_position;
          if(sqrt(x_abs*x_abs + y_abs*y_abs) <= d){
            N_coll[i] += 1; // one collision
          }
        }
      }
      delete Pb_1;
      delete Pb_2;
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
