#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

auto get_distance(const auto& p1, const auto& p2) -> ll {
    return abs(p1.first - p2.first) + abs(p1.second - p2.second);
}

auto merge_ranges(auto& input) -> vector<pair<ll, ll>> {
    ranges::sort(input, [](const auto& p1, const auto& p2) {
        if (p1.second == p2.second) return p1.first < p2.first;
        return p1.second < p2.second;
    });
    auto output = vector<pair<ll, ll>>{input.front()};
    for (const auto& range : input) {
        if (range.first <= output.back().second + 1) {
            output.back().first = min(output.back().first, range.first);
            output.back().second = range.second;
        } else {
            input.push_back(range);
        }
    }
    return output;
}

auto main() -> int {
    auto lines = vector<string>{};
    for (auto line{""s}; getline(cin, line);) {
        lines.push_back(line);
    }

    constexpr auto row{2'000'000ll};
    auto positions = vector<pair<ll, ll>>{};
    auto beacons = unordered_set<ll>{};
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
            if (diff > 0) {
                positions.push_back({sensor.first - diff, sensor.first + diff});
            }
        }
    }

    auto simplified = merge_ranges(positions);
    auto total{0ll}, prevStop{LLONG_MIN};
    for (const auto& [start, stop] : simplified) {
        total += stop - max(start - 1, prevStop);
        prevStop = stop;
    }
    cout << total - beacons.size() << endl;
}
