#include<iostream>
using namespace std;

// Structure to represent a process
struct Process {  
    int arrival_time;   // Arrival time of the process
    int burst_time;     // Burst time (execution time) of the process
    int waiting_time;   // Waiting time of the process
};  

// Comparison function used by qsort to sort processes based on burst time
int compare(const void *a, const void *b) {  
    struct Process *p1 = (struct Process *)a;  
    struct Process *p2 = (struct Process *)b;  
    return p1->burst_time - p2->burst_time;  // Compare based on burst time
}  

int main() {  
    int n, i, j;  
    float avg_waiting_time = 0, avg_turnaround_time = 0;  

    // Input the number of processes
    printf("Enter the number of processes: ");  
    scanf("%d", &n);  

    struct Process processes[n];  // Array to hold the processes

    // Input arrival time and burst time for each process
    for (i = 0; i < n; i++) {  
        printf("Enter arrival time and burst time of process %d: ", i+1);  
        scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);  
    }  

    // Sort processes based on burst time
    qsort(processes, n, sizeof(struct Process), compare);  

    // Calculate waiting time for each process
    processes[0].waiting_time = 0;  
    for (i = 1; i < n; i++) {  
        processes[i].waiting_time = 0;  
        for (j = 0; j < i; j++) {  
            processes[i].waiting_time += processes[j].burst_time;  
        }  
        avg_waiting_time += processes[i].waiting_time;  
    }  

    avg_waiting_time /= n;  // Calculate average waiting time

    // Calculate turnaround time for each process and total average turnaround time
    for (i = 0; i < n; i++) {  
        avg_turnaround_time += processes[i].burst_time + processes[i].waiting_time;  
    }  

    avg_turnaround_time /= n;  // Calculate average turnaround time

    // Output the results
    printf("\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");  
    for (i = 0; i < n; i++) {  
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i+1, processes[i].arrival_time, processes[i].burst_time, processes[i].waiting_time, processes[i].burst_time + processes[i].waiting_time);  
    }  

    // Output the average waiting time and average turnaround time
    printf("\nAverage Waiting Time: %f\n", avg_waiting_time);  
    printf("Average Turnaround Time: %f\n", avg_turnaround_time);  

    return 0;   
}  
