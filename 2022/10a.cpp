#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

auto main() -> int {
    auto lines = vector<string>{};
    for (auto line = string{}; getline(cin, line);) {
        lines.push_back(line);
    }

    auto cycle = 0ll, reg = 1ll, strength = 0ll;
    for (const auto& line : lines) {
        if (auto match = smatch{};
            regex_match(line, match, regex("^addx (-?\\d+)$"))) {
            if ((cycle + 20) % 40 > (cycle + 22) % 40) {
                strength += reg * (((cycle + 22) / 40) * 40 - 20);
            }
            reg += stoll(match.str(1));
            cycle += 2;
        } else if (line == "noop") {
            if ((cycle + 20) % 40 > (cycle + 21) % 40) {
                strength += reg * (((cycle + 21) / 40) * 40 - 20);
            }
            cycle++;
        }
    }

    cout << strength << endl;
}
