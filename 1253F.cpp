// #pragma GCC optimize("Ofast")
// #pragma optimize("unroll-loops")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>

using namespace std;
#define ll long long
#define ld long double

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

const ll MAXN = 1e5 + 7;
const ll MAXQ = 3e5 + 7;
const ll INF = 1e18 + 7;


struct Edge{
    int u , v;
    ll w;
};
Edge E[MAXQ];

bool cmp(Edge u , Edge v){
    return u.w < v.w;
}

int n , m , k , q;
vector<pair<int , ll>> adj[MAXN];
ll dis[MAXN] , par[MAXN];
int trace[MAXN];
int findpar(int u){
    return par[u] < 0 ? u : par[u] = findpar(par[u]);
}

bool joint(int u , int v){
    u = findpar(u); v = findpar(v);
    if(u == v){
        return false;
    }
    if(par[u] > par[v]){
        swap(u , v);
    }
    par[u] += par[v];
    par[v] = u;
    return true;
}

int T[MAXN][20] , depth[MAXN];
ll max_w[MAXN][20];

void DFS(int u , int pre){
    T[u][0] = pre;
    depth[u] = depth[pre] + 1;
    for(int i = 1 ; i <= 18 ; i ++){
        T[u][i] = T[T[u][i - 1]][i -1];
        max_w[u][i] = max(max_w[T[u][i - 1]][i - 1] , max_w[u][i - 1]);
    }
    for(pair b : adj[u]){
        if(b.first != pre){
            max_w[b.first][0] = b.second;
            DFS(b.first , u);
        }
    }
}

ll LCA(int u , int v){
    if(depth[u] <= depth[v]){
        swap(u , v);
    }
    ll res = 0;
    for(int i = 18 ; i >= 0 ; i --){
        if(depth[T[u][i]] >= depth[v]){
            maximize(res , max_w[u][i]);
            u = T[u][i];
        }
    }
    if(u == v){
        return  res;
    }
    for(int i = 18 ; i >= 0 ; i --){
        if(T[u][i] != T[v][i]){
            maximize(res , max_w[u][i]);
            maximize(res , max_w[v][i]);
            u = T[u][i];
            v = T[v][i];
        }
    }
    maximize(res , max_w[u][0]);
    maximize(res , max_w[v][0]);
    return res;
}

signed main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    freopen("new.inp" , "r" , stdin);
    freopen("new.out" , "w" , stdout);
    cin >> n >> m >> k >> q;
    int u , v;
    ll w;
    for(int i = 1 ; i <= m ; i ++){
            cin >> u >> v >> w;
            adj[u].push_back({v , w});
            adj[v].push_back({u , w});
            E[i] ={u , v , w};
    }   
    par[0] = -1;
    for(int i = 1 ; i <= n ; i ++){
        dis[i] = INF;
        par[i] = -1;
        trace[i] = 0;
    }
    priority_queue<pair<ll , int>> qu;
    for(int i = 1 ; i <= k ; i ++){
        dis[i] = 0;
        qu.push({0 , i});
        trace[i] = i;
    }
    while(!qu.empty()){
        u = qu.top().second;
        w = qu.top().first * -1;
        qu.pop();
        if(dis[u] != w){
            continue;
        }
        for(pair<int , ll> b : adj[u]){
            if(dis[b.first] > dis[u] + b.second){
                dis[b.first] = dis[u] + b.second;
                qu.push({-dis[b.first] , b.first});
                trace[b.first] = trace[u];
            }
        }
    }
    for(int i = 1 ; i <= m ; i ++){
        if(trace[E[i].u] != 0 && trace[E[i].v] != 0){
            E[i].w = dis[E[i].u] + dis[E[i].v] + E[i].w;
            E[i].u = trace[E[i].u];
            E[i].v = trace[E[i].v];
        }else{
            E[i].u = 0;
            E[i].w = INF;
        }
    }   
    sort(E + 1 , E + 1 + m , cmp);   
    for(int i = 1 ; i <= m ; i ++){
        if(E[i].w != INF){
            if(joint(E[i].u , E[i].v)){
                if(trace[E[i].u] != -1){
                    adj[E[i].u].clear();
                    trace[E[i].u] = -1;
                }
                if(trace[E[i].v] != -1){
                    adj[E[i].v].clear();
                    trace[E[i].v] = -1;
                }
                adj[E[i].u].push_back({E[i].v , E[i].w});
                adj[E[i].v].push_back({E[i].u , E[i].w});
            }
        }       
    }
    DFS(1 , 0);
    for(int i = 1 ; i <= q ; i ++){
        cin >> u >> v;
        cout << LCA(u , v) << '\n';
    }
    
    return 0;    
    
}
