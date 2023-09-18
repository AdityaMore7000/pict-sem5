#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <array>
#include <map>
using namespace std;

int main() {
    ifstream fin;
    fin.open("source2.txt");

    ofstream fout;
    fout.open("output.txt");

    ofstream mntout;
    mntout.open("mnt.txt");

    ofstream mdtout;
    mdtout.open("mdt.txt");

    ofstream pntout;
    pntout.open("pnt.txt");

    ofstream kpdout;
    kpdout.open("kpd.txt");

    string line, word;
    int p = 1;
    bool started = false;
    bool macrostart = false;

    vector<array<string, 5>> mnttab;
    vector<pair<string, string>> kpdtab;
    map<string, int> pnttab;

    while (getline(fin, line)) {
        stringstream st(line);
        st >> word;

        if (started) {
            if (word != "END") {
                fout << word << " ";
                while (st >> word) {
                    fout << word << " ";
                }
                fout << endl;
            }
        } else if (macrostart) {
            // Process macro definition
            array<string, 5> a;
            mnttab.push_back(a);
            int i = mnttab.size() - 1;
            mnttab[i][0] = word;
            mnttab[i][3] = to_string(p);
            int pp = 0;
            int kp = 0;
            pntout << "---------PNTAB FOR " << word << " MACRO-------\n";
            while (st >> word) {
                if (word[word.length() - 1] == ',') {
                    word = word.substr(0, word.length() - 1);
                }
                int equalindex = word.find('=');
                if (equalindex == string::npos) {
                    pp++;
                    pnttab[word] = pnttab.size() + 1;
                    pntout << pnttab[word] << ". " << word << endl;
                } else {
                    kp++;
                    string beforeequal = word.substr(0, equalindex);
                    string afterequal = word.substr(equalindex + 1);
                    kpdtab.push_back({beforeequal, afterequal});
                    pnttab[beforeequal] = pnttab.size() + 1;
                    pntout << pnttab[beforeequal] << ". " << beforeequal << endl;
                }
            }
            mnttab[i][1] = to_string(pp);
            mnttab[i][2] = to_string(kp);
            if (kp != 0) {
                mnttab[i][4] = to_string(kpdtab.size() - kp + 1);
            } else {
                mnttab[i][4] = '-';
            }
            macrostart = false;
        } else if (word == "MEND") {
            // End of macro definition
            mdtout << "MEND" << endl;
            pnttab.clear();
        } else if (word == "START") {
            // Start processing code
            started = true;
        } else {
            // Process code within macros
            mdtout << word << " ";
            while (st >> word) {
                if (word[0] == '&') {
                    word = word.substr(1);
                    if (word[word.size() - 1] == ',') {
                        word = word.substr(0, word.size() - 1);
                    }
                    mdtout << "(P," << pnttab[word] << "), ";
                } else {
                    if (word[word.size() - 1] == ',') {
                        word = word.substr(0, word.size() - 1);
                    }
                    mdtout << word << " ";
                }
            }
            mdtout << endl;
        }
        p++;
    }

    fin.close();

    // Write MNT and KPD tables to their respective output files
    for (int i = 0; i < mnttab.size(); i++) {
        for (int j = 0; j < 5; j++) {
            mntout << mnttab[i][j] << " ";
        }
        mntout << endl;
    }

    for (auto i : kpdtab) {
        kpdout << i.first << " " << i.second << endl;
    }

    // Close output files
    fout.close();
    mntout.close();
    mdtout.close();
    pntout.close();
    kpdout.close();

    cout << "Program Executed\n";
    return 0;
}
