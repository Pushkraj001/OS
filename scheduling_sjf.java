import java.util.Scanner;

public class scheduling_sjf {
    // Function to find the waiting time for all processes
    static void findWaitingTime(int processes[], int n, int bt[], int wt[], int at[]) {
        int service_time[] = new int[n];
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
    static void findTurnAroundTime(int processes[], int n, int bt[], int wt[], int tat[]) {
        // calculating turnaround time by adding bt[i] + wt[i]
        for (int i = 0; i < n; i++)
            tat[i] = bt[i] + wt[i];
    }

    // Function to calculate average time
    static void findavgTime(int processes[], int n, int bt[], int at[]) {
        int wt[] = new int[n];
        int tat[] = new int[n];
        int total_wt = 0, total_tat = 0;

        // Function to find waiting time of all processes
        findWaitingTime(processes, n, bt, wt, at);

        // Function to find turn around time for all processes
        findTurnAroundTime(processes, n, bt, wt, tat);

        // Display processes along with all details
        System.out.println("Processes " + " Arrival time " + " Burst time " + " Waiting time " + " Turn around time");

        // Calculate total waiting time and total turn around time
        for (int i = 0; i < n; i++) {
            total_wt = total_wt + wt[i];
            total_tat = total_tat + tat[i];
            System.out.println(" " + processes[i] + "\t\t" + at[i] + "\t\t" + bt[i] + "\t " + wt[i] + "\t\t " + tat[i]);
        }

        System.out.println("Average waiting time = " + ((float) total_wt / (float) n));
        System.out.println("Average turn around time = " + ((float) total_tat / (float) n));
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter the number of processes: ");
        int n = scanner.nextInt();

        int[] processes = new int[n];
        int[] arrival_time = new int[n];
        int[] burst_time = new int[n];

        System.out.println("Enter arrival time for each process:");
        for (int i = 0; i < n; i++) {
            System.out.print("Arrival time of process " + (i + 1) + ": ");
            arrival_time[i] = scanner.nextInt();
            processes[i] = i + 1; // Assigning process IDs
        }

        System.out.println("Enter burst time for each process:");
        for (int i = 0; i < n; i++) {
            System.out.print("Burst time for process " + (i + 1) + ": ");
            burst_time[i] = scanner.nextInt();
        }

        findavgTime(processes, n, burst_time, arrival_time);
        scanner.close();
    }
}
