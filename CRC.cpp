#include "CRC.h"
#include <iostream>
#include <time.h>
#include <deque>

using namespace std;

// Ask user to set value for variable K
void CRC::setK()
{
    cout << "Write the number of bits of data D that is to be transmitted (k): ";
    cin >> k;
    cout << endl;
}

// Ask user to set the Bit Error Rate
void CRC::setBER()
{
    cout << "Write the Bit Error Rate (e.g. 0.001): ";
    cin >> BER;
    cout << endl;
}

// Ask user to set value for the binary number P
void CRC::setP()
{
    int temp;
    cout << "Write the binary number P, which divides the sequence T: ";
    cin >> temp;    // Save the answer to int variable temp
    cout << endl;
    while (temp>0)  // Copy each digit of user's answer to the deque P
    {
        n++;        // count the number of P digits
        P.push_front(temp%10);
        temp /= 10;
    }
    n = n + k - 1;  // Determine the number of digits of sequence T
}

// Return the BER value
double CRC::getBER()
{
    return BER;
}

// Determine the sequence D
deque<int> CRC::generateD()
{
    deque<int> D;
    for (int i=0; i<k; i++)
        D.push_front(rand() % 2);
   // cout << "Random Data sequence generated: D = ";
   // for (int i=0; i<D.size(); i++)
    //    cout << D[i] << "";
   // cout << endl;
    return D;

}

// logical operator XOR
int CRC::XOR(int a, int b)
{
    return (a+b) % 2;
}

// Calculate sequence T
deque<int> CRC::calculateT(deque<int> D)
{
    deque<int> R;   // Remainder of division
    deque<int> T;

    for (int i=k; i<n; i++)
        D.push_back(0);         // Fill the D with zeros until his size is equal to <k + (size of P) - 1>

    R = modulo2(D, P);          // Remainder of D/R

    for (int i=0; i<k; i++)
        T.push_back(D[i]);      // First k digits of T are the same with D
    for (int i=0; i<R.size(); i++)
        T.push_back(R[i]);      // Last n-k digits are equal to the remainder R

   // for (int i=0; i<T.size(); i++)
   //     cout << T[i] << "";
   // cout << endl;

    return T;
}

// calculates the mod between two binary numbers.
deque<int> CRC::modulo2(deque<int> Dividend, deque<int> Divisor)
{
    deque<int> Remainder;
    int slot = 0;          // The position which Divisor is put
    for (int i=0; i<Dividend.size(); i++)
        Remainder.push_back(Dividend[i]);       // Firstly remainder is equal to the Dividend

    while (slot < k)        // Divide until last digit of Divisor reaches the last digit of Dividend
    {

        for (int i=0; i<Divisor.size(); i++)
            Remainder[slot+i] = XOR(Remainder[slot+i], Divisor[i]);

        while (Remainder[slot]==0 && slot<Remainder.size())     // Skip the zero digits of Remainder
            slot++;

    }

    for (int i=0; i<k; i++)
        Remainder.pop_front();      // Keep only the last n-k digits of Remainder

    return Remainder;
}

// Checks if T is transmitted to the receiver
bool CRC::transmitT(deque<int> T)
{
    deque<int> R;
    R = modulo2(T, P);
    for (int i=0; i<R.size(); i++)
        if (R[i]==1)
            return false;
    return true;
}
