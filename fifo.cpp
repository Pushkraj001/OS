#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

// Class to implement a page replacement algorithm
class Replacement {
private:
    int f; // Number of frames
    std::vector<int> runQ; // Queue to store pages in frames
    int pageF = 0; // Total page faults
    int time = 0; // Current time
    std::unordered_map<int, int> map; // Map to store page and its last access time

public:
    // Constructor to initialize the number of frames
    Replacement(int f) : f(f) {
        runQ.resize(f, -1); // Initialize the runQ with -1 (empty frames)
    }

    // Method to simulate page access
    void push(int m) {
        // If page is not already in memory (page fault)
        if (!contains(m)) {
            runQ[pageF % f] = m; // Replace a page in a frame
            pageF++; // Increment page fault count
            map[pageF] = time; // Update last access time of the page
            std::cout << "Miss: " << m << std::endl; // Print page fault message
        } else {
            std::cout << "Hit: " << m << std::endl; // Print page hit message
        }
        time++; // Increment current time
        printRunQ(); // Print the current state of frames
    }

    // Method to get the map containing page and its last access time
    const std::unordered_map<int, int>& getMap() const {
        return map; // Return the map
    }

private:
    // Method to check if a page is present in memory
    bool contains(int m) {
        for (int i = 0; i < f; i++) {
            if (runQ[i] == m) {
                return true; // Page found in memory
            }
        }
        return false; // Page not found in memory
    }

    // Method to print the current state of frames
    void printRunQ() {
        std::cout << "RunQ: ";
        for (int i : runQ) {
            std::cout << i << " "; // Print each page in frames
        }
        std::cout << std::endl;
    }
};

int main() {
    std::cout << "Enter string: ";
    std::string str;
    std::cin >> str; // Input string representing page references
    int n = str.length(); // Length of the input string
    std::vector<int> ref(n); // Vector to store page references
    for (int i = 0; i < n; i++) {
        ref[i] = str[i] - '0'; // Convert char to int and store in vector
    }

    std::cout << "Enter number of frames: ";
    int f;
    std::cin >> f; // Input number of frames

    Replacement r(f); // Create an instance of Replacement class with given number of frames
    for (int i = 0; i < n; i++) {
        r.push(ref[i]); // Simulate page accesses using push method
    }

    // Print the page and its last access time
    std::cout << "PageFs\tTime" << std::endl;
    for (const auto& entry : r.getMap()) {
        std::cout << entry.first << "\t\t" << entry.second << std::endl;
    }

    return 0;
}
