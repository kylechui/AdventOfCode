#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

auto main() -> int {
    auto lines = vector<string>{};
    for (auto line = string{}; getline(cin, line);) {
        lines.push_back(line);
    }

    auto seen = set<pair<ll, ll>>{{0, 0}};
    auto head = pair<ll, ll>{0, 0}, tail = pair<ll, ll>{0, 0};
    for (const auto& line : lines) {
        if (auto match = smatch{};
            regex_match(line, match, regex("^(.) (\\d+)$"))) {
            const auto count = stoll(match.str(2));
            const auto dir = match.str(1)[0];
            for (auto _ = 0; _ < count; _++) {
                switch (dir) {
                    case 'L':
                        head.first--;
                        break;
                    case 'R':
                        head.first++;
                        break;
                    case 'D':
                        head.second--;
                        break;
                    case 'U':
                        head.second++;
                        break;
                }

                if ((abs(head.first - tail.first) == 2
                     && abs(head.second - tail.second) == 1)
                    || (abs(head.first - tail.first) == 1
                        && abs(head.second - tail.second) == 2)) {
                    tail.first += (head.first - tail.first) > 0 ? 1 : -1;
                    tail.second += (head.second - tail.second) > 0 ? 1 : -1;
                } else if (abs(head.first - tail.first) == 2) {
                    tail.first += (head.first - tail.first) > 0 ? 1 : -1;
                } else if (abs(head.second - tail.second) == 2) {
                    tail.second += (head.second - tail.second) > 0 ? 1 : -1;
                }
                seen.insert(tail);
            }
        }
    }
    cout << seen.size() << endl;
}
