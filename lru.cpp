#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

class ReplacementLRU {
private:
    int f;
    std::vector<int> runQ;
    int pageF = 0;
    int time = 0;
    std::unordered_map<int, int> map;
    std::unordered_map<int, int> page;

public:
    ReplacementLRU(int f) : f(f) {
        runQ.resize(f, -1);
    }

    void push(int m) {
        if (!contains(m)) {
            if (pageF < f) {
                runQ[pageF % f] = m;
                pageF++;
                page[pageF] = time;
            } else {
                pageF++;
                int lruIndex = 0;
                int lruTime = map[runQ[0]];
                for (int i = 1; i < f; i++) {
                    if (map[runQ[i]] < lruTime) {
                        lruTime = map[runQ[i]];
                        lruIndex = i;
                    }
                }
                runQ[lruIndex] = m;
                page[pageF] = time;
            }
            map[m] = time;
            std::cout << "Miss: " << m << std::endl;
        } else {
            map[m] = time;
            std::cout << "Hit: " << m << std::endl;
        }
        time++;
        printRunQ();
    }

    const std::unordered_map<int, int>& getPage() const {
        return page;
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

    ReplacementLRU r(f);
    for (int i = 0; i < n; i++) {
        r.push(ref[i]);
    }

    std::cout << "PageFs\tTime" << std::endl;
    for (const auto& page : r.getPage()) {
        std::cout << page.first << "\t\t" << page.second << std::endl;
    }

    return 0;
}
