#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath> 
#include <unistd.h> // Include this for sleep function
#include <algorithm> // Include this for sort function

using namespace std;

void gbn(int ws, int nf)
{
    ws = pow(2, ws) - 1;
    cout << "Window size: " << ws << endl;
    int tr(0);
    srand(time(0)); // Use time as seed for srand

    int i = 1;

    while (i <= nf)
    {
        int inc = 0;

        for (int j = i; j < i + ws && j <= nf; j++)
        {
            cout << "Sent frame " << j << endl;
            tr++;
            sleep(1); // Use sleep instead of Sleep
        }

        for (int j = i; j < i + ws && j <= nf; j++)
        {
            int flag = rand() % 2;

            if (!flag)
            {
                cout << "Ack. received for " << j << endl;
                tr++;
                inc++;
                sleep(1); // Use sleep instead of Sleep
            }
            else
            {
                cout << "Ack failed for " << j << endl;
                sleep(1); // Use sleep instead of Sleep
                cout << "Retransmitting the window" << endl;
                sleep(1); // Use sleep instead of Sleep
                break;
            }
        }
        i = i + inc;
        cout << endl;
        cout << "<---Window slided--->" << endl;
        cout << endl;
    }
}

void selective(int ws, int nf)
{
    ws = pow(2, ws - 1);
    cout << "Window size: " << ws << endl;
    int MAX_INPUT = 1000;
    srand(time(0)); // Use time as seed for srand

    int drop_pack[nf + 1];
    int ack_rec = 0;
    int last_pack = 0;
    int last_pack_ack = last_pack;
    int insertHere = 1;
    int i = 1;

    for (int i = 0; i <= nf + 1; i++)
    {
        drop_pack[i] = MAX_INPUT;
    }

    while (ack_rec < nf)
    {

        for (int i = 1; i <= ws && ack_rec < nf; i++)
        {
            if (drop_pack[i] != MAX_INPUT)
            {
                cout << "Sent frame " << drop_pack[i] << endl;
                sleep(1); // Use sleep instead of Sleep
            }
            else
            {
                if (last_pack == nf)
                {
                    continue;
                }
                cout << "Sent frame " << last_pack + 1 << endl;
                last_pack++;
                insertHere++;
                sleep(1); // Use sleep instead of Sleep
            }
        }

        for (int i = 1; i <= ws && ack_rec < nf; i++)
        {
            int flag = rand() % 2;
            if (!flag)
            {
                if (drop_pack[i] != MAX_INPUT)
                {
                    cout << "Ack received for frame " << drop_pack[i] << endl;
                    sleep(1); // Use sleep instead of Sleep
                    drop_pack[i] = MAX_INPUT;
                }
                else
                {
                    if (last_pack_ack == nf)
                        continue;
                    cout << "Ack received for frame " << last_pack_ack + 1 << endl;
                    sleep(1); // Use sleep instead of Sleep
                    last_pack_ack++;
                }
                ack_rec++;
                cout << endl;
                cout << "<---Window slides--->" << endl;
                cout << endl;
            }
            else
            {
                if (drop_pack[i] != MAX_INPUT)
                {
                    cout << "Ack failed for frame " << drop_pack[i] << endl;
                    sleep(1); // Use sleep instead of Sleep
                }
                else
                {
                    if (last_pack_ack == nf)
                        continue;
                    cout << "Ack failed for frame " << last_pack_ack + 1 << endl;
                    sleep(1); // Use sleep instead of Sleep
                    drop_pack[insertHere] = last_pack_ack + 1;
                    last_pack_ack++;
                    insertHere++;
                }
            }
        }

        sort(drop_pack + 1, drop_pack + nf + 1);
        for (int i = 1; i <= nf + 1; i++)
        {
            if (drop_pack[i] == MAX_INPUT)
            {
                insertHere = i;
                break;
            }
        }
    }
}

int main()
{
    int choice;
    int nf, ws;
    cout << "Enter the no of frames :";
    cin >> nf;
    cout << "Enter the no of bits :";
    cin >> ws;

    while (1)
    {
        cout << "\n1.Go-Back-N\n2.Selective Repeat\n3.Exit" << endl;
        cin >> choice;
        if (choice == 1)
        {
            gbn(ws, nf);
        }
        else if (choice == 2)
        {
            selective(ws, nf);
        }
        else if (choice == 3)
        {
            exit(0);
        }
    }
}
