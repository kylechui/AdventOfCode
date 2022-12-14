#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

auto get_representation(const string& packet) -> vector<pair<ll, ll>> {
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

auto main() -> int {
    auto input = vector<string>{"[[2]]", "[[6]]"};
    for (auto line{""s}; getline(cin, line);) {
        if (!line.empty()) input.push_back(line);
    }

    vector<vector<pair<ll, ll>>> representations{};
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
