#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    vector<int> a;
    vector<int> b;

    int a1, b1;

    while (cin >> a1 >> b1) {
        a.push_back(a1);
        b.push_back(b1);
    }

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    long long ans = 0LL;
    for (int i = 0; i < a.size(); i++) {
        ans += abs(a[i] - b[i]);
    }

    cout << ans << endl;
    return 0;
 }