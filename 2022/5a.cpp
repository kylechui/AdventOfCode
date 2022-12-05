#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

class Crane {
   public:
    Crane();
    void moveCrates(const auto& from, const auto& target, const auto& amount);
    void doInstruction(const auto& instruction);
    void printTopCrates() const;

   private:
    vector<string> crates;
    void moveCrate(const auto& from, const auto& target);
};

Crane::Crane() {
    crates = vector<string>(9);
    for (auto line = string{}; getline(cin, line) && !isdigit(line[1]);) {
        for (size_t i = 1; i < line.size(); i += 4) {
            if (line[i] != ' ') {
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

void Crane::printTopCrates() const {
    ranges::for_each(crates, [](const auto& s) {
        if (!s.empty()) {
            putchar(s.back());
        }
    });
}

int main() {
    auto crane = Crane{};
    for (auto line = string{}; getline(cin, line);) {
        crane.doInstruction(line);
    }
    crane.printTopCrates();
}
