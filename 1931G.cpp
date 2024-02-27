
#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>
 
using namespace std;
 
typedef long long ll;
 
const int mod = 998244353;
 
ll pow_mod(ll x, ll p) {
    if (p == 0) {
        return 1;
    }
    if (p % 2 == 0) {
        ll y = pow_mod(x, p / 2);
        return (y * y) % mod;
    }
    return (x * pow_mod(x, p - 1)) % mod;
}
 
ll inv(ll x) {
    return pow_mod(x, mod - 2);
}
 
vector<ll> fact = {1};
 
ll cnk(ll n, ll k) {
    ll res = fact[n];
    res = (res * inv(fact[k])) % mod;
    res = (res * inv(fact[n - k])) % mod;
    return res;
}
 
ll calc(int n1, int n2, int n3, int n4) {
    return (cnk(n1 + n3 - 1, n3) * cnk(n2 + n4 - 1, n4)) % mod;
}
 
void solve() {
    int n1, n2, n3, n4;
    cin >> n1 >> n2 >> n3 >> n4;
    if (n1 + n2 == 0) {
        cout << (n3 == 0 || n4 == 0 ? 1 : 0) << '\n';
        return;
    }
    if (abs(n1 - n2) > 1) {
        cout << "0\n";
        return;
    }
    ll res = 0;
    if (n1 <= n2) {
        res += calc(n1 + 1, n2, n3, n4);
    }
    if (n2 <= n1) {
        res += calc(n1, n2 + 1, n3, n4);
    }
    cout << res % mod << '\n';
}
 
int main() {
    for (ll i = 1; i <= 4e6; ++i) {
        fact.push_back((fact.back() * i) % mod);
    }
    int t;
    cin >> t;
    for (int _ = 0; _ < t; ++_) {
        solve();
    }
}
