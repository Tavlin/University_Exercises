#include <cmath>
#include <vector>
#include <algorithm>
#include <numeric>
#include <omp.h>
#include "iostream"

using namespace std;

using vec    = vector<double>;         // vector
using matrix = vector<vec>;            // matrix

vec GetSolution(matrix* A ,matrix* Q, double t);
