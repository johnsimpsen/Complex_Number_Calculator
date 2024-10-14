//
// Created by john simpsen on 9/25/2024.
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>

#include "Number.h"
#include "Complex.h"

using namespace std;

constexpr int NUM_OF_INPUTS = 20;
constexpr int NUM_OF_EXPS = 2;

//Prototypes
void readFile(const string& filename, Number* numbers[NUM_OF_INPUTS][NUM_OF_EXPS], char operators[NUM_OF_INPUTS]);
void outputResults(const string& filename, Number* numbers[NUM_OF_INPUTS][NUM_OF_EXPS], char operators[NUM_OF_INPUTS]);
void addNumber(const string& num, Number* numbers[NUM_OF_INPUTS][NUM_OF_EXPS], int row, int col);
void addOperator(char opp, char operators[NUM_OF_INPUTS], int row);
bool validateLine(string line);
Number* calculateArithmeticResult(Number* numbers[NUM_OF_INPUTS][NUM_OF_EXPS], char operators[NUM_OF_INPUTS], int row);
bool calculateComparisonResult(Number* numbers[NUM_OF_INPUTS][NUM_OF_EXPS], char operators[NUM_OF_INPUTS], int row);

int main() {
    //2D array full of expressions
    Number* numbers[NUM_OF_INPUTS][NUM_OF_EXPS];

    //1D Array full of operators
    char operators[NUM_OF_INPUTS];

    //Initialize input file
    string filename;
    cout << "Input File: ";
    cin >> filename;
    readFile(filename, numbers, operators);

    //Print results out
    outputResults(filename, numbers, operators);
}

//Verifies the file opens
//Parses each line and puts the left & right expressions and their operators into their own arrays
void readFile(const string& filename, Number* numbers[NUM_OF_INPUTS][NUM_OF_EXPS], char operators[NUM_OF_INPUTS]) {

    ifstream input("../" + filename);

    if (!input.is_open()) {
        cout << "Error: Could not open file: " << filename << endl;
        exit(1);
    }

    //parse each line
    string line;
    int i = 0;
    while(getline(input, line)) {

        //Checks to see if the line is in the correct format
        if (validateLine(line)) {
            string num;
            char opp;
            int index;

            //First expression
            index = line.find(' ');
            num = line.substr(0, index);
            addNumber(num, numbers, i, 0);

            //Middle Operator
            index = line.find(' ');
            opp = line.substr(index+1, 1)[0]; //String to char conversion
            addOperator(opp, operators, i);


            //Second Expression
            index = line.find_last_of(' ');
            num = line.substr(index+1);
            addNumber(num, numbers, i, 1);
        }
        else {
            addOperator('X', operators, i);
        }
        i+=1;
    }
    input.close();
}


//Outputs all results in the correct format
void outputResults(const string& filename, Number* numbers[NUM_OF_INPUTS][NUM_OF_EXPS], char operators[NUM_OF_INPUTS]) {

    //open file
    ifstream input("../" + filename);

    string line;
    int i = 0;
    while(getline(input, line)) {
        //Operator is X if the line was invalid, don't output anything
        //Arithmetic Results
        if (operators[i] == '+' || operators[i] == '-' || operators[i] == '*' || operators[i] == '/')
            cout << line << "\t" << *calculateArithmeticResult(numbers, operators, i) << endl;
        //Comparison Results
        else if (operators[i] == '<' || operators[i] == '>' || operators[i] == '=')
            cout << boolalpha << line << " " << calculateComparisonResult(numbers, operators, i) << endl;

        i+=1;
    }
    input.close();
}

//Determine whether the passed in expression is complex, imaginary only, or real
//Create an object that fits the data type and add it to the list of expressions
void addNumber(const string& num, Number* numbers[NUM_OF_INPUTS][NUM_OF_EXPS], int row, int col) {
    //complex: real (+ or -) imaginary
    //ignores the first character of the string while searching for '-' in case it's a negative, non-imaginary number
    size_t index2 = num.find_first_of("+-", 1); // Find first '+' or '-' after first character

    //Complex
    if (index2 != string::npos && num.find('i') != string::npos) {
        double real = stod(num.substr(0, index2));
        double imag = stod(num.substr(index2, num.size() - index2 - 1));
        numbers[row][col] = new Complex(real, imag);
    }
    //Imaginary only
    else if (num.find('i') != string::npos) {
        double imag = stod(num.substr(0, num.size() - 1)); // Remove 'i' and convert
        numbers[row][col] = new Complex(0, imag); // Real part is 0
    }
    //Real only
    else {
        numbers[row][col] = new Number(stod(num)); // Convert to real number
    }
}

//Adds the middle operator to a list of chars
void addOperator(char opp, char operators[NUM_OF_INPUTS], int row) {
    if (opp == '+')
        operators[row] = '+';
    else if (opp == '-')
        operators[row] = '-';
    else if (opp == '*')
        operators[row] = '*';
    else if (opp == '/')
        operators[row] = '/';
    else if (opp == '<')
        operators[row] = '<';
    else if (opp == '>')
        operators[row] = '>';
    else if (opp == '=')
        operators[row] = '=';
    //For errors
    else
        operators[row] = 'X';
}

//Add in Final Implementation
bool validateLine(string line) {
    string num1;
    string num2;

    //Check if there are the necessary spaces
    int index = line.find(' ');
    if (index == string::npos) {
        return false;
    }

    //Check for <space><operator><space>
    if (!(line[index+1] == '+' || line[index+1] == '-' || line[index+1] == '*' || line[index+1] == '/' || line[index+1] == '<' || line[index+1] == '>' || line[index+1] == '=')) {
        return false;
    }
    if (line[index+2] != ' ') {
        return false;
    }

    num1 = line.substr(0, index);
    num2 = line.substr(index+3);

    if (num1.size() == 0 || num2.size() == 0)
        return false;

    //Determine if the num contains '*' or '/'
    index = num1.find('*');
    if (index != string::npos)
        return false;
    index = num1.find('/');
    if (index != string::npos)
        return false;
    index = num2.find('*');
    if (index != string::npos)
        return false;
    index = num2.find('/');
    if (index != string::npos)
        return false;

    //Make sure each expression in the num does not have more than one decimal point
    index = num2.find('+');
    if (index == string::npos)
        index = num2.find('-');
    if (index == string::npos)
        index = num2.find('*');
    if (index == string::npos)
        index = num2.find('/');

    string exp1 = num2.substr(0, index);
    string exp2 = num2.substr(index+1);

    int numDecimal = 0;
    for (int i = 0; i < exp1.size(); i++) {
        if (exp1[i] == '.')
            numDecimal += 1;
    }
    if (numDecimal > 1)
        return false;

    numDecimal = 0;
    for (int i = 0; i < exp2.size(); i++) {
        if (exp2[i] == '.')
            numDecimal += 1;
    }
    if (numDecimal > 1)
        return false;

    //Make sure there is only one complex num (only one 'i' per expression) in num1
    //Make sure 'i' is the only alphabetic character in num1
    int numComplex = 0;
    for (int i = 0; i < num1.size(); i++) {
        if (num1[i] == 'i')
            numComplex += 1;
        if (isalpha(num1[i]) && num1[i] != 'i')
            return false;
    }
    if (numComplex > 1)
        return false;

    //Make sure there is only one complex num (only one 'i' per expression) in num2
    //Make sure 'i' is the only alphabetic character in num1
    numComplex = 0;
    for (int i = 0; i < num2.size(); i++) {
        if (num2[i] == 'i')
            numComplex += 1;

        if (isalpha(num2[i]) && num2[i] != 'i')
            return false;
    }
    if (numComplex > 1)
        return false;


    //Determine if dividing, if true then make sure the second expression is not equal to zero
    index = line.find('/');
    if (index != string::npos && num2 == "0") {
        return false;
    }

    return true;
}

//Returns the result of doing some arithmetic operation on two expressions
Number* calculateArithmeticResult(Number* numbers[NUM_OF_INPUTS][NUM_OF_EXPS], char operators[NUM_OF_INPUTS], int row) {
    Number* result;

    if (operators[row] == '+')
        result = *numbers[row][0] + *numbers[row][1];
    else if (operators[row] == '-')
        result = *numbers[row][0] - *numbers[row][1];
    else if (operators[row] == '*')
        result = *numbers[row][0] * *numbers[row][1];
    else if (operators[row] == '/')
        result = *numbers[row][0] / *numbers[row][1];

    return result;
}

//Returns the result of doing some comparison operation on two expressions
bool calculateComparisonResult(Number* numbers[NUM_OF_INPUTS][NUM_OF_EXPS], char operators[NUM_OF_INPUTS], int row) {
    if (operators[row] == '<')
        return *numbers[row][0] < *numbers[row][1];
    else if (operators[row] == '>')
        return *numbers[row][0] > *numbers[row][1];
    else if (operators[row] == '=')
        return *numbers[row][0] == *numbers[row][1];
    else
        return false;
}