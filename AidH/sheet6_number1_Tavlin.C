#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "TF1.h"
#include "TMath.h"

using namespace std;

const Int_t n_iter = 1.e3; // number of Collisions
const Double_t sigma = 6.; // 60 mb = 6 fm²
const Double_t d = sqrt(sigma/TMath::Pi()); // max distance in xy plane between to collinding nuclei
const Double_t thick = 0.64; // fm thickness of the wood saxon
const Double_t r = 6.62; //radii of the nuclei in fm


Double_t wood_saxon(Double_t x){
  return 1./ (1. + exp((x-r)/(thick)));
}

// TF1* f = new TF1("f", "wood_saxon(x)", 0.,r);

class Nukleon{
  public:
    Double_t radius, x_position, y_position;
    Nukleon(Double_t r){
      radius = r;
      x_position  = 0; //f->GetRandom(0.,r);
      // make it so that x^2+y^2=r^2 for round nuclei
      y_position  = 0;//f->GetRandom(0.,sqrt(r*r-x_position*x_position));
    }

};

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



void sheet6_number1_Tavlin(void){
  TF1* f = new TF1("f", "wood_saxon(x)", -r,r);

  int N_coll[n_iter]; //initialize N_coll
  int A = 208;

  for(int b = 0; b <= 8; b += 4){

    for (int i = 0; i < n_iter; i++) {
      Kern *Pb_1 = new Kern(A, r);
      Kern *Pb_2 = new Kern(A, r);
      N_coll[i] = 0;

      // change y coords so the nuclei have a difference of b between their centers
      for (int j = 0; j < A; j++) {
        Pb_1->nuklei[j]->x_position = f->GetRandom(-r, r) + b;
        Double_t rest_y_1 = Pb_1->nuklei[j]->x_position;
        Pb_1->nuklei[j]->y_position = f->GetRandom(-sqrt(r*r-rest_y_1 *rest_y_1),sqrt(r*r-rest_y_1 *rest_y_1));
        Pb_2->nuklei[j]->x_position = f->GetRandom(-r, r);
        Double_t rest_y_2 = Pb_2->nuklei[j]->x_position;
        Pb_1->nuklei[j]->y_position = f->GetRandom(-sqrt(r*r-rest_y_2 *rest_y_2), sqrt(r*r-rest_y_2 *rest_y_2));

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
}