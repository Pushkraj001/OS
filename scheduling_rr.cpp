#include <iostream>
#include <climits>
using namespace std;

// Structure to represent a process
struct Process {
    int AT, BT, ST[20], WT, FT, TAT, pos; // Arrival Time, Burst Time, Start Time array, Waiting Time, Final Time, Turnaround Time, Position
};

int quant; // Quantum

int main() {
    int n, i, j;

    // Taking input for the number of processes
    cout << "Enter the number of processes: ";
    cin >> n;
    Process p[n]; // Array of processes

    // Taking input for the quantum
    cout << "Enter the quantum: " << endl;
    cin >> quant;

    // Taking input for the process numbers
    cout << "Enter the process numbers: " << endl;
    for (i = 0; i < n; i++)
        cin >> p[i].pos;

    // Taking input for arrival time of processes
    cout << "Enter the Arrival time of processes: " << endl;
    for (i = 0; i < n; i++)
        cin >> p[i].AT;

    // Taking input for burst time of processes
    cout << "Enter the Burst time of processes: " << endl;
    for (i = 0; i < n; i++)
        cin >> p[i].BT;

    // Initializing variables
    int c = n, s[n][20];
    float time = 0, mini = INT_MAX, b[n], a[n];

    // Initializing burst and arrival time arrays
    int index = -1;
    for (i = 0; i < n; i++) {
        b[i] = p[i].BT;
        a[i] = p[i].AT;
        for (j = 0; j < 20; j++) {
            s[i][j] = -1; // Initializing Start Time array
        }
    }

    int tot_wt, tot_tat;
    tot_wt = 0;
    tot_tat = 0;
    bool flag = false;

    // Round Robin algorithm implementation
    while (c != 0) {
        mini = INT_MAX;
        flag = false;

        // Finding the process with the minimum arrival time that hasn't been executed yet
        for (i = 0; i < n; i++) {
            float p = time + 0.1;
            if (a[i] <= p && mini > a[i] && b[i] > 0) {
                index = i;
                mini = a[i];
                flag = true;
            }
        }

        // If no process is ready to execute, increment time and continue
        if (!flag) {
            time++;
            continue;
        }

        // Calculating start time
        j = 0;
        while (s[index][j] != -1) {
            j++;
        }

        if (s[index][j] == -1) {
            s[index][j] = time;
            p[index].ST[j] = time;
        }

        // Executing the process for the quantum or until it finishes
        if (b[index] <= quant) {
            time += b[index];
            b[index] = 0;
        } else {
            time += quant;
            b[index] -= quant;
        }

        // Updating arrival time if process is not finished
        if (b[index] > 0) {
            a[index] = time + 0.1;
        }

        // Calculating arrival, burst, final times and updating counters
        if (b[index] == 0) {
            c--;
            p[index].FT = time;
            p[index].WT = p[index].FT - p[index].AT - p[index].BT;
            tot_wt += p[index].WT;
            p[index].TAT = p[index].BT + p[index].WT;
            tot_tat += p[index].TAT;
        }
    } // end of while loop

    // Printing output
    cout << "Process number ";
    cout << "Arrival time ";
    cout << "Burst time ";
    cout << "\tStart time";
    j = 0;
    while (j != 10) {
        j += 1;
        cout << " ";
    }
    cout << "\t\tFinal time";
    cout << "\tWait Time ";
    cout << "\tTurnAround Time" << endl;

    for (i = 0; i < n; i++) {
        cout << p[i].pos << "\t\t";
        cout << p[i].AT << "\t\t";
        cout << p[i].BT << "\t";
        j = 0;
        int v = 0;
        while (s[i][j] != -1) {
            cout << p[i].ST[j] << " ";
            j++;
            v += 3;
        }
        while (v != 40) {
            cout << " ";
            v += 1;
        }
        cout << p[i].FT << "\t\t";
        cout << p[i].WT << "\t\t";
        cout << p[i].TAT << endl;
    }

    // Calculating average wait time and turnaround time
    double avg_wt, avg_tat;
    avg_wt = tot_wt / static_cast<double>(n);
    avg_tat = tot_tat / static_cast<double>(n);

    // Printing average wait time and turnaround time
    cout << "The average wait time is: " << avg_wt << endl;
    cout << "The average TurnAround time is: " << avg_tat << endl;

    return 0;
}
