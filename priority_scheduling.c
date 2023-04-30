#include <stdio.h>
#include <stdlib.h>
struct process {
    int pid;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int turnaround_time;
    int priority;
};

void priorityschedule(struct process *procs, int n) {
    int current_time = 0;
    int completed = 0;
    printf("Priority Scheduling Gantt Chart:\n");
    printf("%d", current_time);
    while (completed < n) {
        int next_proc = -1;
        int largest_priority = -999999;
        for (int i = 0; i < n; i++) {
            if (procs[i].arrival_time <= current_time && procs[i].priority > largest_priority && procs[i].turnaround_time == 0) {
                largest_priority = procs[i].priority;
                next_proc = i;
            }
        }
        if (next_proc == -1) {
            current_time++;
        } else {
            current_time += procs[next_proc].burst_time;
            printf(" | P%d | %d", procs[next_proc].pid, current_time);
            procs[next_proc].waiting_time = current_time - procs[next_proc].arrival_time - procs[next_proc].burst_time;
            if (procs[next_proc].waiting_time < 0) {
                procs[next_proc].waiting_time = 0;
            }
            procs[next_proc].turnaround_time = procs[next_proc].burst_time + procs[next_proc].waiting_time;
            completed++;
        }
    }
    printf("\n");
    int total_waiting_time_prschedule = 0;
    int total_turnaround_time_prschedule = 0;
    for (int i = 0; i < n; i++) {
        total_waiting_time_prschedule += procs[i].waiting_time;
        total_turnaround_time_prschedule += procs[i].turnaround_time;
    }
float avg_waiting_time_prschedule = (float)total_waiting_time_prschedule / (float)n;
float avg_turnaround_time_prschedule = (float)total_turnaround_time_prschedule / (float)n;
printf("\nAverage Waiting time: %f", avg_waiting_time_prschedule);
printf("\nAverage Turnaround time: %f\n", avg_turnaround_time_prschedule);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct process *procs = malloc(n * sizeof(struct process));
    for (int i = 0; i < n; i++) {
        printf("Enter the arrival time , burst time and priority for process %d: ", i+1);
        scanf("%d %d %d", &procs[i].arrival_time, &procs[i].burst_time, &procs[i].priority);
        procs[i].pid = i+1;
        procs[i].waiting_time = 0;
        procs[i].turnaround_time = 0;
    }

    priorityschedule(procs,n);

    return 0;
}