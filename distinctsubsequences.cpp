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

string st1 , st2;
vector<int > base[30];
ll new_arr[MAXN];
int n;
struct item{
    int max_l , num;
} st[4000 + 7];
void update(int id , int l , int r , int pos , int le , int cnt){
    if(l == r){
        if(st[id].max_l == le){
            st[id].num += cnt;
        }
        if(st[id].max_l < le){
            st[id].num = cnt;
            st[id].max_l = le;
        }
        return;
    }
    int mid = l + r;
    mid >>= 1;
    if(pos <= mid){
        update(id << 1 , l , mid , pos , le , cnt);
    }else{
        update(id << 1 | 1 , mid + 1 , r , pos , le , cnt);
    }
    st[id].max_l = max(st[id << 1].max_l , st[id << 1 | 1].max_l);
    st[id].num =0;
    if(st[id].max_l == st[id << 1].max_l){
        st[id].num += st[id << 1].num;
    }
    if(st[id].max_l == st[id << 1 | 1].max_l){
        st[id].num += st[id << 1 | 1].num;
    }
}
item get(int id , int l , int r , int u , int v){
    if(l > r){
        return {0 , 0};
    }
    if(l > v || r < u){
        return {0 , 0};
    }
    if(u <= l && r <= v){
        return st[id];
    }
    int mid = l + r;
    mid >>= 1;
    item k ;
    item g = get(id << 1 , l , mid , u , v);
    item h = get(id << 1 | 1 , mid + 1 , r , u , v);
    k.max_l = max(g.max_l , h.max_l);
    k.num = (g.num * (g.max_l == k.max_l)) + (h.num * (h.max_l == k.max_l));
    return k;
}
void rebuild(int id , int l , int r){
    st[id].max_l = 0;
    st[id].num = 0;
    if(l == r){
        return ;
    }
    int mid = l + r;
    mid >>= 1;
    rebuild(id << 1 , l , mid);
    rebuild(id << 1 | 1 , mid + 1 , r);
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    freopen("new.inp" , "r" , stdin);
    freopen("new.out" , "w" , stdout);
    cin >> st1;
    cin >> st2;
    for(int i = 1 ; i <= st1.size() ; i ++){
        base[st1[i - 1] - 'a'].push_back(i);
    }
    for(int i = 0 ; i <= 29 ; i ++){
        if(base[i].size()){
            sort(base[i].begin() , base[i].end());
            reverse(base[i].begin() , base[i].end());
        }
    }

    for(int i = 1 ; i <= st2.size() ; i ++){
        
        for(int j : base[st2[i - 1] - 'a']){
            n ++;
            new_arr[n] = j;
        }
    }
    rebuild(1 , 1 , st1.size());
    for(int i = 1 ; i <= n ; i ++){
        item get_res = get(1 , 1 , st1.size() , 1 , new_arr[i] - 1);
        if(get_res.max_l == 0){
            get_res.num = 1;
        }
        update(1 , 1 , st1.size()  , new_arr[i] , get_res.max_l + 1 , get_res.num);
    }
    if(st[1].max_l != st2.size()){
        cout << 0 << '\n';
        return 0;
    }
    cout << st[1].num;
    return 0;
}
// dp bottom up 
/*
class Solution {
public:
    int numDistinct(string s, string t) {
        int m = s.size(), n = t.size(), mod = 1e9+7;
        if(m < n) return 0;
        vector<vector<int>> dp(m, vector<int>(n, 0));
        dp[0][0] = s[0]==t[0];
        for(int i = 1; i < m; i++) {
            if(s[i] == t[0]) dp[i][0] = (dp[i-1][0]%mod + 1)%mod;
            else dp[i][0] = dp[i-1][0];
        }
        
        for(int i = 1; i < m; i++) {
            for(int j = 1; j < n; j++) {
                if(s[i] == t[j]) dp[i][j] = (dp[i-1][j]%mod + dp[i-1][j-1]%mod)%mod;
                else dp[i][j] = dp[i-1][j];
            }
        }
        return dp[m-1][n-1];
    }
};
*/
