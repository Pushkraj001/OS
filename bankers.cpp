#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

static int m;
static int n;

void input(int matrix[][100], const std::string& s) {
    std::cout << "Enter " << s << " values: " << std::endl;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            std::cin >> matrix[i][j];
        }
    }
}

int main() {
    std::vector<int> arrayList;
    
    std::cout << "Enter number of resources: ";
    std::cin >> n;
    std::cout << "Enter number of processes: ";
    std::cin >> m;

    int allocate[100][100];
    int maxNeed[100][100];
    int remNeed[100][100];
    int flag[100];
    std::fill(flag, flag + m, 0);

    int totalAvailable[100];
    int totalAllocate[100];
    int available[100];

    input(allocate, "Allocated");
    input(maxNeed, "Max Need");

    std::cout << "Total Available Memory: " << std::endl;
    for (int i = 0; i < n; i++) {
        std::cin >> totalAvailable[i];
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            remNeed[i][j] = maxNeed[i][j] - allocate[i][j];
        }
    }

    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum = 0;
        for (int j = 0; j < m; j++) {
            sum += allocate[j][i];
        }
        totalAllocate[i] = sum;
    }

    for (int i = 0; i < n; i++) {
        available[i] = totalAvailable[i] - totalAllocate[i];
    }

    int count = 0;
    int release = 0;
    bool flg = true;

    while (flg) {
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (remNeed[i][j] <= available[j] && flag[i] == 0) {
                    count++;
                    if (count == n) {
                        count = 0;
                        flag[i] = 1;
                        for (int k = 0; k < n; k++) {
                            available[k] = available[k] + allocate[i][k];
                        }
                        arrayList.push_back(i + 1);
                    }
                } else {
                    release++;
                    if (release == m) {
                        flg = false;
                    }
                    break;
                }
            }
        }
    }

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
