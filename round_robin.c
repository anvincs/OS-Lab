#include <stdio.h>
#include <stdlib.h>
#define SIZE 10
#define TIME_QUANTUM 6

struct process {
    int pid;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int turnaround_time;
};

int queue[SIZE];
int front=-1 , rear=-1;
int added[SIZE] = {0};

int isFull() {
    if((rear+1)%SIZE == front) {
        return 1;
    }
    return 0;
}

void enqueue(int val) {
    if(isFull()) {
        return;
    }
    if(rear==-1) {
        rear = 0;
        front = 0;
        queue[rear] = val;
        return;
    }
    rear = (rear+1)%SIZE;
    queue[rear]  = val;
}

int dequeue() {
    if(front == -1) {
        return -1;
    }
    int val = queue[front];
    if(front == rear) {
        front = -1;
        rear = -1;
    }
    else {
        front = (front+1)%SIZE;
    }
    return val;
}

void RR(struct  process *procs , int n) {
    int current_time = -1;
    int current_process;
    int completed = 0;

    printf("\nRR Gantt Chart:\n");
    printf("0");

    while(completed < n) {
        current_process = dequeue();

        if(current_process == -1) {
            current_time++;
            if(current_time>0) {
            printf("| - | %d", current_time);
            }
            for (int i = 0; i < n; i++)
            {
                if(procs[i].arrival_time <= current_time && procs[i].burst_time > 0) {
                    enqueue(i);
                    added[i] = 1;
                }
            }
            
        }

        else {
            added[current_process] = 0;
            if(procs[current_process].burst_time <= TIME_QUANTUM) {
                current_time += procs[current_process].burst_time;
                procs[current_process].burst_time = 0;
                completed++;
                added[current_process] = 1;
                printf(" | P%d | %d", procs[current_process].pid, current_time);
            }
            else {
                current_time += TIME_QUANTUM;
                procs[current_process].burst_time -= TIME_QUANTUM;
                printf(" | P%d | %d", procs[current_process].pid, current_time);
            }
            for(int i=0;i<n;i++) {
                int lowest_arrival_time = 999999;
                int enqueue_proc = -1;
                for(int j=0;j<n;j++) {
                    if(j==current_process) {
                        continue;
                    }
                    if(added[j] != 1 && procs[j].arrival_time <= current_time && procs[j].burst_time > 0) {
                        if(procs[j].arrival_time < lowest_arrival_time) {
                            lowest_arrival_time = procs[j].arrival_time;
                            enqueue_proc = j;
                        }
                    }
                }
                if(enqueue_proc != -1) {
                    enqueue(enqueue_proc);
                    added[enqueue_proc] = 1;
                }
            }

            if(procs[current_process].burst_time > 0) {
                enqueue(current_process);
                added[current_process] = 1;
            }
        }
    }
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct process *procs = malloc(n * sizeof(struct process));
    for (int i = 0; i < n; i++) {
        printf("Enter the arrival time and burst time for process %d: ", i+1);
        scanf("%d %d", &procs[i].arrival_time, &procs[i].burst_time);
        procs[i].pid = i+1;
        procs[i].waiting_time = 0;
        procs[i].turnaround_time = 0;
    }

    RR(procs , n);
    printf("\n");

    return 0;
}