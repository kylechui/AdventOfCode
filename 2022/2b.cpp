#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

auto getPoints(const auto& s) {
    auto outcome = s[2] - 'Y';
    auto points = (outcome + 1) * 3;
    points += (s[0] - 'A' + outcome + 3) % 3 + 1;
    return points;
}

int main() {
    auto s = string{};
    auto points = ll{};
    while (getline(cin, s)) {
        points += getPoints(s);
    }
    cout << points << endl;
}
