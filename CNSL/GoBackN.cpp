#include <iostream> 
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <thread>
#include <chrono>

using namespace std;

int main()
{
    int noofframes = 10, m;
    int count = 0;

    cout << "Enter the Bit size (m-bit): ";
    cin >> m;
    int N = pow(2, m) - 1;
    cout << "Your window size is: " << N << endl;

    srand(time(NULL));
    int i = 1;
    while (i <= noofframes)
    {
        int x = 0;
        for (int j = i; j < i + N && j <= noofframes; j++)
        {
            cout << "Sending the Frame " << j << endl;
            count++;
        }
        bool ackReceived = true;
        for (int j = i; j < i + N && j <= noofframes; j++)
        {
            int flag = rand() % 3; // Increase the range to reduce the probability of 0 (timeout)
            if (flag != 0) // If flag is not 0, consider it as an acknowledgment
            {
                cout << "\nAcknowledgment for Window Received whose first packet is " << j;
                x++;
            }
            else
            {
                cout << "\nData Packet in Cumulative Acknowledgement Not Received whose first packet is " << j;
                cout << "\nRetransmitting the Same Window \n";
                ackReceived = false;
                break;
            }
        }

        if (!ackReceived)
        {
            cout << "\nTimeout occurred. Retransmitting the Same Window \n";
            i -= x;
            if (i < 1)
                i = 1;
        }
        else
        {
            cout << "\nWindow slided" << endl; 
            i += x;
        }

        cout << endl;
    }
    cout << "\nTotal number of transmissions : " << count;
    return 0;
}