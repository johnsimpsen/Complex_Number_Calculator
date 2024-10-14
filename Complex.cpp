//
// Created by john simpsen on 9/25/2024.
//

#include "Complex.h"

double Complex::calculateMagnitude() const {
    double a = pow(realNumber, 2);
    double b = pow(imaginaryNumber, 2);
    return fabs(sqrt(a + b));
}