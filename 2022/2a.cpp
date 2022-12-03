#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

auto getPoints(const auto& s) {
    auto otherMove = s[0] - 'A', yourMove = s[2] - 'X';
    auto points = yourMove + 1;
    if (otherMove == yourMove) points += 3;
    if (otherMove + 1 == yourMove || otherMove == yourMove + 2) points += 6;
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
