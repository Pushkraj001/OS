#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <string>

// Class to implement a page replacement algorithm using Optimal approximation
class ReplacementOptimal {
private:
    int f; // Number of frames
    std::vector<int> runQ; // Queue to store pages in frames
    int pageF = 0; // Total page faults
    int time = 0; // Current time
    std::unordered_map<int, int> map; // Map to store page and its insertion time

public:
    // Constructor to initialize the number of frames
    ReplacementOptimal(int f) : f(f) {
        runQ.resize(f, -1); // Initialize the runQ with -1 (empty frames)
    }

    // Method to simulate page access
    void push(int m, const std::vector<int>& futRef) {
        // If page is not already in memory (page fault)
        if (!contains(m)) {
            // If there are available frames
            if (pageF < f) {
                runQ[pageF % f] = m; // Replace a page in a frame
                pageF++; // Increment page fault count
            } else {
                pageF++; // Increment page fault count
                int farthest = -1; // Index of the farthest future reference
                int replaceIndex = -1; // Index of the page to be replaced
                // Find the page with the farthest future reference
                for (int i = 0; i < f; i++) {
                    int currentP = runQ[i];
                    bool found = false;
                    // Search for the page in future references
                    for (int j = time; j < futRef.size(); j++) {
                        if (currentP == futRef[j]) {
                            found = true;
                            if (j > farthest) {
                                farthest = j;
                                replaceIndex = i;
                            }
                            break;
                        }
                    }
                    // If not found in future references, replace it
                    if (!found) {
                        replaceIndex = i;
                        break;
                    }
                }
                runQ[replaceIndex] = m; // Replace the page with the farthest future reference
            }
            map[pageF] = time; // Update insertion time of the page
            std::cout << "Miss: " << m << std::endl; // Print page fault message
        } else {
            std::cout << "Hit: " << m << std::endl; // Print page hit message
        }
        time++; // Increment current time
        printRunQ(); // Print the current state of frames
    }

    // Method to check if a page is present in memory
    bool contains(int m) {
        for (int i = 0; i < f; i++) {
            if (runQ[i] == m) {
                return true; // Page found in memory
            }
        }
        return false; // Page not found in memory
    }

    // Method to get the map containing page and its insertion time
    const std::unordered_map<int, int>& getMap() const {
        return map; // Return the map
    }

private:
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
    std::vector<int> ref(n);
    for (int i = 0; i < n; i++) {
        ref[i] = str[i] - '0'; // Convert char to int and store in vector
    }

    std::cout << "Enter number of frames: ";
    int f;
    std::cin >> f; // Input number of frames

    // Generate future references by skipping the current reference
    std::vector<int> futRef(ref.begin() + 1, ref.end());
    ReplacementOptimal r(f); // Create an instance of ReplacementOptimal class with given number of frames
    for (int i = 0; i < n; i++) {
        r.push(ref[i], futRef); // Simulate page accesses using push method
    }

    // Print the page and its insertion time
    std::cout << "PageFs\tTime" << std::endl;
    for (const auto& map : r.getMap()) {
        std::cout << map.first << "\t\t" << map.second << std::endl;
    }

    return 0;
}
