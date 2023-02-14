#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

auto main() -> int {
    auto lines = vector<string>{};
    for (auto line{""s}; getline(cin, line);) {
        lines.push_back(line);
    }

    auto edges = unordered_map<string, vector<string>>{};
    auto flow = unordered_map<string, ll>{};
    auto seen = unordered_set<string>{};
    auto nonzero = vector<string>{};
    for (const auto& line : lines) {
        if (auto match = smatch{}; regex_match(
                line, match,
                regex("^Valve ([^ ]+) .* rate=(\\d+); .* valves? (.*)$"))) {
            auto view = match.str(3) | views::split(", "sv)
                        | views::transform([](const auto& v) {
                              return string(v.begin(), v.end());
                          })
                        | views::common;
            auto outnodes = vector<string>(view.begin(), view.end());
            edges[match.str(1)] = vector<string>(view.begin(), view.end());
            flow[match.str(1)] = stoll(match.str(2));
            if (stoll(match.str(2))) }
    }
}
