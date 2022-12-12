#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

class Monkey {
   public:
    Monkey(const auto& input);
    auto getInspections() const -> ll;
    auto examineItems() -> vector<pair<ll, ll>>;
    auto add(const auto& item) -> void;

   private:
    ll inspections;
    queue<ll> items;
    pair<ll, ll> targetMonkeys;
    function<ll(ll)> operation;
    function<bool(ll)> passesTest;
    auto examineItem() -> pair<ll, ll>;
};

Monkey::Monkey(const auto& input) : inspections(0) {
    for (const auto& line : input) {
        if (auto match = smatch{};
            regex_match(line, match, regex("^ +Starting items: (.*)$"))) {
            auto view = match.str(1) | views::split(", "sv)
                        | views::transform([](const auto& v) {
                              return stoll(string(v.begin(), v.end()));
                          })
                        | views::common;
            for (const auto& e : view) {
                items.push(e);
            }
        } else if (regex_match(
                       line, match,
                       regex(
                           "^ +Operation: new = old (\\+|\\*) (\\d+|old)$"))) {
            const auto op = match.str(1);
            const auto other = match.str(2);
            operation = [=](const auto& old) -> ll {
                auto value = other == "old" ? old : stoll(other);
                return op == "+" ? old + value : old * value;
            };
        } else if (regex_match(line, match,
                               regex("^ +Test: divisible by (\\d+)$"))) {
            const auto divisor = stoll(match.str(1));
            passesTest = [=](const auto& value) -> bool {
                return value % divisor == 0;
            };
        } else if (regex_match(line, match,
                               regex("^ +If true: throw to monkey (\\d+)$"))) {
            targetMonkeys.first = stoll(match.str(1));
        } else if (regex_match(line, match,
                               regex("^ +If false: throw to monkey (\\d+)$"))) {
            targetMonkeys.second = stoll(match.str(1));
        }
    }
}

auto Monkey::getInspections() const -> ll { return inspections; };

auto Monkey::examineItems() -> vector<pair<ll, ll>> {
    auto vals = vector<pair<ll, ll>>{};
    vals.reserve(items.size());
    inspections += items.size();
    while (!items.empty()) {
        vals.push_back(examineItem());
    }
    return vals;
}

auto Monkey::examineItem() -> pair<ll, ll> {
    auto item = items.front();
    items.pop();
    item = operation(item) / 3;
    return {passesTest(item) ? targetMonkeys.first : targetMonkeys.second,
            item};
}

auto Monkey::add(const auto& item) -> void { items.push(item); }

auto main() -> int {
    auto lines = vector<string>{};
    for (auto line = string{}; getline(cin, line);) {
        lines.push_back(line);
    }

    auto view = lines | views::split("") | views::transform([](const auto& v) {
                    return vector<string>(v.begin(), v.end());
                })
                | views::common;
    auto monkeyInputs = vector<vector<string>>(view.begin(), view.end());

    auto monkeys = vector<Monkey>{};
    monkeys.reserve(monkeyInputs.size());
    for (const auto& monkeyInput : monkeyInputs) {
        monkeys.push_back(Monkey(monkeyInput));
    }

    for (auto i = 0; i < 20; i++) {
        for (auto& monkey : monkeys) {
            const auto vals = monkey.examineItems();
            for (const auto& [id, item] : vals) {
                monkeys[id].add(item);
            }
        }
    }

    auto inspections = vector<ll>{};
    inspections.reserve(monkeys.size());
    for (const auto& monkey : monkeys) {
        inspections.push_back(monkey.getInspections());
    }
    partial_sort(inspections.begin(), inspections.begin() + 2,
                 inspections.end(), greater<ll>());
    cout << inspections[0] * inspections[1] << endl;
}
