#include <bits/stdc++.h>

using namespace std;
typedef long long  ll;
typedef long double ld;

typedef pair<int, int> pi;
typedef pair<ll, int> pli;
typedef pair<int, ll> pil;
typedef pair<ll,ll> pl;
typedef pair<ld,ld> pd;

typedef vector<int> vi;
typedef vector<bool> vb;
typedef vector<ld> vd;
typedef vector<ll> vl;
typedef vector<pi> vpi;
typedef vector<pl> vpl;
typedef vector<pli> vli;
typedef vector<pil> vil;

#define FORE(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); i++)
#define BIT(x, i) (((x) >> (i)) & 1)
#define MASK(i) (1LL << (i))
#define mp make_pair
#define pb push_back
#define f first

// #define s second
#define lb lower_bound
#define ub upper_bound
#define sz(x) (int)x.size()
#define ALL(x) begin(x), end(x)

void minimize(long long &x,long long y){
   if(x>y){
      x=y;
   }
}

void maximize(long long &x,long long y){
    if(x<y){
        x=y;
    }
}

template <typename T> inline void read(T & x)
{
    char c; bool nega=0;
    while((!isdigit(c=getchar()))&&c!='-');
    if(c=='-')
    {
        c=getchar();
        nega=1;
    }
    x=c-48;
    while(isdigit(c=getchar()))
    {
        x=x*10+c-48;
    }
    if(nega) x=-x;
}
template <typename T> void Write(T x) {if (x > 9) Write(x/10); putchar(x%10+48);}
template <typename T> void write(T x) {if (x < 0) {putchar('-'); x = -x;} Write(x);}

long long pow_mod(long long a, long long b, long long m) {
     long long res = 1;
     while(b){
            res = res * (b & 1 ? a : 1) % m;
            a = a * a % m; b >>= 1;
     }
     return res;
}

long long GCD(long long a , long long b){
    while(b != 0 ){
         a = a % b;
         long long tmp = a;
         a = b;
         b = tmp;
    }
    return a;
}

long long minn(long long a ,long long b , long long c ,long long d){
    long long res = a;
    if(res > d) res = d;
    if(res > b) res = b;
    if(res > c) res = c;
    return res;
}
const ll INF = 1e5 + 7;
const ll MAXN = 1e5 + 7;
const ll MOD = 1e9;
int n , m;
vector<int>adj[MAXN] , adj2[MAXN] , cur[MAXN] , toposort;
int num[MAXN] , low[MAXN] , dd[MAXN] ,ans = 0;
stack<int>st;
int pos[MAXN];
bool is_strong_conectivity[MAXN];
struct item{
    ll val ;
    bool check;
};
item dp[MAXN];
void dfs(int u) {
    num[u] = ++num[0];
    low[u] = INF;
    st.push(u);
    for (auto v : adj[u]) if (!dd[v]) {
            if (num[v]) low[u] = min(low[u], num[v]);
            else {
                dfs(v);
                low[u] = min(low[u], low[v]);
            }
        }
    if (low[u] < num[u]) return;
    ans++;
    for (;;) {
        int k = st.top();
        st.pop();
        dd[k] = 1;
        pos[k] = ans;
        cur[ans].push_back(k);
        if (k == u) return ;
    }
}
void DFS(int u){
    dd[u] = 1;
    for(int v : adj2[u]){
        if(!dd[u]) DFS(u);
    }
    toposort.push_back(u);
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    freopen("new.inp" , "r" , stdin);
    freopen("new.out" , "w" , stdout);
    cin >> n >> m;
    int u , v;
    for(int i = 1 ; i <= m ; i ++){
        cin >> u >> v;
        adj[u].push_back(v);
    }
    for(int u = 1 ; u <= n ; u ++){
        if(!dd[u]) dfs(u);
    }     
    for(int i = 1 ; i <= n ; i ++){
        dd[i] = 0;
        dp[i].check = false;
    }
    for(int i = 1 ; i <= ans ; i ++){
        if(cur[i].size() > 1){
            is_strong_conectivity[i] = true;
            dp[i].check = true;
        }else{
            dp[i].check = false;
        }
        for(int v : cur[i]){
            for(int u : adj[v]){
                if(pos[v] == pos[u]) continue;
                adj2[pos[v]].push_back(pos[u]);
            }
        }
    }
    for(int i = 1 ; i <= ans ; i ++){
        if(!dd[i]){
            DFS(i);
        }
    }
    reverse(toposort.begin() , toposort.end());
    dp[pos[1]].val = 1;
    dp[pos[1]].check = is_strong_conectivity[pos[1]];
    for(int i = 0 ; i < toposort.size() ; i ++){
        for(int v : adj2[toposort[i]]){
            dp[v].val += dp[toposort[i]].val;
            dp[v].val %= MOD;
            if(dp[toposort[i]].val != 0)
                dp[v].check |=  dp[toposort[i]].check;
        }
    }
    if(dp[pos[n]].check){
        cout << "INFINITE PATHS" << '\n';
    }else{
        cout << dp[pos[n]].val % MOD;
    }
    return 0;
}