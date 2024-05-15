#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

class Replacement {
private:
    int f;
    std::vector<int> runQ;
    int pageF = 0;
    int time = 0;
    std::unordered_map<int, int> map;

public:
    Replacement(int f) : f(f) {
        runQ.resize(f, -1);
    }

    void push(int m) {
        if (!contains(m)) {
            runQ[pageF % f] = m;
            pageF++;
            map[pageF] = time;
            std::cout << "Miss: " << m << std::endl;
        } else {
            std::cout << "Hit: " << m << std::endl;
        }
        time++;
        printRunQ();
    }

    const std::unordered_map<int, int>& getMap() const {
        return map;
    }

private:
    bool contains(int m) {
        for (int i = 0; i < f; i++) {
            if (runQ[i] == m) {
                return true;
            }
        }
        return false;
    }

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

    Replacement r(f);
    for (int i = 0; i < n; i++) {
        r.push(ref[i]);
    }

    std::cout << "PageFs\tTime" << std::endl;
    for (const auto& entry : r.getMap()) {
        std::cout << entry.first << "\t\t" << entry.second << std::endl;
    }

    return 0;
}
