#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

auto main() -> int {
    auto instructions = queue<pair<ll, ll>>{};
    auto clock = 0ll;
    for (auto line = string{}; getline(cin, line);) {
        if (auto match = smatch{};
            regex_match(line, match, regex("^addx (-?\\d+)$"))) {
            clock += 2;
            instructions.push({clock, stoll(match.str(1))});
        } else {
            clock++;
        }
    }

    constexpr auto ROWS = 6, COLS = 40;
    auto screen = vector<string>(ROWS, string(COLS, '.'));
    auto position = 1ll;
    for (auto cycle = 0; cycle < ROWS * COLS; cycle++) {
        if (!instructions.empty() && instructions.front().first == cycle) {
            position += instructions.front().second;
            instructions.pop();
        }
        if (abs((cycle % COLS) - position) <= 1)
            screen[cycle / COLS][cycle % COLS] = '#';
    }

    for (const auto& line : screen) {
        cout << line << endl;
    }
}
