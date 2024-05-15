#include<iostream>
using namespace std;

struct Process {  
int arrival_time;  
int burst_time;  
int waiting_time;  
};  
  
int compare(const void *a, const void *b) {  
struct Process *p1 = (struct Process *)a;  
struct Process *p2 = (struct Process *)b;  
return p1->burst_time - p2->burst_time;  
}  
  
int main() {  
int n, i, j;  
float avg_waiting_time = 0, avg_turnaround_time = 0;  
printf("Enter the number of processes: ");  
scanf("%d", &n);  
struct Process processes[n];  
for (i = 0; i< n; i++) {  
printf("Enter arrival time and burst time of process %d: ", i+1);  
scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);  
}  
qsort(processes, n, sizeof(struct Process), compare);  
processes[0].waiting_time = 0;  
for (i = 1; i< n; i++) {  
processes[i].waiting_time = 0;  
for (j = 0; j <i; j++)   
{   
  
processes[i].waiting_time += processes[j].burst_time;   
  
}   
  
avg_waiting_time += processes[i].waiting_time;   
  
}   
  
avg_waiting_time /= n;   
  
for (i = 0; i< n; i++) {   
  
avg_turnaround_time += processes[i].burst_time + processes[i].waiting_time;   
  
}   
  
avg_turnaround_time /= n;   
  
printf("\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");   
  
for (i = 0; i< n; i++) {   
  
printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i+1, processes[i].arrival_time, processes[i].burst_time, processes[i].waiting_time, processes[i].burst_time+processes[i].waiting_time);   
  
}   
  
printf("\nAverage Waiting Time: %f\n", avg_waiting_time);   
  
printf("Average Turnaround Time: %f\n", avg_turnaround_time);   
  
return 0;   
  
}
