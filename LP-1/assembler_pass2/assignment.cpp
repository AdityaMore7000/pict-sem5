#include <bits/stdc++.h>
#include<string.h>
using namespace std;

int main()
{

    ifstream sin;
    sin.open("symbol_table.txt");

    ifstream lin;
    lin.open("littab.txt");

    ifstream fin;
    fin.open("ic.txt");

    ofstream fout;
    fout.open("machineCode.txt");

    string line, word;

    vector<pair<string, int>> symtab;
    while (getline(sin, line))
    {
        stringstream st(line);
        st >> word;
        string label = word;
        st >> word;
        symtab.push_back({label, stoi(word)});
    }
    sin.close();

    vector<pair<string, int>> littab;
    while (getline(lin, line))
    {
        stringstream st(line);
        st >> word;
        string label = word;
        st >> word;
        littab.push_back({label, stoi(word)});
    }
    lin.close();

    int lc = -1;

    while (getline(fin, line))
    {
        // cout << "\nIn getline\n";
        stringstream st(line);
        st >> word;
        string cls, mnemonic;
        cls = word.substr(1, 2);
        mnemonic = word.substr(4, 2);

        if (cls == "AD")
        {
            fout << " No Machine Code" << endl;

            if (mnemonic == "01")
            {
                st >> word;
                word = word.substr(3, word.length() - 4);
                lc = stoi(word);
            }
            else if (mnemonic == "03")
            {
                st >> word;
                // cout << word << endl;
                word = word.substr(4, 1);
                int ind = stoi(word);
                ind--;
                lc = symtab[ind].second;
                // cout << lc << endl;
            }
        }
        else if (cls == "IS")
        {
            fout << lc << " " << mnemonic << " ";
            lc++;
            if (mnemonic == "00") //stop
            {
                fout << "0 000" << endl;
                continue;
            }
            st >> word;
            if (word[1] != 'S' && word[1] != 'L')
            {
                word = word.substr(1, 1);
                fout << word << " ";
                st >> word;
            }
            else
            {
                fout << "0 ";
            }

            string temp = word.substr(3, 2);
            int num = stoi(temp);
            num--;
            if (word[1] == 'S')
            {
                fout << symtab[num].second << endl;
            }
            else if (word[1] == 'L')
            {
                fout << littab[num].second << endl;
            }
        }
        else if (cls == "DL")
        {
            fout << lc << " ";
            lc++;
            if (mnemonic == "01")
            {
                fout << "00 0 ";
                st >> word;
                word = word.substr(3, 1);
                fout << "00" << word << endl;
            }
            else if (mnemonic == "02")
            {
                fout << "No Machine Code" << endl;
            }
        }
    }
    fout.close();
    fin.close();
    cout << "\nProgram Executed\n";

    return 0;
}