#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Job {
public:
    int job_id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int priority;

    Job(int job_id, int arrival_time, int burst_time, int priority)
        : job_id(job_id), arrival_time(arrival_time), burst_time(burst_time),
          remaining_time(burst_time), priority(priority) {}

    friend ostream& operator<<(ostream& os, const Job& job) {
        os << "Job " << job.job_id << ": Arrival Time=" << job.arrival_time
           << ", Burst Time=" << job.burst_time << ", Priority=" << job.priority;
        return os;
    }
};

class Scheduler {
public:
    vector<Job> queue;
    int time;
    float avg_waiting_time;
    int total_burst_time;

    Scheduler() : time(0), avg_waiting_time(0), total_burst_time(0) {}

    void add_job(const Job& job) {
        queue.push_back(job);
    }

    void fcfs() {
        sort(queue.begin(), queue.end(), [](const Job& a, const Job& b) {
            return a.arrival_time < b.arrival_time;
        });

        int total_waiting_time = 0;
        for (const auto& job : queue) {
            total_waiting_time += time - job.arrival_time;
            execute_job(job);
        }
        avg_waiting_time = static_cast<float>(total_waiting_time) / queue.size();
        calculate_total_burst_time();
    }

    void sjf_preemptive() {
        vector<Job> temp_queue = queue;
        sort(temp_queue.begin(), temp_queue.end(), [](const Job& a, const Job& b) {
            return a.arrival_time < b.arrival_time;
        });

        int total_waiting_time = 0;
        while (!temp_queue.empty()) {
            Job job = temp_queue.front();
            temp_queue.erase(temp_queue.begin());
            int waiting_time = time - job.arrival_time;
            total_waiting_time += waiting_time;
            execute_job(job);
        }
        avg_waiting_time = static_cast<float>(total_waiting_time) / queue.size();
        calculate_total_burst_time();
    }

    void priority_non_preemptive() {
        sort(queue.begin(), queue.end(), [](const Job& a, const Job& b) {
            return a.arrival_time < b.arrival_time;
        });

        int total_waiting_time = 0;
        for (const auto& job : queue) {
            total_waiting_time += time - job.arrival_time;
            execute_job(job);
        }
        avg_waiting_time = static_cast<float>(total_waiting_time) / queue.size();
        calculate_total_burst_time();
    }

    void round_robin_preemptive(int time_slice) {
        vector<Job> temp_queue = queue;
        int total_waiting_time = 0;

        while (!temp_queue.empty()) {
            Job job = temp_queue.front();
            temp_queue.erase(temp_queue.begin());
            int waiting_time = time - job.arrival_time;
            total_waiting_time += waiting_time;
            int time_executed = min(time_slice, job.remaining_time);
            job.remaining_time -= time_executed;
            time += time_executed;

            if (job.remaining_time > 0) {
                temp_queue.push_back(job);
            } else {
                print_job_completion(job);
            }
        }

        int num_completed_jobs = queue.size() - temp_queue.size();
        avg_waiting_time = static_cast<float>(total_waiting_time) / (num_completed_jobs > 0 ? num_completed_jobs : 1);
        calculate_total_burst_time();
    }

    void execute_job(const Job& job) {
        time = max(time, job.arrival_time);
        print_job_execution(job);
        time += job.burst_time;
    }

    void print_job_execution(const Job& job) {
        cout << "Time=" << time << ", Executing " << job << endl;
    }

    void print_job_completion(const Job& job) {
        cout << "Time=" << time << ", Job " << job.job_id << " completed!" << endl;
    }

    void calculate_total_burst_time() {
        total_burst_time = 0;
        for (const auto& job : queue) {
            total_burst_time += job.burst_time;
        }
    }
};

int main() {
    Job job1(1, 0, 8, 2);
    Job job2(2, 1, 4, 1);
    Job job3(3, 2, 9, 3);
    Job job4(4, 3, 5, 4);

    Scheduler scheduler;
    scheduler.add_job(job1);
    scheduler.add_job(job2);
    scheduler.add_job(job3);
    scheduler.add_job(job4);

    cout << "FCFS:" << endl;
    scheduler.fcfs();
    cout << "Average Waiting Time: " << scheduler.avg_waiting_time << endl;
    cout << "Total Burst Time: " << scheduler.total_burst_time << endl;

    cout << "\nSJF Preemptive:" << endl;
    scheduler.sjf_preemptive();
    cout << "Average Waiting Time: " << scheduler.avg_waiting_time << endl;
    cout << "Total Burst Time: " << scheduler.total_burst_time << endl;

    cout << "\nPriority Non-Preemptive:" << endl;
    scheduler.priority_non_preemptive();
    cout << "Average Waiting Time: " << scheduler.avg_waiting_time << endl;
    cout << "Total Burst Time: " << scheduler.total_burst_time << endl;

    cout << "\nRound Robin Preemptive:" << endl;
    scheduler.round_robin_preemptive(3);
    cout << "Average Waiting Time: " << scheduler.avg_waiting_time << endl;
    cout << "Total Burst Time: " << scheduler.total_burst_time << endl;

    return 0;
}
