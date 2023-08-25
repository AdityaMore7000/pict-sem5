//============================================================================
// Name        : Assign2_31152_04082023.cpp
// Author      : AdityaMore7000
// Version     :1.0.0
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <bits/stdc++.h>
using namespace std;
long convertToBinary(long n){
	long ans = 0;
	while (n > 0) {
	        ans*=10;
	        ans += n % 2;
	        n = n / 2;
	    }
	    string long_to_string = to_string(ans);
	    string final ="";
	    for(int i = long_to_string.size()-1;i>=0;i--){
	    	final +=long_to_string[i];
	    }
	    ans = stoll(final);
	return ans;
}

long countSetBits(long n) {
    if (n == 0) return 1;
    long count = 0;
    while (n > 0) {
        count += 1;
        n /= 10;
    }
    return count;
}

int main() {
    cout << "Enter value: ";
    char ch;
    cin>>ch;
    cout<<"Entered value is: "<<ch<<'\n';
    int n = int(ch);
    cout<<"ASCII Code is: "<<n<<'\n';
    long number = convertToBinary(n);
//    cin >> number;

    cout << "Final Hamming Array: ";
    long m = countSetBits(number);
    long r = 1;
    while (pow(2, r) < m + r + 1) {
        r++;
    }
    cout<<""<<r<<'\n';
    // Generate Parity Bits
    vector<long> parityArrayPos(r);
    for (long i = 0; i < r; i++) {
        parityArrayPos[i] = pow(2, i);
    }

    vector<long> parityArray(r, -1);

    // Initial Hamming Array Calculation
    vector<long> hammingArray(r + m);
    int j = 0;
    for (int i = 0; i < r + m; i++) {
        if (j < r && i == parityArrayPos[j] - 1) {
            hammingArray[i] = parityArray[j];
            j++;
        } else {
            long x = number % 10;
            hammingArray[i] = x;
            number = number / 10;
        }
    }

//    cout << "Initial Hamming Array: ";
//    for (const auto& val : hammingArray) {
//        cout << val << " ";
//    }
//    cout << endl;
    for (int i = 0; i < r; i++) {
        string s1 = "";
        for (int k = parityArrayPos[i] - 1; k < r + m; k++) {
            if ((k + 1) & (1 << i)) {
                s1 += to_string(hammingArray[k]);
            }
        }

        int oneCount = 0;
        for (int a = 0; a < s1.length(); a++) {
            if (s1[a] == '1') {
                oneCount++;
            }
        }
        parityArray[i] = oneCount % 2;
    }

    j = 0;
    for (int i = 0; i < r + m; i++) {
        if (j < r && i == parityArrayPos[j] - 1) {
            hammingArray[i] = parityArray[j];
            j++;
        }
    }
    for (const auto& val : hammingArray) {
        cout << val;
    }
    cout << endl;
    return 0;
}
