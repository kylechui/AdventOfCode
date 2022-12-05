#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

auto getInitialState() {
    auto state = vector<string>(9);
    for (auto line = string{}; getline(cin, line) && !isdigit(line[1]);) {
        for (size_t i = 1; i < line.size(); i += 4) {
            if (isalpha(line[i])) {
                state[i / 4].push_back(line[i]);
            }
        }
    }
    ranges::for_each(state, [](auto& s) { ranges::reverse(s); });
    return state;
}

int main() {
    auto state = getInitialState();
    auto moveCrates = [&state](const auto& from, const auto& target,
                               const auto& count) {
        for (auto _ = 0; _ < count; _++) {
            state[target].push_back(state[from].back());
            state[from].pop_back();
        }
        reverse(next(state[target].end(), -count), state[target].end());
    };

    auto match = smatch{};
    for (auto line = string{}; getline(cin, line);) {
        if (regex_search(line, match,
                         regex("^move (\\d+) from (\\d+) to (\\d+)$"))) {
            const auto count = stoll(match.str(1));
            const auto from = stoll(match.str(2)) - 1;
            const auto target = stoll(match.str(3)) - 1;
            moveCrates(from, target, count);
        }
    }

    ranges::for_each(state, [](const auto& s) { putchar(s.back()); });
}
