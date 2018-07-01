#include <cmath>
#include <vector>
#include <algorithm>
#include <numeric>
#include <omp.h>
using namespace std;


using vec    = vector<double>;         // vector
using matrix = vector<vec>;            // matrix
const double epsilon = 1.0e-20;

void JacobiRotation(matrix& A, matrix& Q);
