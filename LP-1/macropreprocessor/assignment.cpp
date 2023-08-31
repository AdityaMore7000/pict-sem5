#include <bits/stdc++.h>
using namespace std;
int main()
{
    vector<vector<string>> table;
    vector<string> row;

    fstream file;
    file.open("ic.txt", ios::in);
    if (!file)
    {
        cout << "Error in opening file..";
        return 0;
    }
    string word;
    string temp;
    while(getline(file, word))
    {
    int j = 0;
    int i = 0;
    for (; i < word.length(); i++)
    {
        if (word[i] == ' '||word[i]==',')
        {
            cout << word.substr(j, i) << ' ';
            j = i + 1;
        }
    }
    cout << word.substr(j, i) << ' ';
    j = 0;
    cout<<'\n';
    }
    cout << "Program executed successfully...\n";
    return 0;
}
