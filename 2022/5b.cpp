#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

auto getInitialState() {
    auto line = string{};
    auto state = vector<string>(9);
    while (getline(cin, line) && !isdigit(line[1])) {
        for (size_t i = 1; i < line.size(); i += 4) {
            if (line[i] != ' ') {
                state[i / 4].push_back(line[i]);
            }
        }
    }
    ranges::for_each(state, [](auto& s) { ranges::reverse(s); });
    return state;
}

int main() {
    auto state = getInitialState();
    auto moveCrates = [&state](auto from, auto target, auto count) {
        for (auto i = 0; i < count; i++) {
            state[target].push_back(state[from].back());
            state[from].pop_back();
        }
        reverse(next(state[target].end(), -count), state[target].end());
    };

    auto line = string{};
    auto match = smatch{};
    while (getline(cin, line)) {
        if (regex_search(line, match,
                         regex("^move (\\d+) from (\\d+) to (\\d+)$"))) {
            auto count = stoll(match.str(1));
            auto from = stoll(match.str(2)) - 1;
            auto target = stoll(match.str(3)) - 1;
            moveCrates(from, target, count);
        }
    }

    ranges::for_each(state, [](const auto& s) { putchar(s.back()); });
}
