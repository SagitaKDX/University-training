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
const ll MAXQ = 1e5 + 7;
const ll INF = 1e18 + 7;

struct edge{
    int u , v ;
    ll val;
};

edge E[MAXN];
int n , m , k;
vector<pair<int , ll>> adj[MAXN];
int a[MAXN] , trace[MAXN] , sz[MAXN];
ll dis[MAXN];
bool cmp(edge u , edge v){
    return u.val < v.val;
}
int findpar(int u){
    return a[u] < 0 ? u : a[u] = findpar(a[u]);
}

bool join(int u , int v){
    u = findpar(u) , v = findpar(v);
    if(u == v){
        return false;
    }
    if(a[u] > a[v]){
        swap(u , v);
    }
    a[u] += a[v];
    a[v] = u;
    return true;
}

signed main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    // freopen("new.inp" , "r" , stdin);
    // freopen("new.out" , "w" , stdout);
    cin >> n >> m;
    int u , v ;
    ll w;
    for(int i = 1 ; i <= m ; i ++){
        cin >> u >> v >> w;
        adj[u].push_back({v , w});
        adj[v].push_back({u , w});
        E[i].u = u;
        E[i].v = v;
        E[i].val = w;
    }

    cin >> k;
    for(int i = 1 ; i <= n ; i ++){
        trace[i] = i; 
        a[i] = -1;
        dis[i] = INF;
    }
    priority_queue<pair<ll , int>> qu;
    for(int i = 1 ; i <= k ; i ++){
        cin >> a[i];
        dis[a[i]] = 0;
        qu.push({0 , a[i]});
        trace[a[i]] = a[i];
        a[i] = -1;
    }
    while(!qu.empty()){
        u = qu.top().second; 
        w = -1 * qu.top().first;
        qu.pop();
        if(dis[u] != w){
            continue;
        }
        for(pair<int , int> v : adj[u]){
            if(dis[v.first] > dis[u] + v.second){
                dis[v.first] = dis[u] + v.second;
                trace[v.first] = trace[u];
                qu.push({-dis[v.first] , v.first});
            }
        }
    }
    for(int i = 1 ; i <= m ; i ++){
        E[i] = {trace[E[i].u] , trace[E[i].v] ,1ll * dis[E[i].u] + 1ll * dis[E[i].v] + E[i].val};
    }
    sort(E + 1, E + 1 + m , cmp);
    ll res = 0;
    for(int i = 1 ; i <= m ; i ++){
        if(join(E[i].u , E[i].v)){
            res += E[i].val;
        }
    }
    cout << res + dis[1];
    
    return 0;    
    
}
