#include <math.h>
#include "contract.h"

double derivative_central(double A, double deltaX) {
    return (cos(A + deltaX) - cos(A - deltaX)) / (2 * deltaX);
}