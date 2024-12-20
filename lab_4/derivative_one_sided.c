#include <math.h>
#include "contract.h"

double derivative_one_sided(double A, double deltaX) {
    return (cos(A + deltaX) - cos(A)) / deltaX;
}