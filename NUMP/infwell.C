// compute energy eigenvalues and wave functions of the infinite potential well,
// -\psi’’ = E \psi ,
// with boundary conditions \psi(x=0) = \psi(x=1) = 0
// **********
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
// **********
// physics parameters and functions
// **********
// y = (\psi , \phi , E)
// f = (\phi , -E \psi , 0)
const int N = 3; // number of components of \vec{y} and \vec{f}
double y_0[N] = { 0.0 , 1.0 , 0.0 }; // Anfangsbedingungen y(t=0).
// function computing f(y(t),t) * tau
void f_times_tau(double *y_t, double t, double *f_times_tau_, double tau){
  if(N != 3){
    fprintf(stderr, "Error: N != 3!\n");
    exit(EXIT_FAILURE);
  }
  f_times_tau_[0] = y_t[1] * tau;
  f_times_tau_[1] = -y_t[2] * y_t[0] * tau;
  f_times_tau_[2] = 0.0;
}
// **********
// RK parameters
// **********
// #define __EULER__
#define __RK_2ND__
// #define __RK_3RD__
// #define __RK_4TH__
#ifdef __EULER__
const int order = 1;
#endif
#ifdef __RK_2ND__
const int order = 2;
#endif
#ifdef __RK_3RD__
const int order = 3;
#endif
#ifdef __RK_4TH__
const int order = 4;
#endif
// number of steps
const int num_steps = 1000;
// compute trajectory (= wave function) from t = t_0 to T = t_1
const double t_0 = 0.0;
const double t_1 = 1.0;
double tau = (t_1 - t_0) / (double)num_steps; // step size
double h = 0.000001; // finite difference for numerical derivative
double dE_min = 0.0000001; // Newton-Raphson accuracy
// **********
#ifdef __EULER__
...
#endif
#ifdef __RK_2ND__
// RK step (2nd order), step size tau
void RK_step(double *y_t, double t, double *y_t_plus_tau, double tau){
  int i1;
  // *****
  // k1 = f(y(t),t) * tau
  double k1[N];
  f_times_tau(y_t, t, k1, tau);
  // *****
  // k2 = f(y(t)+(1/2)*k1 , t+(1/2)*tau) * tau
  double y_[N];
  for(i1 = 0; i1 < N; i1++){
    y_[i1] = y_t[i1] + 0.5*k1[i1];
  }
  double k2[N];
  f_times_tau(y_, t + 0.5*tau, k2, tau);
  // *****
  for(i1 = 0; i1 < N; i1++){
    y_t_plus_tau[i1] = y_t[i1] + k2[i1];
  }
}
#endif

#ifdef __RK_3RD__
...
#endif

#ifdef __RK_4TH__
...
#endif

// **********
// RK computation of the trajectory (= wave function)
double t[num_steps+1]; // discretized time
double y[num_steps+1][N]; // discretized trajectories
double RK(bool output = false){
  double d1;
  int i1, i2;
  // *****
  // RK steps
  for(i1 = 0; i1 < num_steps; i1++){
    // y(t) --> y(t+\tau)
    RK_step(y[i1], t[i1], y[i1+1], tau);
    t[i1+1] = t[i1] + tau;
  }
  // *****
  if(output == true){
    // output
    for(i1 = 0; i1 <= num_steps; i1++){
      printf("%9.6lf %9.6lf %9.6lf %9.6lf\n", t[i1], y[i1][0], y[i1][1], y[i1][2]);
    }
  }
  // *****
  return y[num_steps][0];
}
// **********
int main(int argc, char **argv){
  int i1;
  // *****
  // initialize trajectories with initial conditions
  t[0] = t_0;
  for(i1 = 0; i1 < N; i1++){
    y[0][i1] = y_0[i1];
  }

  // **********
  // shooting method
  // **********
  // /*
  // intial condition (energy)
  // double E = 10.0;
  // double E = 40.0;
  double E = 90.0;
  fprintf(stderr, "E_num = %+10.6lf .\n", E);
  while(1){
    // change initial condition (energy)
    y[0][N-1] = E;
    // RK computation of the trajectory (= wave function)
    double psi_1_E = RK(false);
    // *****
    // numerical derivative (d/dh) psi(x=1)
    y[0][N-1] = E-h;
    double psi_1_E_mi_h = RK(false);
    y[0][N-1] = E+h;
    double psi_1_E_pl_h = RK(false);
    double dpsi_1_E = (psi_1_E_pl_h - psi_1_E_mi_h) / (2.0 * h);
    // *****
    // Newton-Raphson step
    double dE = psi_1_E / dpsi_1_E;
    if(fabs(dE) < dE_min){
      break;
    }
    E = E - dE;
    // *****
    // fprintf(stderr, "E_num = %+10.6lf , E_ana = %+10.6lf , \\psi(x=1) = %+.6lf .\n",
    // E, M_PI*M_PI, psi_1_E);
    // fprintf(stderr, "E_num = %+10.6lf , E_ana = %+10.6lf , \\psi(x=1) = %+.6lf .\n",
    // E, 4.0*M_PI*M_PI, psi_1_E);
    fprintf(stderr, "E_num = %+10.6lf , E_ana = %+10.6lf , \\psi(x=1) = %+.6lf .\n",
    E, 9.0*M_PI*M_PI, psi_1_E);
  }
  // output
  RK(true);
  // */
  // **********
  // **********
  // **********
  return EXIT_SUCCESS;
}
