#include<iostream>
#include<queue>
#include<unordered_set>
#include<unordered_map>
using namespace std;

int LRU(string pages, int frames){
    unordered_set<char> s;
    unordered_map<char, int> indexes;
    int page_faults = 0;
    int page_hits = 0;
    for (int i = 0; i < pages.size(); i++){
        
    }
    return page_faults;
}

int pageFaultsFIFO(string pages, int frames) {
    queue<char> q;
    unordered_set<char> s;
    int page_faults = 0;
    int page_hits = 0;
    for (char page : pages) {
        if (s.find(page) == s.end()) {
            if (q.size() == frames) {
                s.erase(q.front());
                q.pop();
            }
            q.push(page);
            s.insert(page);
            page_faults++;
        } else {
            page_hits++;
        }
        for (char ele: s){
            cout << ele << ",";
        }
        cout<<'\n';
    }
    cout << "Page Faults using FIFO: " << page_faults << endl;
    cout << "Page Hits using FIFO: " << page_hits << endl;
    return page_faults;
}

int main() {
    string pages;
    int frames;
    cout << "Enter number of page references: ";
    int n;
    cin >> n;
    cout << "Enter page references: ";
    cin >> pages;
    cout << "Enter number of frames: ";
    cin >> frames;
    int choice;
    cout<<"Enter 1 for FIFO, 2 for LRU: \n";
    cin>>choice;
    switch (choice)
    {
    case 1:
        pageFaultsFIFO(pages, frames);
        break;
    case 2:
        LRU(pages, frames);
        break;
    default:
        break;
    }
    return 0;
}