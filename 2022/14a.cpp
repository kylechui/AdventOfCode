#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

auto main() -> int {
    auto lines = vector<string>{};
    for (auto line{""s}; getline(cin, line);) {
        lines.push_back(line);
    }

    auto rock = unordered_set<pair<ll, ll>, decltype([](const auto& p) {
                                  return p.first * 1000 + p.second;
                              })>{};
    auto highest = unordered_map<ll, ll>{};
    for (const auto& line : lines) {
        auto re = regex{"(\\d+),(\\d+)"};
        auto prevX = optional<ll>{}, prevY = optional<ll>{};
        for (auto it{sregex_iterator(line.begin(), line.end(), re)};
             it != sregex_iterator{}; it++) {
            const auto x = stoll(it->str(1)), y = stoll(it->str(2));
            if (prevX.has_value() && prevX.value() == x) {
                for (auto i{min(y, prevY.value())}; i <= max(y, prevY.value());
                     i++) {
                    rock.insert({x, i});

                    highest[x] = max(highest[x], i);
                }
            } else if (prevY.has_value() && prevY.value() == y) {
                for (auto i{min(x, prevX.value())}; i <= max(x, prevX.value());
                     i++) {
                    rock.insert({i, y});

                    highest[i] = max(highest[i], y);
                }
            }
            prevX = x, prevY = y;
        }
    }

    constexpr auto start = pair{500ll, 0ll};
    auto pos{start};
    auto numSand{0};
    while (!highest.contains(pos.first) || highest[pos.first] > pos.second) {
        if (!rock.contains({pos.first, pos.second + 1})) {
            pos.second++;
        } else if (!rock.contains({pos.first - 1, pos.second + 1})) {
            pos.first--;
        } else if (!rock.contains({pos.first + 1, pos.second + 1})) {
            pos.first++;
        } else {
            rock.insert({pos});
            pos = start;
            numSand++;
        }
    }
    cout << numSand << endl;
}
