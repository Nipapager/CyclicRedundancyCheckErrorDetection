#include <iostream>
#include "CRC.h"
#include <time.h>
#include <deque>
#include <fstream>

using namespace std;


int main()
{
    ofstream out;
    out.open("output.txt", ios::out);   // create a text file to save the results
    srand(time(NULL));      // to prevent repeats between runs
    CRC crc;
    int num;                // Number of messages to be transmitted
    deque<int> P;
    float total = 0;               // Total messages
    float transmited = 0;          // Total transmitted messages
    float NonDetectableErrors = 0; // Total transmitted messages that have errors
    float DetectableErrors = 0;    // Total messages with errors that detected and did not transmit


    cout << "Write the number of messages: ";
    cin >> num;
    cout << endl;

    crc.setK();
    crc.setBER();
    crc.setP();

    for (int i=0; i<num; i++)    // Create num messages
    {
        deque<int> D;
        deque<int> T;
        bool E = false;          // bool variable that becomes true if a bit of T changed
        D = crc.generateD();     // Determine D
        T = crc.calculateT(D);   // Determine T
        total++;

        // Save every random number D and every sequence T in output.txt
        //==============================================================
        out << i+1 << ". Random D = ";
        for (int i=0; i<D.size(); i++)
            out << D[i] << "";
        out << endl;
        out << i+1 << ". T = ";
        for (int i=0; i<T.size(); i++)
            out << T[i] << "";
        out << endl << endl;
        //===============================================================

        // For every digit of T there is a possibility BER to be changed
        for (int j=0; j<T.size(); j++)
        {
            if ((rand() % (int)(1/crc.getBER()))==1)
            {
                T[j] = (T[j]==1) ? 0 : 1;   // If it was 0 it becomes 1, else 0
                E = true;                   // E becomes true because there is a change on T
            }
        }

        // If sequence T transmitted to the receiver
        if (crc.transmitT(T))
        {
            transmited++;
            if (E)
                NonDetectableErrors++;
        }
        else
            if (E) DetectableErrors++;

    }

    cout << "==================================================================" << endl;
    cout << "Total Messages: " << total << endl;
    cout << "Total Transmited: " << transmited << endl;
    cout << "Total Detected: " << DetectableErrors << endl;
    cout << "Total Non Detected: " << NonDetectableErrors << endl;
    cout << "==================================================================" << endl;
    cout << "Messages reached receiver with error: " << ((DetectableErrors+NonDetectableErrors)/total)*100 << "%" << endl;
    cout << "Messages with errors detected from receiver " << (DetectableErrors/total)*100 << "%" << endl;
    cout << "Messages with errors but couldn't be detected from receiver " << (NonDetectableErrors/total)*100 << "%" << endl;

    // Save results in output.txt
    out << "==================================================================" << endl;
    out << "Total Messages: " << total << endl;
    out << "Total Transmited: " << transmited << endl;
    out << "Total Detected: " << DetectableErrors << endl;
    out << "Total Non Detected: " << NonDetectableErrors << endl;
    out << "==================================================================" << endl;
    out << "Messages reached receiver with error: " << ((DetectableErrors+NonDetectableErrors)/total)*100 << "%" << endl;
    out << "Messages with errors detected from receiver " << (DetectableErrors/total)*100 << "%" << endl;
    out << "Messages with errors but couldn't be detected from receiver " << (NonDetectableErrors/total)*100 << "%" << endl;

    out.close();
    return 0;
}
