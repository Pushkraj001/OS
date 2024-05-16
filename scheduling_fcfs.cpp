#include<iostream>
using namespace std;

// Function to find the waiting time for all processes
void findWaitingTime(int processes[], int n, int bt[], int wt[], int at[]) {
    int service_time[n];
    service_time[0] = at[0]; // Service time for first process is its arrival time
    wt[0] = 0; // Waiting time for first process is 0

    // calculating waiting time
    for (int i = 1; i < n; i++) {
        // Calculating service time for each process
        service_time[i] = service_time[i - 1] + bt[i - 1];
        
        // If the current process hasn't arrived yet, wait until it arrives
        if (service_time[i] < at[i])
            service_time[i] = at[i];
        
        // Calculate waiting time
        wt[i] = service_time[i] - at[i];
        
        // If waiting time is negative, make it 0
        if (wt[i] < 0)
            wt[i] = 0;
    }
}

// Function to calculate turn around time
void findTurnAroundTime(int processes[], int n, int bt[], int wt[], int tat[]) {
    // calculating turnaround time by adding bt[i] + wt[i]
    for (int i = 0; i < n; i++)
        tat[i] = bt[i] + wt[i];
}

// Function to calculate average time
void findavgTime(int processes[], int n, int bt[], int at[]) {
    int wt[n], tat[n], total_wt = 0, total_tat = 0;

    // Function to find waiting time of all processes
    findWaitingTime(processes, n, bt, wt, at);

    // Function to find turn around time for all processes
    findTurnAroundTime(processes, n, bt, wt, tat);

    // Display processes along with all details
    cout << "Processes " << " Arrival time " << " Burst time "
        << " Waiting time " << " Turn around time\n";

    // Calculate total waiting time and total turn around time
    for (int i = 0; i < n; i++) {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
        cout << " " << processes[i] << "\t\t" << at[i] << "\t\t"
            << bt[i] << "\t " << wt[i] << "\t\t " << tat[i] << endl;
    }

    // Calculate and display average waiting time and average turn around time
    cout << "Average waiting time = "
        << (float)total_wt / (float)n;
    cout << "\nAverage turn around time = "
        << (float)total_tat / (float)n;
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    int processes[n]; // Array to store process IDs
    int arrival_time[n]; // Array to store arrival times
    int burst_time[n]; // Array to store burst times
    
    // Input arrival times for each process
    cout << "Enter arrival time for each process:\n";
    for (int i = 0; i < n; i++) {
        cout << "Arrival time of process " << i + 1 << ": ";
        cin >> arrival_time[i];
        processes[i] = i + 1; // Assigning process IDs
    }

    // Input burst times for each process
    cout << "Enter burst time for each process:\n";
    for (int i = 0; i < n; i++) {
        cout << "Burst time for process " << i + 1 << ": ";
        cin >> burst_time[i];
    }

    // Calculate and display average waiting time and average turn around time
    findavgTime(processes, n, burst_time, arrival_time);
    return 0;
}
