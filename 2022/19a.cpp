#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

auto main() -> int {
    for (auto line{""s}; getline(cin, line);) {
        if (auto match = smatch{}; regex_match(
                line, match,
                regex(
                    "^.*(\\d+).*(\\d+).*(\\d+).*(\\d+).*(\\d+).*(\\d+).*$"))) {
            auto oreRobot = stoll(match.str(1));
            auto clayRobot = stoll(match.str(2));
            auto obsidianRobot = pair{stoll(match.str(3)), stoll(match.str(3))};
            auto geodeRobot = pair{stoll(match.str(4)), stoll(match.str(5))};
        }
    }
}
