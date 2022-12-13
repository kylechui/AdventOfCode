#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

auto main() -> int {
    auto grid = vector<string>{};
    for (auto line = string{}; getline(cin, line);) {
        grid.push_back(line);
    }
    const auto rows = ll(grid.size()), cols = ll(grid[0].size());

    auto height = char{};
    auto distance = vector<vector<ll>>(rows, vector<ll>(cols, -1));
    auto toVisit = queue<tuple<ll, ll, ll>>{};
    for (auto i = 0; i < rows; i++) {
        for (auto j = 0; j < cols; j++) {
            if (grid[i][j] == 'S') {
                toVisit.push({i, j, 0});
                break;
            }
        }
        if (!toVisit.empty()) break;
    }

    auto isValid = [&](const auto row, const auto col) -> bool {
        return 0 <= row && row < rows && 0 <= col && col < cols
               && (grid[row][col] == 'E' ? 'z' : grid[row][col]) - height <= 1;
    };
    while (!toVisit.empty()) {
        const auto [r, c, d] = toVisit.front();
        toVisit.pop();
        if (distance[r][c] != -1) continue;
        distance[r][c] = d;
        height = grid[r][c] == 'S' ? 'a' : grid[r][c];
        if (grid[r][c] == 'E') {
            cout << d << endl;
            return 0;
        }
        if (isValid(r - 1, c)) toVisit.push({r - 1, c, d + 1});
        if (isValid(r + 1, c)) toVisit.push({r + 1, c, d + 1});
        if (isValid(r, c - 1)) toVisit.push({r, c - 1, d + 1});
        if (isValid(r, c + 1)) toVisit.push({r, c + 1, d + 1});
    }
}
