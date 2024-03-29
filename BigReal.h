#ifndef _BIGREAL_H
#define _BIGREAL_H
#include "BigDecimalIntClass.cpp"
using namespace std;

class BigReal{
private:
    BigDecimalInt number,fraction;
public:
    BigReal (double realNumber = 0.0); // Default constructor
    BigReal (string realNumber); //Initialize from a string
    BigReal (BigDecimalInt bigInteger); //Initialize from a BigDecimalInt object
    BigReal (const BigReal& other); // Copy constructor
    BigReal (BigReal&& other); // Move constructor
    BigReal& operator= (BigReal& other); // Assignment operator
    BigReal& operator= (BigReal&& other); // Move assignment
    BigReal operator+ (BigReal& other);
    BigReal operator- (BigReal& other);
    bool operator< (BigReal anotherReal);
    bool operator> (BigReal anotherReal);
    bool operator== (BigReal anotherReal);
    int size();
    int Sign();
    friend ostream& operator << (ostream& out, BigReal num);
    friend istream& operator >> (istream& out, BigReal& num);
};


#endif //_BIGREAL_H
