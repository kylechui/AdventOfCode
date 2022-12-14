#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

auto get_representation(const string& packet)
    -> vector<pair<optional<ll>, ll>> {
    auto representation = vector<pair<optional<ll>, ll>>{};
    auto cur = optional<ll>{};
    auto depth = 0ll;
    ranges::for_each(packet, [&](const auto& c) {
        if (isdigit(c)) {
            cur = 10 * cur.value_or(0ll);
            cur.value() += c - '0';
        } else {
            if (cur.has_value()) {
                representation.push_back({cur, depth});
            }
            cur.reset();
            if (c == ']') {
                representation.push_back({cur, depth});
            }
            depth += c == '[';
            depth -= c == ']';
        }
    });
    return representation;
}

auto main() -> int {
    auto input = vector<string>{"[[2]]", "[[6]]"};
    for (auto line{""s}; getline(cin, line);) {
        if (!line.empty()) input.push_back(line);
    }

    vector<vector<pair<optional<ll>, ll>>> representations{};
    ranges::transform(input, back_inserter(representations),
                      get_representation);
    ranges::sort(representations);

    const auto div1 = get_representation("[[2]]");
    const auto div2 = get_representation("[[6]]");
    auto product = 1;
    for (size_t i{0}; i < representations.size(); i++) {
        if (representations[i] == div1 || representations[i] == div2) {
            product *= i + 1;
        }
    }
    cout << product << endl;
}
