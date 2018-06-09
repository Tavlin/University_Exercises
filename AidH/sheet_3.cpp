#include <iostream>
#include <fstream>
#include <cmath>
#include <stdlib.h>
#include <string.h>

using namespace std;

// anlegen der arrays x und y
const int array_lenght = 10;
double x[array_lenght] = {0.62, 1.25, 1.91, 3.01, 4.22, 5.89, 6.12, 6.86, 8.07, 9.43};
double y[array_lenght] = {0.572, 0.663, 1.32, 1.79, 2.71, 3.52, 3.49, 4., 4.84, 5.58};

// Funktion zur Ausgabe der Tuple (x,y)
void print_array(const int array_lenght, double* array1, double* array2){
  for (int i = 0; i < array_lenght; i++) {
    cout << "(" << array1[i] << "," << array2[i] << ")" << endl;
  }
}

// Funktion zur Berechnung des Mittelwertes von y/x
void mean_calc(const int array_lenght, double* array1, double* array2){
  double sigma = 0;
  double mean, mean_squared;
  mean = 0;
  mean_squared = 0;

  for (int i = 0; i < array_lenght; i++) {
    mean += array2[i]/array1[i];
    mean_squared += pow(array2[i]/array1[i],2.);
  }
  mean /= array_lenght;
<<<<<<< HEAD
  mean *= mean;
  mean_squared /= array_lenght;
  cout << " <y/x>² = " << mean << endl;
  cout << " <(y/x)²> = " << mean_squared << endl;
=======
  cout << "mean = " << mean << endl;
  mean *= mean;
  mean_squared /= array_lenght;
  cout << " <y/x>Â² = " << mean << endl;
  cout << " <(y/x)Â²> = " << mean_squared << endl;
>>>>>>> aeb99fc5d81f72b1734f496af5ea1caa0021f271
  sigma = sqrt(mean_squared-mean);
  cout << "sigma = " << sigma << endl;
}


int main(void){

  print_array(array_lenght, x, y);
  mean_calc(array_lenght, x, y);

  return 0;
}
