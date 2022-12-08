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
    auto left = vector<vector<ll>>(rows, vector<ll>(cols, 0)),
         right = vector<vector<ll>>(rows, vector<ll>(cols, 0)),
         up = vector<vector<ll>>(rows, vector<ll>(cols, 0)),
         down = vector<vector<ll>>(rows, vector<ll>(cols, 0));
    for (auto i = 0; i < rows; i++) {
        auto stk = vector<pair<int, char>>{};
        for (auto j = 0; j < cols; j++) {
            while (!stk.empty() && stk.back().second < lines[i][j]) {
                stk.pop_back();
            }
            left[i][j] = stk.empty() ? j : j - stk.back().first;
            stk.push_back({j, lines[i][j]});
        }

        stk.clear();
        for (auto j = cols - 1; j >= 0; j--) {
            while (!stk.empty() && stk.back().second < lines[i][j]) {
                stk.pop_back();
            }
            right[i][j] = stk.empty() ? rows - j - 1 : stk.back().first - j;
            stk.push_back({j, lines[i][j]});
        }
    }

    for (auto j = 0; j < cols; j++) {
        auto stk = vector<pair<int, char>>{};
        for (auto i = 0; i < rows; i++) {
            while (!stk.empty() && stk.back().second < lines[i][j]) {
                stk.pop_back();
            }
            up[i][j] = stk.empty() ? i : i - stk.back().first;
            stk.push_back({i, lines[i][j]});
        }
        stk.clear();
        for (auto i = rows - 1; i >= 0; i--) {
            while (!stk.empty() && stk.back().second < lines[i][j]) {
                stk.pop_back();
            }
            down[i][j] = stk.empty() ? cols - i - 1 : stk.back().first - i;
            stk.push_back({i, lines[i][j]});
        }
    }

    auto maxScore = ll{};
    for (auto i = 1; i < rows - 1; i++) {
        for (auto j = 1; j < cols - 1; j++) {
            maxScore =
                max(maxScore, left[i][j] * right[i][j] * up[i][j] * down[i][j]);
        }
    }
    cout << maxScore << endl;
}
