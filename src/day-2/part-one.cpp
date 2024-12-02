#include <iostream>
#include <vector>

using namespace std;

bool isSafe(const vector<int>& record) {
    const bool incr = record[1] > record[0];
    for (int i = 0; i < record.size() - 1; i++) {
        int diff = record[i + 1] - record[i];

        if ((incr && diff < 0) || (!incr && diff > 0)) {
            return false;
        }

        diff = abs(diff);
        if (diff < 1 || diff > 3) {
            return false;
        }
    }
    return true;
}

int main() {
    int safe = 0;
    string s;
    while (getline(cin, s)) {
        if (s.size() == 0) break;
        vector<int> v;
        int index = 0;
        for (int i = 0; i < s.size(); i++) {
            if (isspace(s[i]) || i == s.size() - 1) {
                v.push_back(stoi(s.substr(index, i - index + 1)));
                index = i;
            }
        }

        if (isSafe(v)) safe++;
    }
    cout << safe << endl;

    return 0;
}