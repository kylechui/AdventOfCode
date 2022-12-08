#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

auto main() -> int {
    auto lines = vector<string>{};
    for (auto line = string{}; getline(cin, line);) {
        lines.push_back(line);
    }

    const auto rows = ll(lines.size()), cols = ll(lines[0].size());
    auto left = lines, right = lines, up = lines, down = lines;
    for (auto i = 0; i < rows; i++) {
        for (auto j = 1; j < cols; j++) {
            left[i][j] = max(left[i][j - 1], lines[i][j]);
        }
        for (auto j = cols - 2; j >= 0; j--) {
            right[i][j] = max(right[i][j + 1], lines[i][j]);
        }
    }

    for (auto j = 0; j < cols; j++) {
        for (auto i = 1; i < rows; i++) {
            up[i][j] = max(up[i - 1][j], lines[i][j]);
        }
        for (auto i = rows - 2; i >= 0; i--) {
            down[i][j] = max(down[i + 1][j], lines[i][j]);
        }
    }

    auto count = ll{};
    for (auto i = 1; i < rows - 1; i++) {
        for (auto j = 1; j < cols - 1; j++) {
            const auto c = lines[i][j];
            count += c > left[i][j - 1] || c > right[i][j + 1]
                     || c > up[i - 1][j] || c > down[i + 1][j];
        }
    }
    cout << count + 2 * (rows + cols - 2) << endl;
}
