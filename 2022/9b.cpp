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
    auto knots = vector<pair<ll, ll>>(10, pair<ll, ll>{0, 0});
    for (const auto& line : lines) {
        if (auto match = smatch{};
            regex_match(line, match, regex("^(.) (\\d+)$"))) {
            const auto count = stoll(match.str(2));
            const auto dir = match.str(1)[0];
            for (auto _ = 0; _ < count; _++) {
                switch (dir) {
                    case 'L':
                        knots[0].first--;
                        break;
                    case 'R':
                        knots[0].first++;
                        break;
                    case 'D':
                        knots[0].second--;
                        break;
                    case 'U':
                        knots[0].second++;
                        break;
                }

                for (auto i = 1; i < 10; i++) {
                    if ((abs(knots[i - 1].first - knots[i].first) >= 2
                         && abs(knots[i - 1].second - knots[i].second) >= 1)
                        || (abs(knots[i - 1].first - knots[i].first) >= 1
                            && abs(knots[i - 1].second - knots[i].second)
                                   >= 2)) {
                        knots[i].first +=
                            (knots[i - 1].first - knots[i].first) > 0 ? 1 : -1;
                        knots[i].second +=
                            (knots[i - 1].second - knots[i].second) > 0 ? 1
                                                                        : -1;
                    } else if (abs(knots[i - 1].first - knots[i].first) >= 2) {
                        knots[i].first +=
                            (knots[i - 1].first - knots[i].first) > 0 ? 1 : -1;
                    } else if (abs(knots[i - 1].second - knots[i].second)
                               >= 2) {
                        knots[i].second +=
                            (knots[i - 1].second - knots[i].second) > 0 ? 1
                                                                        : -1;
                    }
                }
                seen.insert(knots.back());
            }
        }
    }
    cout << seen.size() << endl;
}
