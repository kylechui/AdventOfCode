#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

auto main() -> int {
    auto line = string{};
    getline(cin, line);

    const auto numUnique = 14;
    for (size_t i = 0; i + numUnique < line.size(); i++) {
        const auto current =
            unordered_set<char>(line.begin() + i, line.begin() + i + numUnique);
        if (current.size() == numUnique) {
            cout << i + numUnique << endl;
            break;
        }
    }
}
