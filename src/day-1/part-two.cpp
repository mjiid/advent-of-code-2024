#include <iostream>
#include <unordered_map>
#include <unordered_set>

using namespace std;

int main() {
    unordered_map<int, int> right;
    unordered_map<int, int> left;

    int x, y;

    while (cin >> x >> y) {
        left[x]++;
        right[y]++;
    }

    long long score = 0;
    for (const auto& p : left) {
        score += p.first * right[p.first] * p.second;
    }

    cout << score << endl;
    return 0;
}