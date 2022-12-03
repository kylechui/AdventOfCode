#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int main() {
    auto heap = vector<ll>{};
    auto curCookies = ll{};
    auto s = string{};
    while (getline(cin, s)) {
        if (s.empty()) {
            heap.push_back(curCookies);
            ranges::push_heap(heap, greater<ll>());
            curCookies = 0;
            if (heap.size() > 3) {
                ranges::pop_heap(heap, greater<ll>());
                heap.pop_back();
            }
        } else {
            curCookies += stoll(s);
        }
    }
    cout << accumulate(heap.cbegin(), heap.cend(), 0) << endl;
}
