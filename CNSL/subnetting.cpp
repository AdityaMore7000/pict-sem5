#include <bits/stdc++.h>
#include <cstdlib>

using namespace std;

void checkClass(string IP)
{
    cout << "IP class : "
         << " ";
   
    int firstOct = IP.find('.');
    string fOct = IP.substr(0, firstOct);

    if (stoi(fOct) >= 0 && stoi(fOct) <= 127)
    {
        cout << "Class A" << endl;
        cout<<endl;
        cout << "Default subnetMask: 255.0.0.0\n";
    }
    else if (stoi(fOct) >= 128 && stoi(fOct) <= 191)
    {
        cout << "Class B" << endl;
        cout<<endl;
        cout << "Default subnetMask: 255.255.0.0\n";
    }
    else if (stoi(fOct) >= 192 && stoi(fOct) <= 224)
    {
        cout << "Class C" << endl;
        cout<<endl;
        cout << "Default subnetMask: 255.255.255.0\n";
    }
    else if (stoi(fOct) >= 225 && stoi(fOct) <= 239)
    {
        cout << "Class D" << endl;
        cout<<endl;
        cout << "Default subnetMask: not defined\n";
    }
    else if (stoi(fOct) >= 240 && stoi(fOct) <= 255)
    {
        cout << "Class E" << endl;
        cout<<endl;
        cout << "Default subnetMask: not defined\n";
    }
   
}

void createSubnet(string IP, int n)
{
   
    int bitToTransfer = ceil(log(n)/log(2.0));
    cout<<"No. of bits to transfer : "<<bitToTransfer<<endl;
    cout<<endl;
    int subnettedMask = 0;

    for (int i = 7; i > 7 - bitToTransfer; i--)
    {
        subnettedMask += pow(2, i);
    }
    cout << "Subnet Mask: "
         << "255.255.255." << to_string(subnettedMask);

    // show range of each subnet
    int rangeToAdd = pow(2, 8 - bitToTransfer);
    int varNum = 0;
    cout<<endl;
    cout << "\nRange : \n";
    int thirdDot = IP.find_last_of('.');

    string threeOct = IP.substr(0, thirdDot);
    int flag=0;
    for (int i = 0; i < n - 1 || varNum+rangeToAdd-1<255; i++)
    {
        if(varNum>=(rangeToAdd*n) && !flag){
            cout<<endl;
            cout<<"Unused subnets -> "<<endl;
            flag=!flag;
        }
        cout << threeOct << "." << varNum << " - ";
        varNum += rangeToAdd - 1;
        cout << threeOct << "." << varNum << endl;
        varNum++;
    }
    cout << threeOct << "." << varNum << " - " << threeOct << "." << varNum + rangeToAdd - 1 << endl;
}

int main()
{
    int noSbnet;
    string IP;
    cout << "No. of subnets ? : ";
    cin >> noSbnet;
    cout<<endl;
    cout << "Enter the IP: ";
    cin >> IP;
   cout<<endl;
    checkClass(IP);
    cout<<endl;
    createSubnet(IP, noSbnet);
    cout << endl; 
    cout << endl;

    char cmd[20] = "ping ";
    for (int i = 0; i < IP.length(); i++)
    {
        cmd[5 + i] = IP[i];
    }
    system(cmd);
    // 10.10.14.201
    return 0;
}