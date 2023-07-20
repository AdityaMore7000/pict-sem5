#include <iostream>
using namespace std;
class Job {
  int wt, at, bt, ct, tat, id;
  string name;

public:
  Job();
  void setData();
  friend class JobScheduler;
};
Job::Job() {
  this->wt = this->at = this->bt = this->ct = this->tat = 0;
  this->id = -1;
  this->name = "";
}
class JobScheduler {
  Job *rq;
  int np;
  int averageWaitingTime, totalExecutionTime;

public:
  JobScheduler(int);
  void sort();
  void show();
void FCFS();
};
JobScheduler::JobScheduler(int np) {
  this->averageWaitingTime = this->totalExecutionTime = 0;
  this->np = np;
  rq = new Job[np];
  for (int i = 0; i < np; i++) {
    cout << "Enter for job" << (i + 1) << '\n';
    cout << "Enter name:\n";
    cin >> rq[i].name;
    cout << "Enter ID:\n";
    cin >> rq[i].id;
    cout << "Enter arrival time:\n";
    cin >> rq[i].at;
    cout << "Enter burst time:\n";
    cin >> rq[i].bt;
    
  }
  sort();
  FCFS();
}
void JobScheduler::FCFS(){
  for(int i = 0;i<np;i++){ 
  rq[i].wt = totalExecutionTime - rq[i].at;
    this->totalExecutionTime += rq[i].bt;
    rq[i].ct = this->totalExecutionTime;
    rq[i].tat = rq[i].ct - rq[i].at;
  }
}
void JobScheduler::sort() {
  for (int i = 0; i < np - 1; i++) {
    int min = i;
    for (int j = i + 1; j < np; j++) {
      if (rq[j].at < rq[min].at)
        min = j;
    }
      if (min != i)
        swap(rq[min], rq[i]);
  }
}
void JobScheduler::show() {
  for (int i = 0; i < np; i++) {
    cout << "Process: " << i + 1 << "\n\n";
    cout <<"ID: "<< rq[i].id << '\t';
    cout <<"Name: "<< rq[i].name << '\t';
    cout <<"AT: "<< rq[i].at << '\t';
    cout <<"BT: "<< rq[i].bt << '\t';
    cout <<"CT: "<< rq[i].ct << '\t';
    cout <<"TAT: "<< rq[i].tat << '\t';
    cout <<"WT: "<< rq[i].wt << '\t';
    cout<<'\n';
  }
}

int main() {
  cout << "Hello world\n";
  JobScheduler js(5);
  js.show();
  return 0;
}