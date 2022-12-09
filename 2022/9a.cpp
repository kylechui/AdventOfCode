#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

auto main() -> int {
    constexpr auto NUM_KNOTS = 2ll;

    auto lines = vector<string>{};
    for (auto line = string{}; getline(cin, line);) {
        lines.push_back(line);
    }

    auto seen = set<pair<ll, ll>>{};
    auto knots = vector<pair<ll, ll>>(NUM_KNOTS);
    for (const auto& line : lines) {
        if (auto match = smatch{};
            regex_match(line, match, regex("^(.) (\\d+)$"))) {
            const auto dir = match.str(1)[0];
            const auto count = stoll(match.str(2));
            for (auto _ = 0; _ < count; _++) {
                knots[0].first -= dir == 'L';
                knots[0].first += dir == 'R';
                knots[0].second -= dir == 'D';
                knots[0].second += dir == 'U';

                for (auto i = 1; i < NUM_KNOTS; i++) {
                    const auto dx = knots[i - 1].first - knots[i].first;
                    const auto dy = knots[i - 1].second - knots[i].second;
                    if (abs(dx) > 1 || abs(dy) > 1) {
                        knots[i].first += (dx > 0) - (dx < 0);
                        knots[i].second += (dy > 0) - (dy < 0);
                    }
                }
                seen.insert(knots.back());
            }
        }
    }
    cout << seen.size() << endl;
}
