#include<iostream>
using namespace std;
class Job{
    int wt,at,bt,ct,tat,id;
    string name;
    public:
    Job(){
        cout<<"Enter process name:\n";
        cin>>this->name;
        cout<<"Enter process ID:\n";
        cin>>this->id;
        // cout<<"Enter process arrival time:\n";
        // cin>>this->at;
        this->at = 0;
        cout<<"Enter burst time:\n";
        cin>>this->bt;
        
    }
};
int main(){
    cout<<"Hello world\n";
    return 0;
}