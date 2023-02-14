#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

auto main() -> int {
    auto xy = unordered_set<array<ll, 2>, decltype([](const auto& coords) {
                                const auto& [x, y] = coords;
                                return 100 * x + y;
                            })>{},
         yz = xy, xz = xy;
    for (auto line{""s}; getline(cin, line);) {
        if (auto match = smatch{};
            regex_match(line, match, regex("^(\\d+),(\\d+),(\\d+)$"))) {
            const auto x = stoll(match.str(1));
            const auto y = stoll(match.str(2));
            const auto z = stoll(match.str(3));
            xy.insert({x, y});
            xz.insert({x, z});
            yz.insert({y, z});
        }
    }
    cout << 2 * (xy.size() + xz.size() + yz.size()) << endl;
}
