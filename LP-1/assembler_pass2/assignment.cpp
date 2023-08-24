#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

int main() {
    ifstream sin("symbol_table.txt");
    ifstream lin("littab.txt");
    ifstream fin("ic.txt");
    ofstream fout("machineCode.txt");

    string line, word;
    vector<pair<string, int>> symtab;
    vector<pair<string, int>> littab;

    while (getline(sin, line)) {
        stringstream st(line);
        st >> word;
        string label = word;
        st >> word;
        symtab.push_back({label, stoi(word)});
    }
    sin.close();

    while (getline(lin, line)) {
        stringstream st(line);
        st >> word;
        string label = word;
        st >> word;
        littab.push_back({label, stoi(word)});
    }
    lin.close();

    int lc = -1;

    while (getline(fin, line)) {
        stringstream st(line);
        st >> word;
        string cls, mnemonic;
        cls = word.substr(1, 2);
        mnemonic = word.substr(4, 2);

        if (cls == "AD") {
            fout << " No Machine Code" << endl;

            if (mnemonic == "01") {
                st >> word;
                word = word.substr(3, word.length() - 4);
                lc = stoi(word);
            } else if (mnemonic == "03") {
                st >> word;
                word = word.substr(4, 1);
                int ind = stoi(word) - 1;
                lc = symtab[ind].second;
            }
        } else if (cls == "IS") {
            fout << lc << " " << mnemonic << " ";
            lc++;
            
            if (mnemonic == "00") { // Stop
                fout << "0 000" << endl;
                continue;
            }
            
            st >> word;
            
            if (word[1] != 'S' && word[1] != 'L') {
                word = word.substr(1, 1);
                fout << word << " ";
                st >> word;
            } else {
                fout << "0 ";
            }

            int num = stoi(word.substr(3, 2)) - 1;
            
            if (word[1] == 'S') {
                fout << symtab[num].second << endl;
            } else if (word[1] == 'L') {
                fout << littab[num].second << endl;
            }
        } else if (cls == "DL") {
            fout << lc << " ";
            lc++;
            
            if (mnemonic == "01") {
                fout << "00 0 ";
                st >> word;
                fout << "00" << word.substr(3, 1) << endl;
            } else if (mnemonic == "02") {
                fout << "No Machine Code" << endl;
            }
        }
    }
    
    fout.close();
    fin.close();
    cout << "\nProgram Executed\n";

    return 0;
}
