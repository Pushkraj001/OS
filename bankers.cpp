#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

static int m; // Number of processes (static for global access)
static int n; // Number of resources (static for global access)

// Function to input values into a 2D array matrix
void input(int matrix[][100], const std::string& s) {
    std::cout << "Enter " << s << " values: " << std::endl;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            std::cin >> matrix[i][j];
        }
    }
}

int main() {
    std::vector<int> arrayList; // Vector to store the execution order of processes
    
    // Input number of resources and processes
    std::cout << "Enter number of resources: ";
    std::cin >> n;
    std::cout << "Enter number of processes: ";
    std::cin >> m;

    int allocate[100][100]; // Matrix to store allocated resources for each process
    int maxNeed[100][100]; // Matrix to store maximum need of resources for each process
    int remNeed[100][100]; // Matrix to store remaining need of resources for each process
    int flag[100]; // Array to mark whether a process has been executed or not
    std::fill(flag, flag + m, 0); // Initialize flag array with zeros

    int totalAvailable[100]; // Array to store total available memory for each resource type
    int totalAllocate[100]; // Array to store total allocated memory for each resource type
    int available[100]; // Array to store available memory for each resource type

    // Input allocated resources and maximum need for each process
    input(allocate, "Allocated");
    input(maxNeed, "Max Need");

    // Input total available memory for each resource type
    std::cout << "Total Available Memory: " << std::endl;
    for (int i = 0; i < n; i++) {
        std::cin >> totalAvailable[i];
    }

    // Calculate remaining need for each process
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            remNeed[i][j] = maxNeed[i][j] - allocate[i][j];
        }
    }

    // Calculate total allocated memory for each resource type
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum = 0;
        for (int j = 0; j < m; j++) {
            sum += allocate[j][i];
        }
        totalAllocate[i] = sum;
    }

    // Calculate available memory for each resource type
    for (int i = 0; i < n; i++) {
        available[i] = totalAvailable[i] - totalAllocate[i];
    }

    int count = 0; // Counter to track the number of resources allocated to a process
    int release = 0; // Counter to track the number of processes that cannot be executed
    bool flg = true; // Flag to control the execution of the while loop

    // Loop to find the execution order of processes
    while (flg) {
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                // Check if remaining need of process i for resource j can be satisfied
                // and if the process has not been executed yet
                if (remNeed[i][j] <= available[j] && flag[i] == 0) {
                    count++;
                    // If all resource requests for process i can be satisfied
                    if (count == n) {
                        count = 0;
                        flag[i] = 1; // Mark process i as executed
                        // Update available resources after executing process i
                        for (int k = 0; k < n; k++) {
                            available[k] = available[k] + allocate[i][k];
                        }
                        arrayList.push_back(i + 1); // Store the execution order of process i
                    }
                } else {
                    release++; // Increment release counter if process cannot be executed
                    if (release == m) {
                        flg = false; // Exit the loop if all processes are considered for execution
                    }
                    break;
                }
            }
        }
    }

    // Print the execution order of processes or indicate deadlock
    if (arrayList.empty()) {
        std::cout << "Deadlock occurs." << std::endl;
    } else {
        std::cout << "Order: ";
        for (int i : arrayList) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
