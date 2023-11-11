#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll pow_mod(ll a , ll b , ll m){
    ll res = 1;
    while(b){
        res = res * (b & 1 ? a : 1) % m;
        a = a * a;
        a %= m;
        b >>= 1;
    }
    return res;
}
ll GCD(ll a , ll b){
    while(b != 0){
        a = a % b;
        ll tmp = a;
        a = b;
        b = tmp;
    }
    return a;
}

const ll MAXN = 1e6 + 7;
const ll MAXVAL = 1e5 + 7;
int n , d;
int a[MAXN];
int bit[MAXVAL];
int maxx = 0;
void update(int idx , int val){
    for( ; idx <= maxx ; idx += idx & -idx){
        bit[idx] = max(bit[idx] , val);
    }
}

int get(int idx){
    int res = 0;
    for( ; idx > 0 ; idx -= idx & -idx){
        res = max(res , bit[idx]);
    }
    return res;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    freopen("new.inp" , "r" , stdin);
    freopen("new.out" , "w" , stdout);
    cin >> n;
    for(int i = 1 ; i <= n ; i ++){
        cin >> a[i];
        maxx = max(maxx , a[i]);
    }
    update(a[1] , 1);
    int res = 1;
    for(int i = 1 ; i <= n ; i ++){
        int cur = get(a[i] - 1 );
        update(a[i] , cur + 1);
        res = max(res , cur + 1);
    }
    cout << res << '\n';
    return 0;
}