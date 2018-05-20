//Pendulum with RK 4th Order
// \vec{F} = -mge_{z}
// \phi(t=0) = \phi_{0}

//EOM:
//d^{2}\phi/dt^2 = -sin(\phi)

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

const int N = 2; //Number of needed Dimensions
const int num_steps = 1.e4; //Number of steps
const double tau = 1.e-3; // Stepsize

double y[N][num_steps+1]; // array of 2D points forming the Trajectory
void sheet_2_2(void){
  //Initial Conditions
  y[0][0] = M_PI/8; //starting angle
  y[1][0] = 0; //starting velocity

  int i,j;

  //RK 4th Order
  for (i = 1; i <= num_steps; i++) {
    double k1[N], k2[N], k3[N], k4[N];
    k1[0] = y[1][i-1]*tau;
    k1[1] = -sin(y[0][i-1])*tau;

    k2[0] = (y[1][i-1]+0.5*k1[1])*tau;
    k2[1] = (-sin(y[0][i-1]+0.5*k1[0]))*tau;

    k3[0] = (y[1][i-1]+0.5*k2[1])*tau;
    k3[1] = (-sin(y[0][i-1]+0.5*k2[0]))*tau;

    k4[0] = (y[1][i-1]+k3[1])*tau;
    k4[1] = (-sin(y[0][i-1]+k3[0]))*tau;
    for (j = 0; j < 2; j++) {
      y[j][i] = y[j][i-1] + 1./6.*(k1[j]+2*k2[j]+2*k3[j]+k4[j]);
    }
  }
  // output into a file
  ofstream myfile;
  myfile.open("pendulum.txt");

  for(i = 0; i <= num_steps; i++){
    double t = i * tau;
    // printf("%9.6lf %9.6lf\n", t, y[0][i]);
    myfile << t << "\t" << y[0][i] << endl;
  }
  myfile.close();

  //Drawing the obtained solution:
  


}
