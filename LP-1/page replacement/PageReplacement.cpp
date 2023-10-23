#include<bits/stdc++.h>
using namespace std;

int Optimal(string pages, int frames) {
    vector<int> next(pages.size(), -1);
    for (int i = pages.size() - 2; i >= 0; i--) {
        next[i] = next[i + 1];
        for (int j = i + 1; j < pages.size(); j++) {
            if (pages[j] == pages[i]) {
                next[i] = j;
                break;
            }
        }
    }
    unordered_set<char> s;
    unordered_map<char, int> idx;
    int page_faults = 0;
    for (int i = 0; i < pages.size(); i++) {
        if (s.size() < frames) {
            if (s.find(pages[i]) == s.end()) {
                s.insert(pages[i]);
                page_faults++;
            }
            idx[pages[i]] = i;
        } else {
            if (s.find(pages[i]) == s.end()) {
                int farthest = -1, victim;
                for (auto it = s.begin(); it != s.end(); it++) {
                    if (next[idx[*it]] > farthest) {
                        farthest = next[idx[*it]];
                        victim = *it;
                    }
                }
                s.erase(victim);
                s.insert(pages[i]);
                page_faults++;
            }
            idx[pages[i]] = i;
        }
        if(i!= pages.size()-1){
        cout << "Frames: ";
        for (auto it = s.begin(); it != s.end(); it++) {
            cout << *it << " ";
        }
        cout << "Page Faults: " << page_faults << endl;
        }
    }
    cout<<"Page Faults using Optimal: "<<page_faults-1<<endl;
    cout<<"Page Hits using Optimal: "<<pages.size()-page_faults+1<<endl;
    return page_faults;
}

int LRU(string pages, int frames){

    bool no_increment = false;
    int page_faults = 0;
    int page_hits = 0;
    vector<int> frame(frames, -1);
    unordered_map<int, int> index;
    int n = pages.size();
    for(int i = 0; i < n; i++){
        int page = pages[i] - '0';
        if(index.find(page) == index.end()){
            if(frame[frames-1] != -1){
                index.erase(frame[frames-1]);
            }
            for(int j = frames-2; j >= 0; j--){
                frame[j+1] = frame[j];
            }
            frame[0] = page;
            index[page] = 0;
            page_faults++;
            no_increment = false;
        }
        else{
            page_hits++;
            no_increment = true;
            // int pos = index[page];
            // for(int j = pos; j >= 1; j--){
            //     frame[j] = frame[j-1];
            //     index[frame[j]] = j;
            // }
            // frame[0] = page;
            // index[page] = 0;
        }
        cout << "Frames: ";
        for(int j = 0; j < frames; j++){
            if(frame[j] == -1){
                cout << " ";
            }
            else{
                cout << frame[j]<<" ";
            }
        }
        if(no_increment){
            cout << "Page Hit"<< endl;
        }
        else{
            cout << "Page Faults: " << page_faults << endl;
        }
        // cout <<" Page Faults: " << page_faults << endl;
    }
    cout << "Page Faults using LRU: " << page_faults << endl;
    cout << "Page Hits using LRU: " << page_hits << endl;
    return page_faults;
}

int pageFaultsFIFO(string pages, int frames) {
    queue<char> q;
    unordered_set<char> s;
    bool no_increment = false;
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
            no_increment = false;
        } else {
            page_hits++;
            no_increment = true;
        }
        queue<char> Q = q;
        cout<<"Frames: ";
        while (!Q.empty()) {
            cout << Q.front() << " ";
            Q.pop();
        }
        if(no_increment){
            cout << "Page Hit"<< endl;
        }
        else{
            cout << "Page Faults: " << page_faults << endl;
        }

        // cout << "Page Faults: " << page_faults << endl;
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
    while(1){
    cout<<"Enter 1 for FIFO, 2 for LRU, 3 for Optimal, 0 to Exit: \n";
    cin>>choice;
    switch (choice)
    {
    case 0:
        exit(0);
        break;
    case 1:
        pageFaultsFIFO(pages, frames);
        break;
    case 2:
        LRU(pages, frames);
        break;
    case 3:
        Optimal(pages, frames);
        break;
    default:
        break;
    }
}
    return 0;
}