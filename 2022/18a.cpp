#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

auto main() -> int {
    auto blocks = unordered_set<array<ll, 3>, decltype([](const auto& coords) {
                                    const auto& [x, y, z] = coords;
                                    return 10000 * x + 100 * y + z;
                                })>{};
    auto totalArea{0ll};
    for (auto line{""s}; getline(cin, line);) {
        if (auto match = smatch{};
            regex_match(line, match, regex("^(\\d+),(\\d+),(\\d+)$"))) {
            const auto x = stoll(match.str(1));
            const auto y = stoll(match.str(2));
            const auto z = stoll(match.str(3));
            totalArea += blocks.contains({x - 1, y, z}) ? -1 : 1;
            totalArea += blocks.contains({x + 1, y, z}) ? -1 : 1;
            totalArea += blocks.contains({x, y - 1, z}) ? -1 : 1;
            totalArea += blocks.contains({x, y + 1, z}) ? -1 : 1;
            totalArea += blocks.contains({x, y, z - 1}) ? -1 : 1;
            totalArea += blocks.contains({x, y, z + 1}) ? -1 : 1;
            blocks.insert({x, y, z});
        }
    }
    cout << totalArea << endl;
}
