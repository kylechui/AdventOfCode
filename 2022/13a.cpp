#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

auto get_representation(const auto& packet) -> vector<pair<ll, ll>> {
    auto representation = vector<pair<ll, ll>>{};
    auto cur = 0, depth = 0;
    for (size_t i{0}; i < packet.size(); i++) {
        auto c = packet[i];
        if (isdigit(c)) {
            cur *= 10;
            cur += c - '0';
        } else {
            if (isdigit(packet[i - 1])) {
                representation.push_back({cur, depth});
            }
            if (c == ']') {
                representation.push_back({INT_MIN, depth});
            }
            depth += c == '[';
            depth -= c == ']';
            cur = 0;
        }
    }
    return representation;
}

auto in_right_order(const auto& packets) -> bool {
    auto leftRep = get_representation(packets[0]),
         rightRep = get_representation(packets[1]);
    auto n = min(leftRep.size(), rightRep.size());
    for (size_t i{0}; i < n; i++) {
        if (leftRep[i] != rightRep[i]) return leftRep[i] < rightRep[i];
    }
    return n == leftRep.size();
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
        if (in_right_order(input[i])) {
            sum += i + 1;
        }
    }
    cout << sum << endl;
}
