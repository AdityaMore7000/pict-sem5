//============================================================================
// Name        : Assign2_31152_04082023.cpp
// Author      : AdityaMore7000
// Version     :1.0.0
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <bits/stdc++.h>
using namespace std;

vector<int> decimalToBinary(int x) {
    int p = x;
    vector<int> output;
    while (p != 0) {
        int m = p / 2;
        output.push_back(p % 2);
        p = m;
    }
    reverse(output.begin(), output.end());
    return output;
}

int binaryToDecimal(const vector<int>& num) {
    int output = 0;
    for (int i = num.size() - 1; i >= 0; i--) {
        output += pow(2, num.size() - 1 - i) * num[i];
    }
    return output;
}

string listToStr(const vector<int>& l) {
    string result;
    for (int bit : l) {
        result += to_string(bit);
    }
    return result;
}

int getEvenParity(const vector<int>& seq) {
    return (accumulate(seq.begin(), seq.end(), 0) % 2 != 0) ? 1 : 0;
}

int getOddParity(const vector<int>& seq) {
    return (accumulate(seq.begin(), seq.end(), 0) % 2 == 0) ? 1 : 0;
}

pair<vector<int>, int> encode(const vector<int>& message, const string& parity) {
    int m = message.size();
    auto parityFunc = (parity == "even") ? getEvenParity : getOddParity;
    int r = 0;
    while (pow(2, r) < m + r + 1) {
        r++;
    }
    vector<int> codeWord(m + r, 0);
    vector<int> parityPositions;

    for (int i = 0; i < r; i++) {
        parityPositions.push_back(pow(2, i) - 1);
    }

    vector<int> dataPositions;
    for (int i = 0; i < m + r; i++) {
        if (find(parityPositions.begin(), parityPositions.end(), i) == parityPositions.end()) {
            dataPositions.push_back(i);
        }
    }

    for (size_t i = 0; i < message.size(); i++) {
        codeWord[dataPositions[i]] = message[i];
    }

    for (size_t i = 0; i < parityPositions.size(); i++) {
        vector<int> paritySeq;
        bool take = true;
        int takeCount = pow(2, i);

        for (size_t j = parityPositions[i]; j < codeWord.size(); j++) {
            if (take) {
                paritySeq.push_back(codeWord[j]);
                takeCount--;
            } else {
                takeCount++;
            }

            if (takeCount == 0) {
                take = false;
            } else if (takeCount == pow(2, i)) {
                take = true;
            }
        }

        codeWord[parityPositions[i]] = parityFunc(paritySeq);
    }

    return make_pair(codeWord, r);
}

vector<int> decode(const vector<int>& codeWord, int r, const string& parity) {
    auto parityFunc = (parity == "even") ? getEvenParity : getOddParity;
    vector<int> parityPositions;

    for (int i = 0; i < r; i++) {
        parityPositions.push_back(pow(2, i) - 1);
    }

    vector<int> parityBits;

    for (int i = 0; i < r; i++) {
        vector<int> paritySeq;
        bool take = true;
        int takeCount = pow(2, i);

        for (size_t j = parityPositions[i]; j < codeWord.size(); j++) {
            if (take) {
                paritySeq.push_back(codeWord[j]);
                takeCount--;
            } else {
                takeCount++;
            }

            if (takeCount == 0) {
                take = false;
            } else if (takeCount == pow(2, i)) {
                take = true;
            }
        }

        parityBits.push_back(parityFunc(paritySeq));
    }

    return parityBits;
}

int main() {
    string parity;
    cout << "Which parity do you need? (even,odd) => ";
    getline(cin, parity);
    parity = (parity == "") ? "even" : "odd";

    while (true) {
        cout << "\nTransmitter" << endl;

        string inputMessageStr;
        cout << "\nEnter message: ";
        getline(cin, inputMessageStr);
        vector<char> inputChars(inputMessageStr.begin(), inputMessageStr.end());

        vector<vector<int>> binReprLists;

        cout << "Data on transmitter side is: " << endl;
        for (char inputChar : inputChars) {
            int ascii = static_cast<int>(inputChar);
            vector<int> binRepr = decimalToBinary(ascii);
            binReprLists.push_back(binRepr);
            cout <<"\nInput Char: " <<inputChar << "\nAscii: " << ascii << "\nBinary: " << listToStr(binRepr) << endl;
            cout<<endl;
        }

        vector<vector<int>> codeWordLists;
        int numRBits = 0;

        cout << "Code words on transmitter side:" << endl;
        for (size_t i = 0; i < inputChars.size(); i++) {
            vector<int> binRepr = binReprLists[i];
            pair<vector<int>, int> encodedResult = encode(binRepr, parity);
            codeWordLists.push_back(encodedResult.first);
            numRBits = encodedResult.second;
            cout << inputChars[i] << ": " << listToStr(encodedResult.first) << endl;
            
            // Display parity bits at transmitter side
            cout << "Parity bits on transmitter side: ";
            for (int j = 0; j < numRBits; j++) {
                cout << encodedResult.first[pow(2, j) - 1] << " ";
            }
            cout << endl;
        }

        cout << "Number of redundant bits => r = " << numRBits << endl;
        cout << "Number of bits in message => m = " << codeWordLists[0].size() - numRBits << endl;

        cout << "\nTransmission Medium" << endl;

        string error;
        cout << "Do you wish to induce errors in the message? (no,yes) => ";
        getline(cin, error);

        if (error == "yes") {
            for (vector<int>& codeWord : codeWordLists) {
                int randomPosition = rand() % codeWord.size();
                codeWord[randomPosition] = (codeWord[randomPosition] == 1) ? 0 : 1;
                cout << "For code word " << listToStr(codeWord) << ", error induced at position=" << randomPosition << endl;
            }
        }

        cout << "\nReceiver" << endl;

        string decodedMessage = "";
        for (size_t i = 0; i < codeWordLists.size(); i++) {
            vector<int> codeWord = codeWordLists[i];
            string codeWordStr = listToStr(codeWord);
            vector<int> parityBits = decode(codeWord, numRBits, parity);

            // Display received parity bits at receiver side
            cout << "Received parity bits: ";
            for (int j = 0; j < numRBits; j++) {
                cout << parityBits[j] << " ";
            }
            cout << endl;

            if (accumulate(parityBits.begin(), parityBits.end(), 0) == 0) {
                vector<int> parityPositions;
                for (int j = 0; j < numRBits; j++) {
                    parityPositions.push_back(pow(2, j) - 1);
                }
                vector<int> charBinRepr;
                for (size_t pos = 0; pos < codeWord.size(); pos++) {
                    if (find(parityPositions.begin(), parityPositions.end(), static_cast<int>(pos)) == parityPositions.end()) {
                        charBinRepr.push_back(codeWord[pos]);
                    }
                }
                char decodedChar = static_cast<char>(binaryToDecimal(charBinRepr));
                cout << "Code " << codeWordStr << " received without any error."
                     << " Decoded character => " << decodedChar << endl;
                decodedMessage += decodedChar;
            } else {
                int errorPosition = binaryToDecimal(vector<int>(parityBits.rbegin(), parityBits.rend())) - 1;
                cout << "Code " << codeWordStr << " received with an error."
                     << " Error is at index=" << errorPosition << endl;
                codeWord[errorPosition] = (codeWord[errorPosition] == 1) ? 0 : 1;
                vector<int> parityPositions;
                for (int j = 0; j < numRBits; j++) {
                    parityPositions.push_back(pow(2, j) - 1);
                }
                vector<int> charBinRepr;
                for (size_t pos = 0; pos < codeWord.size(); pos++) {
                    if (find(parityPositions.begin(), parityPositions.end(), static_cast<int>(pos)) == parityPositions.end()) {
                        charBinRepr.push_back(codeWord[pos]);
                    }
                }
                char decodedChar = static_cast<char>(binaryToDecimal(charBinRepr));
                cout << "Corrected codeword => " << decodedChar << endl;
                decodedMessage += decodedChar;
            }
        }

        cout << "Message on receiver side => " << decodedMessage << endl;
    }

    return 0;
}