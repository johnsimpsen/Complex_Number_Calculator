//
// Created by john simpsen on 9/25/2024.
//

#ifndef NUMBER_H
#define NUMBER_H
#include <ostream>


//Base Class
class Number {
protected:

    double realNumber;

public:

    //constructors
    Number() {realNumber = 0.0;}
    Number(double r) {realNumber = r;}

    virtual ~Number() {}

    //accessors
    double getRealNumber() const {return realNumber;}

    //mutators
    void setRealNumber(double r) {realNumber = r;}

    //overloaded operators
    friend std::ostream& operator<<(std::ostream& out, Number& n);

    //overloaded comparison operators
    bool operator==(Number& rhs);
    bool operator>(Number& rhs);
    bool operator<(Number& rhs);

    //overloaded arithmetic operators
    Number* operator+(Number& rhs);
    Number* operator-(Number& rhs);
    Number* operator*(Number& rhs);
    Number* operator/(Number& rhs);
};

#endif //NUMBER_H
