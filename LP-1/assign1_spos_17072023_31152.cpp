#include <bits/stdc++.h>
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
  int averageWaitingTime, totalExecutionTime, totalWaitingTime,totalBurstTime;

public:
  JobScheduler(int);
  void sort();
  void show();
  void FCFS();
  void SJF();
  void PBS();
  void RR();
};
JobScheduler::JobScheduler(int np) {
  this->averageWaitingTime = this->totalExecutionTime = this->totalWaitingTime = this->totalBurstTime=
      0;
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
    this->totalBurstTime += rq[i].bt;
  }
  sort();
}
void JobScheduler::FCFS() {
  for (int i = 0; i < np; i++) {
    totalExecutionTime +=rq[i].bt;
     rq[i].ct = totalExecutionTime;
    rq[i].tat = rq[i].ct-rq[i].at;
    rq[i].wt = rq[i].tat - rq[i].bt;
    this->totalWaitingTime +=rq[i].wt;
  }
}
void JobScheduler::PBS(){
  cout<<"PBS\n";
  return;
}
void JobScheduler::SJF(){
  int time = 0;
  sort();
  return;
}
void JobScheduler::RR(){
  cout<<"RR\n";
  return;
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
    cout << "ID: " << rq[i].id << '\t';
    cout << "Name: " << rq[i].name << '\t';
    cout << "AT: " << rq[i].at << '\t';
    cout << "BT: " << rq[i].bt << '\t';
    cout << "CT: " << rq[i].ct << '\t';
    cout << "TAT: " << rq[i].tat << '\t';
    cout << "WT: " << rq[i].wt << '\t';
    float f;
    f = float(this->totalWaitingTime)/np;
    cout << '\n';
  }
}

int main() {
  int choice;
  cout << "Enter number of jobs:\n";
  int n;
  cin >> n;
  JobScheduler js(n);
  cout << "Press 1 for First come first serve(non-preemptive)\n";
  cout << "Press 2 for Shortest Job First(non-preemptive)\n";
  cout << "Press 3 for Priority based Scheduling(non-preemptive)\n";
  cout << "Press 4 for Round Robin(preemptive)\n";
  cout << "Enter choice:\n";
  cin >> choice;
  switch (choice) {
  case 1: {
    js.FCFS();
    js.show();
    break;
  }
  case 2: {
    js.SJF();
    break;
  }
  case 3: {
    js.PBS();
    break;
  }
  case 4: {
    js.RR();
    break;
  }
  }
  return 0;
}