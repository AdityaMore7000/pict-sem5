//============================================================================
// Name        : Assign2_31152_04082023.cpp
// Author      : AdityaMore7000
// Version     :1.0.0
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <iostream>
#include <vector>
#include <cmath>
#include <string>

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
    std::cout << "Enter Number: ";
    long number;
    std::cin >> number;

    long m = countSetBits(number);
    long r = 1;
    while (pow(2, r) < m + r + 1) {
        r++;
    }

    // Generate Parity Bits
    std::vector<long> parityArrayPos(r);
    for (long i = 0; i < r; i++) {
        parityArrayPos[i] = pow(2, i);
    }

    std::vector<long> parityArray(r, -1);

    // Initial Hamming Array Calculation
    std::vector<long> hammingArray(r + m);
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

    std::cout << "Initial Hamming Array: ";
    for (const auto& val : hammingArray) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    // Calculate R1, R2 ...
    for (int i = 0; i < r; i++) {
        std::string s1 = "";
        for (int k = parityArrayPos[i] - 1; k < r + m; k++) {
            if ((k + 1) & (1 << i)) {  // Check if k+1 has bit i set
                s1 += std::to_string(hammingArray[k]);
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

    std::cout << "Final Hamming Array: ";
    for (const auto& val : hammingArray) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    return 0;
}
