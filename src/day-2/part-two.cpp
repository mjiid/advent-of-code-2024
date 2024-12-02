#include <iostream>
#include <vector>

using namespace std;

bool isSafeRecord(const vector<int>& record) {
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

bool isSafe(const vector<int>& record) {
    const size_t n = record.size();
    if (isSafeRecord(record)) return true;

    // The record is not safe, Check if it's possible to make it safe by removing a single bad level,
    for (int i = 0; i < n; i++) {
        vector<int> tmp(record);
        tmp.erase(tmp.begin() + i);

        if (isSafeRecord(tmp)) return true;
    }
    return false;
}

int main() {
    int safe = 0;
    string s;
    while (getline(cin, s)) {
        if (s.empty()) break;
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