#ifndef CRC_H_INCLUDED
#define CRC_H_INCLUDED
#include <iostream>
#include <deque>

using namespace std;

class CRC
{
private:
    deque<int> P;       // Binary number P divides message D
    int k;              // Number of D's digits
    int n = 0;          // Number of T's digits
    double BER;         // Bit Error Rate


public:
    CRC(){};            // Empty Constructor
    void setK();        // Return the BER value
    void setBER();      // Ask user to set the Bit Error Rate
    void setP();        // Ask user to set value for the binary number P
    double getBER();    // Return the BER value
    deque<int> generateD();     // logical operator XOR
    int XOR(int, int);                              // logical operator XOR
    deque<int> calculateT(deque<int>);              // Calculate sequence T
    bool transmitT(deque<int>);                     // Checks if T is transmitted to the receiver
    deque<int> modulo2(deque<int>, deque<int>);     // calculates the mod between two binary numbers.



};


#endif // CRC_H_INCLUDED
