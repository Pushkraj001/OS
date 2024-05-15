#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <string>

class ReplacementOptimal {
private:
    int f;
    std::vector<int> runQ;
    int pageF = 0;
    int time = 0;
    std::unordered_map<int, int> map;

public:
    ReplacementOptimal(int f) : f(f) {
        runQ.resize(f, -1);
    }

    void push(int m, const std::vector<int>& futRef) {
        if (!contains(m)) {
            if (pageF < f) {
                runQ[pageF % f] = m;
                pageF++;
            } else {
                pageF++;
                int farthest = -1;
                int replaceIndex = -1;
                for (int i = 0; i < f; i++) {
                    int currentP = runQ[i];
                    bool found = false;
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
                    if (!found) {
                        replaceIndex = i;
                        break;
                    }
                }
                runQ[replaceIndex] = m;
            }
            map[pageF] = time;
            std::cout << "Miss: " << m << std::endl;
        } else {
            std::cout << "Hit: " << m << std::endl;
        }
        time++;
        printRunQ();
    }

    bool contains(int m) {
        for (int i = 0; i < f; i++) {
            if (runQ[i] == m) {
                return true;
            }
        }
        return false;
    }

    const std::unordered_map<int, int>& getMap() const {
        return map;
    }

private:
    void printRunQ() {
        std::cout << "RunQ: ";
        for (int i : runQ) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    std::cout << "Enter string: ";
    std::string str;
    std::cin >> str;
    int n = str.length();
    std::vector<int> ref(n);
    for (int i = 0; i < n; i++) {
        ref[i] = str[i] - '0';
    }

    std::cout << "Enter number of frames: ";
    int f;
    std::cin >> f;

    std::vector<int> futRef(ref.begin() + 1, ref.end());
    ReplacementOptimal r(f);
    for (int i = 0; i < n; i++) {
        r.push(ref[i], futRef);
    }

    std::cout << "PageFs\tTime" << std::endl;
    for (const auto& map : r.getMap()) {
        std::cout << map.first << "\t\t" << map.second << std::endl;
    }

    return 0;
}
