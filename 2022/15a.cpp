#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

auto get_distance(const auto& p1, const auto& p2) -> ll {
    return abs(p1.first - p2.first) + abs(p1.second - p2.second);
}

auto main() -> int {
    auto lines = vector<string>{};
    for (auto line{""s}; getline(cin, line);) {
        lines.push_back(line);
    }

    constexpr auto row{2'000'000ll};
    auto positions = unordered_set<ll>{}, beacons = unordered_set<ll>{};
    for (const auto& line : lines) {
        if (auto match = smatch{};
            regex_match(line, match,
                        regex("^Sensor at x=(-?\\d+), y=(-?\\d+): closest "
                              "beacon is at x=(-?\\d+), y=(-?\\d+)$"))) {
            auto sensor = pair{stoll(match.str(1)), stoll(match.str(2))};
            auto beacon = pair{stoll(match.str(3)), stoll(match.str(4))};
            auto dist = get_distance(sensor, beacon);
            auto diff = dist - abs(row - sensor.second);
            if (beacon.second == row) beacons.insert(beacon.first);
            for (auto x{sensor.first - diff}; x <= sensor.first + diff; x++) {
                positions.insert(x);
            }
        }
    }
    cout << positions.size() - beacons.size() << endl;
}
