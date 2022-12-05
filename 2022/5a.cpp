#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

class Crane {
   public:
    Crane(const auto& input);
    void moveCrates(const auto& from, const auto& target, const auto& amount);
    void doInstructions(const auto& instructions);
    void printTopCrates() const;

   private:
    vector<string> crates;
    void moveCrate(const auto& from, const auto& target);
    void doInstruction(const auto& instruction);
};

Crane::Crane(const auto& initialState) {
    crates.resize(initialState[0].size() / 4 + 1);
    for (const auto& line : initialState) {
        for (size_t i = 1; i < line.size(); i += 4) {
            if (isalpha(line[i])) {
                crates[i / 4].push_back(line[i]);
            }
        }
    }
    ranges::for_each(crates, [](auto& s) { ranges::reverse(s); });
}

void Crane::moveCrate(const auto& from, const auto& target) {
    const auto crate = crates[from].back();
    crates[target].push_back(crate);
    crates[from].pop_back();
}

void Crane::moveCrates(const auto& from, const auto& target,
                       const auto& amount) {
    for (auto _ = 0; _ < amount; _++) {
        moveCrate(from, target);
    }
}

void Crane::doInstruction(const auto& instruction) {
    if (auto match = smatch{}; regex_search(
            instruction, match, regex("^move (\\d+) from (\\d+) to (\\d+)$"))) {
        auto amount = stoll(match.str(1));
        auto from = stoll(match.str(2)) - 1;
        auto target = stoll(match.str(3)) - 1;
        moveCrates(from, target, amount);
    }
}

void Crane::doInstructions(const auto& instructions) {
    for (const auto& instruction : instructions) {
        doInstruction(instruction);
    }
}

void Crane::printTopCrates() const {
    ranges::for_each(crates, [](const auto& s) {
        if (!s.empty()) {
            putchar(s.back());
        }
    });
}

int main() {
    auto lines = vector<string>{};
    for (auto line = string{}; getline(cin, line);) {
        lines.push_back(line);
    }

    auto view = lines | views::split("")
                | views::transform([](const auto& tmp) {
                      return vector<string>(tmp.begin(), tmp.end());
                  })
                | views::common;
    const auto input = vector<vector<string>>(view.begin(), view.end());
    const auto initialState = input[0];
    const auto instructions = input[1];

    auto crane = Crane(initialState);
    crane.doInstructions(instructions);
    crane.printTopCrates();
}
