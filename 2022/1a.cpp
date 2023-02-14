#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;

auto main() -> int {
    auto lines = vector<string>{};
    for (auto line = string{}; getline(cin, line);) {
        lines.push_back(line);
    }

    auto cookies =
        lines | views::split("") | views::transform([](const auto& v) {
            return accumulate(
                v.begin(), v.end(), 0,
                [](auto sum, const auto& s) { return sum + stoi(s); });
        });
    cout << ranges::max(cookies) << endl;
}
