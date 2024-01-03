#include<bits/stdc++.h>
using namespace std;
#define ll long long
long long pow_mod(long long a, long long b, long long m) {
     long long res = 1;
     while(b){
            res = res * (b & 1 ? a : 1) % m;
            a = a * a % m; b >>= 1;
     }
     return res;
}
long long GCD(ll a , ll b){
    while(b != 0 ){
         a = a % b;
         long long tmp = a;
         a = b;
         b = tmp;
    }
    return a;
}
#define BIT(x, i) (((x) >> (i)) & 1)
#define MASK(i) (1LL << (i))
#define ONBIT(x, i) ((x) | MASK(i))
const ll MAXN = 5e4 + 7;
const ll MOD = 1e9 + 7;
const ll INF = 1e18 + 7;
int n , k;
ll bit[MAXN][200];
int a[MAXN], b[MAXN];
void update(int idx ,int mask ,ll val){
    for(  ;idx <= MAXN - 6 ; idx += idx & (-idx)){
        bit[idx][mask] += val;
        bit[idx][mask] %= MOD;
    }
}
ll get(int idx , int mask){
    ll res = 0;
    for( ; idx > 0 ; idx -= idx & (-idx)){
        res += bit[idx][mask];
        res %= MOD;
    }
    return res;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    freopen("new.inp" , "r" , stdin);
    freopen("new.out" , "w" , stdout);
    cin >> n >> k;
    for(int i = 1 ; i <= n ; i ++){
        cin >> a[i] >> b[i];
        a[i] ++;
        b[i] -- ;
    }
    ll res = 0;
    for(int i = 1 ; i <= n ; i ++){
        for(int j = 0 ; j < (1 << k) ; j ++){
            if(BIT(j , b[i]) == 0){
                int mask = ONBIT(j , b[i]);
                ll cur = get(a[i] - 1 , j);
                cur %= MOD;
                update(a[i] , mask , cur);
            }else{
                ll cur = get(a[i] - 1 , j);
                cur %= MOD;
                update(a[i] , j , cur);
            }
            if(j == 0){
                int mask = ONBIT(j , b[i]);
                update(a[i] , mask , 1);
            }
        }
    }
    cout << get(MAXN - 6 ,(1 << k) - 1) % MOD;
    return 0;
}
