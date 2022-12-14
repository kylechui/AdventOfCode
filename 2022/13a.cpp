#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

auto get_representation(const auto& packet) -> vector<pair<optional<ll>, ll>> {
    auto representation = vector<pair<optional<ll>, ll>>{};
    auto cur = optional<ll>{};
    auto depth = 0ll;
    for (size_t i{0}; i < packet.size(); i++) {
        auto c = packet[i];
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
    }
    return representation;
}

auto main() -> int {
    auto lines = vector<string>{};
    for (auto line{""s}; getline(cin, line);) {
        lines.push_back(line);
    }

    auto view = lines | views::split("") | views::transform([](const auto& v) {
                    return vector<string>(v.begin(), v.end());
                })
                | views::common;
    auto input = vector<vector<string>>(view.begin(), view.end());
    auto sum = 0;
    for (size_t i{0}; i < input.size(); i++) {
        if (get_representation(input[i][0])
            <= get_representation(input[i][1])) {
            sum += i + 1;
        }
    }
    cout << sum << endl;
}
