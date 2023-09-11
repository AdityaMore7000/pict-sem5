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
    while(getline(file, word))
    {
   int k = 0;
    int count = 0;
    for(int i = 0;i<word.length();i++)
    {
        count++;
        if(word[i]==' ')
        {
            row.push_back(word.substr(k,count-1));
            k = i+1;
            count = 0;
        }
    }
    table.push_back(row);
    row.clear();
    }
    for(auto i:table){
        for(auto j:i){
            cout << j << " ";
        }
        cout << endl;
    }
    cout << "Program executed successfully...\n";
    return 0;
}
