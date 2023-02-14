#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

auto get_distance(const auto& p1, const auto& p2) -> ll {
    return abs(p1.first - p2.first) + abs(p1.second - p2.second);
}

auto is_valid(const auto& position) -> bool {
    constexpr auto mn = 0ll, mx = 4'000'000ll;
    return mn <= position.first && position.first <= mx && mn <= position.second
           && position.second <= mx;
}

auto get_perimeter(const auto& center, const auto& distance)
    -> vector<pair<ll, ll>> {
    const auto& [x, y] = center;
    auto perimeter = vector<pair<ll, ll>>{};
    for (auto i = 0; i < distance + 1; i++) {
        if (is_valid(pair{x + i, y + distance + 1 - i}))
            perimeter.push_back({x + i, y + distance + 1 - i});
        if (is_valid(pair{x + distance + 1 - i, y - i}))
            perimeter.push_back({x + distance + 1 - i, y - i});
        if (is_valid(pair{x - i, y - distance - 1 + i}))
            perimeter.push_back({x - i, y - distance - 1 + i});
        if (is_valid(pair{x - distance - 1 + i, y + i}))
            perimeter.push_back({x - distance - 1 + i, y + i});
    }
    return perimeter;
}

auto main() -> int {
    auto lines = vector<string>{};
    for (auto line{""s}; getline(cin, line);) {
        lines.push_back(line);
    }

    auto positions = vector<pair<ll, ll>>{}, sensors = vector<pair<ll, ll>>{},
         beacons = vector<pair<ll, ll>>{};
    sensors.reserve(lines.size());
    beacons.reserve(lines.size());
    for (const auto& line : lines) {
        if (auto match = smatch{};
            regex_match(line, match,
                        regex("^Sensor at x=(-?\\d+), y=(-?\\d+): closest "
                              "beacon is at x=(-?\\d+), y=(-?\\d+)$"))) {
            auto sensor = pair{stoll(match.str(1)), stoll(match.str(2))};
            auto beacon = pair{stoll(match.str(3)), stoll(match.str(4))};
            sensors.push_back(sensor);
            beacons.push_back(beacon);
            auto dist = get_distance(sensor, beacon);
            auto perimeter = get_perimeter(sensor, dist);
            for (const auto& point : perimeter) {
                positions.push_back(point);
            }
        }
    }

    for (size_t i{0}; i < sensors.size(); i++) {
        positions.erase(remove_if(positions.begin(), positions.end(),
                                  [&](const auto& point) {
                                      return get_distance(point, sensors[i])
                                             <= get_distance(beacons[i],
                                                             sensors[i]);
                                  }),
                        positions.end());
    }

    ranges::sort(positions);
    const auto& [x, y] = positions.front();
    cout << x * 4'000'000ll + y << endl;
}
