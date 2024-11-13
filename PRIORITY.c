#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int priority;
    int remaining_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
};

void priority_scheduling(struct Process processes[], int n, bool preemptive) {
    int completed = 0, current_time = 0;
    bool is_completed[n];
    for (int i = 0; i < n; i++) {
        processes[i].remaining_time = processes[i].burst_time;
        is_completed[i] = false;
    }

    while (completed != n) {
        int idx = -1;
        int highest_priority = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && !is_completed[i]) {
                if (processes[i].priority < highest_priority) {
                    highest_priority = processes[i].priority;
                    idx = i;
                } else if (processes[i].priority == highest_priority) {
                    if (processes[i].arrival_time < processes[idx].arrival_time) {
                        idx = i;
                    }
                }
            }
        }

        if (idx != -1) {
            if (preemptive) {
                processes[idx].remaining_time--;
                current_time++;
                if (processes[idx].remaining_time == 0) {
                    processes[idx].completion_time = current_time;
                    processes[idx].turnaround_time = processes[idx].completion_time - processes[idx].arrival_time;
                    processes[idx].waiting_time = processes[idx].turnaround_time - processes[idx].burst_time;
                    is_completed[idx] = true;
                    completed++;
                }
            } else {
                current_time += processes[idx].burst_time;
                processes[idx].completion_time = current_time;
                processes[idx].turnaround_time = processes[idx].completion_time - processes[idx].arrival_time;
                processes[idx].waiting_time = processes[idx].turnaround_time - processes[idx].burst_time;
                is_completed[idx] = true;
                completed++;
            }
        } else {
            current_time++;
        }
    }
}

void print_results(struct Process processes[], int n) {
    printf("PID\tAT\tBT\tPRI\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", processes[i].pid, processes[i].arrival_time, processes[i].burst_time,
               processes[i].priority, processes[i].completion_time, processes[i].turnaround_time, processes[i].waiting_time);
    }
}

int main() {
    struct Process processes[] = {{1, 0, 7, 2}, {2, 2, 4, 1}, {3, 4, 1, 3}, {4, 5, 4, 2}};
    int n = sizeof(processes) / sizeof(processes[0]);

    printf("Priority Scheduling (Non-Preemptive):\n");
    priority_scheduling(processes, n, false);
    print_results(processes, n);

    printf("\nPriority Scheduling (Preemptive):\n");
    priority_scheduling(processes, n, true);
    print_results(processes, n);

    return 0;
}
