#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

// Class to implement a page replacement algorithm using Least Recently Used (LRU) approximation
class ReplacementLRU {
private:
    int f; // Number of frames
    std::vector<int> runQ; // Queue to store pages in frames
    int pageF = 0; // Total page faults
    int time = 0; // Current time
    std::unordered_map<int, int> map; // Map to store page and its last access time
    std::unordered_map<int, int> page; // Map to store page and its insertion time

public:
    // Constructor to initialize the number of frames
    ReplacementLRU(int f) : f(f) {
        runQ.resize(f, -1); // Initialize the runQ with -1 (empty frames)
    }

    // Method to simulate page access
    void push(int m) {
        // If page is not already in memory (page fault)
        if (!contains(m)) {
            // If there are available frames
            if (pageF < f) {
                runQ[pageF % f] = m; // Replace a page in a frame
                pageF++; // Increment page fault count
                page[pageF] = time; // Update insertion time of the page
            } else {
                pageF++; // Increment page fault count
                int lruIndex = 0; // Index of least recently used page
                int lruTime = map[runQ[0]]; // Time of least recently used page
                // Find least recently used page
                for (int i = 1; i < f; i++) {
                    if (map[runQ[i]] < lruTime) {
                        lruTime = map[runQ[i]]; // Update least recently used time
                        lruIndex = i; // Update least recently used index
                    }
                }
                runQ[lruIndex] = m; // Replace least recently used page with new page
                page[pageF] = time; // Update insertion time of the page
            }
            map[m] = time; // Update last access time of the page
            std::cout << "Miss: " << m << std::endl; // Print page fault message
        } else {
            map[m] = time; // Update last access time of the page
            std::cout << "Hit: " << m << std::endl; // Print page hit message
        }
        time++; // Increment current time
        printRunQ(); // Print the current state of frames
    }

    // Method to get the map containing page and its insertion time
    const std::unordered_map<int, int>& getPage() const {
        return page; // Return the map
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

    ReplacementLRU r(f); // Create an instance of ReplacementLRU class with given number of frames
    for (int i = 0; i < n; i++) {
        r.push(ref[i]); // Simulate page accesses using push method
    }

    // Print the page and its insertion time
    std::cout << "PageFs\tTime" << std::endl;
    for (const auto& page : r.getPage()) {
        std::cout << page.first << "\t\t" << page.second << std::endl;
    }

    return 0;
}
