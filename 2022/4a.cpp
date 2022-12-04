#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

auto isContained(const auto& p1, const auto& p2) {
    return (p1.first >= p2.first && p1.second <= p2.second)
           || (p1.first <= p2.first && p1.second >= p2.second);
}

int main() {
    auto match = smatch{};
    auto totalContained = ll{};
    for (const auto& s : views::istream<string>(cin)) {
        if (regex_search(s, match, regex("^(\\d+)-(\\d+),(\\d+)-(\\d+)$"))) {
            auto range1 = make_pair(stoll(match.str(1)), stoll(match.str(2)));
            auto range2 = make_pair(stoll(match.str(3)), stoll(match.str(4)));
            totalContained += isContained(range1, range2);
        }
    }
    cout << totalContained << endl;
}
