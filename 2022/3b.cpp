#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

auto getPriority(const auto& tup) {
    const auto [sack1, sack2, sack3] = tup;
    const auto set1 = unordered_set(sack1.begin(), sack1.end());
    const auto set2 = unordered_set(sack2.begin(), sack2.end());
    auto view =
        sack3 | views::filter([&](const auto c) {
            return set1.find(c) != set1.end() && set2.find(c) != set2.end();
        })
        | views::common;
    return isupper(view.front()) ? view.front() - 'A' + 27
                                 : view.front() - 'a' + 1;
}

int main() {
    auto s1 = string{}, s2 = string{}, s3 = string{};
    auto totalPriority = ll{};
    while (getline(cin, s1) && getline(cin, s2) && getline(cin, s3)) {
        totalPriority += getPriority(make_tuple(s1, s2, s3));
    }
    cout << totalPriority << endl;
}
