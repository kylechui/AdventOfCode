#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;

int main() {
    auto maxCookies = ll{}, curCookies = ll{};
    auto s = string{};
    while (getline(cin, s)) {
        if (s.empty()) {
            maxCookies = max(maxCookies, curCookies);
            curCookies = 0;
        } else {
            curCookies += stoll(s);
        }
    }
    cout << max(maxCookies, curCookies) << endl;
}
