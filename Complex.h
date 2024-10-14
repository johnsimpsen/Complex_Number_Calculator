//
// Created by john simpsen on 9/25/2024.
//

#ifndef COMPLEX_H
#define COMPLEX_H

#include "Number.h"

#include <iostream>
#include <iomanip>
#include <cmath>


//Sub Class
class Complex : public Number {
private:

    double imaginaryNumber;

public:

    //constructors
    Complex() : Number() {imaginaryNumber = 0;}
    Complex(double r, double i) : Number(r) { imaginaryNumber = i;}

    //accessors
    double getImaginaryNumber() const {return imaginaryNumber;}

    //mutators
    void setImaginaryNumber(double i) {imaginaryNumber = i;}

    //methods
    double calculateMagnitude() const;
};



#endif //COMPLEX_H
