#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

auto getPriority(const auto& s) {
    const auto sz = s.size();
    const auto half = unordered_set(s.begin(), s.begin() + sz / 2);
    auto view = s | views::drop(sz / 2)
                | views::filter([&](auto c) { return half.contains(c); })
                | views::common;
    return isupper(view.front()) ? view.front() - 'A' + 27
                                 : view.front() - 'a' + 1;
}

int main() {
    auto s = string{};
    auto totalPriority = ll{};
    while (getline(cin, s)) {
        totalPriority += getPriority(s);
    }
    cout << totalPriority << endl;
}
