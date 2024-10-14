//
// Created by john simpsen on 9/25/2024.
//

#include "Number.h"
#include "Complex.h"

//overloaded operators
std::ostream& operator<<(std::ostream& out, Number& n) {
    //Check if Complex or Number (nullptr if Number)
    Complex* b = dynamic_cast<Complex*>(&n);

    out << std::fixed << std::setprecision(2);

    //check if passed in object is a complex
    if (b) {
        //Real number is zero, Imaginary only
        if (b->getRealNumber() == 0)
            out << b->getImaginaryNumber() << "i";
        //Real number is zero, Imaginary only
        else if (b->getImaginaryNumber() == 0)
            out << b->getRealNumber();
        //Positive imaginaryNumber output
        else if (b->getImaginaryNumber() >= 0)
            out << b->getRealNumber() << "+" << b->getImaginaryNumber() << "i";
        //Negative imaginaryNumber output
        else
            out << b->getRealNumber() << "-" << fabs(b->getImaginaryNumber()) << "i";
    }
    else {
        out << n.getRealNumber();
    }
    return out;
}

//overloaded comparison operators
bool Number::operator==(Number& rhs) {
    //Check if Complex or Number (nullptr if Number)
    Complex* a = dynamic_cast<Complex*>(this);
    Complex* b = dynamic_cast<Complex*>(&rhs);

    //Complex == Complex
    if (a && b) {
        return a == b;
    }
    //Complex == Number
    else if (a) {
        return a->calculateMagnitude() == rhs.realNumber;
    }
    //Number == Complex
    else if (b) {
        return this->realNumber == b->calculateMagnitude();
    }
    //Number == Number
    else
        return this->realNumber == rhs.realNumber;
}

bool Number:: operator>(Number& rhs) {
    //Check if Complex or Number (nullptr if Number)
    Complex* a = dynamic_cast<Complex*>(this);
    Complex* b = dynamic_cast<Complex*>(&rhs);

    //Complex > Complex
    if (a && b) {
        return a->calculateMagnitude() > b->calculateMagnitude();
    }
    //Complex > Number
    else if (a) {
        return a->calculateMagnitude() > rhs.realNumber;
    }
    //Number > Complex
    else if (b) {
        return this->realNumber > b->calculateMagnitude();
    }
    //Number > Number
    else
        return this->realNumber > rhs.realNumber;
}

bool Number::operator<(Number& rhs) {
    //Check if Complex or Number (nullptr if Number)
    Complex* a = dynamic_cast<Complex*>(this);
    Complex* b = dynamic_cast<Complex*>(&rhs);

    //Complex < Complex
    if (a && b) {
        return a->calculateMagnitude() < b->calculateMagnitude();
    }
    //Complex < Number
    else if (a) {
        return a->calculateMagnitude() < rhs.realNumber;
    }
    //Number < Complex
    else if (b) {
        return this->realNumber < b->calculateMagnitude();
    }
    //Number < Number
    else
        return this->realNumber < rhs.realNumber;
}

Number* Number::operator+(Number& rhs) {
    Complex* res = new Complex();
    //Check if Complex or Number (nullptr if Number)
    Complex* a = dynamic_cast<Complex*>(this);
    Complex* b = dynamic_cast<Complex*>(&rhs);

    res->setRealNumber(this->getRealNumber() + rhs.getRealNumber());

    //Complex + Complex
    if (a && b) {
        res->setImaginaryNumber(a->getImaginaryNumber() + b->getImaginaryNumber());
    }
    //Complex + Number
    else if (a) {
        res->setImaginaryNumber(a->getImaginaryNumber());
    }
    //Number + Complex
    else if (b) {
        res->setImaginaryNumber(b->getImaginaryNumber());
    }

    return res;
}

Number* Number::operator-(Number& rhs) {
    Complex* res = new Complex();
    //Check if Complex or Number (nullptr if Number)
    Complex* a = dynamic_cast<Complex*>(this);
    Complex* b = dynamic_cast<Complex*>(&rhs);

    res->setRealNumber(this->getRealNumber() - rhs.getRealNumber());

    //Complex - Complex
    if (a && b) {
        res->setImaginaryNumber(a->getImaginaryNumber() - b->getImaginaryNumber());
    }
    //Complex - Number
    else if (a) {
        res->setImaginaryNumber(a->getImaginaryNumber());
    }
    //Number - Complex
    else if (b) {
        res->setImaginaryNumber(b->getImaginaryNumber());
    }

    return res;
}

Number* Number::operator*(Number& rhs) {
    Complex* res = new Complex();

    //Check if Complex or Number (nullptr if Number)
    Complex* a = dynamic_cast<Complex*>(this);
    Complex* b = dynamic_cast<Complex*>(&rhs);

    //Multiply the real numbers first
    res->setRealNumber(this->getRealNumber() * rhs.getRealNumber());

    //Complex * Complex
    if (a && b) {
        res->setImaginaryNumber(a->getImaginaryNumber() * b->getRealNumber() + a->getRealNumber() * b->getImaginaryNumber());
        res->setRealNumber(a->getRealNumber() * b->getRealNumber() + -1 * a->getImaginaryNumber() * b->getImaginaryNumber());
    }
    //Complex * Number
    else if (a) {
        res->setImaginaryNumber(a->getImaginaryNumber() * rhs.realNumber);
    }
    //Number * Complex
    else if (b) {
        res->setImaginaryNumber(this->realNumber * b->getImaginaryNumber());
    }

    return res;
}

Number* Number::operator/(Number& rhs) {
    Complex* res = new Complex();
    //Check if Complex or Number (nullptr if Number)
    Complex* a = dynamic_cast<Complex*>(this);
    Complex* b = dynamic_cast<Complex*>(&rhs);

    res->setRealNumber(this->realNumber / rhs.realNumber);

    //Complex / Complex
    if (a && b) {
        int A = a->getRealNumber();
        int B = a->getImaginaryNumber();
        int C = b->getRealNumber();
        int D = b->getImaginaryNumber();

        res->setRealNumber((A*C + B*D)/(pow(C, 2) + pow(D, 2)));
        res->setImaginaryNumber((B*C - A*D)/(pow(C, 2) + pow(D, 2)));
    }
    //Complex / Number
    else if (a) {
        res->setRealNumber(a->getRealNumber() / rhs.realNumber);
        res->setImaginaryNumber(a->getImaginaryNumber() / rhs.realNumber);
    }
    //Number / Complex
    else if (b) {
        int A = this->realNumber;
        int B = 0;
        int C = b->getRealNumber();
        int D = b->getImaginaryNumber();

        res->setRealNumber((A*C + B*D)/(pow(C, 2) + pow(D, 2)));
        res->setImaginaryNumber((B*C - A*D)/(pow(C, 2)+pow(D, 2)));
    }

    return res;
}
