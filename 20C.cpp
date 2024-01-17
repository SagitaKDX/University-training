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
 
#define BIT(x, i) (((x) >> (i)) & 1)
#define MASK(i) (1LL << (i))
#define mp make_pair
#define pb push_back
#define f first
 
#define s second
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
const ll MAXN = 1e6 + 7 ;
const ll MOD = 1e9 + 7;
const ll INF = 1e18 + 7;
int n ,m;
vector<pair<int , int >> adj[MAXN];
ll dis[MAXN];
bool vis[MAXN];
int trace[MAXN];

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    freopen("new.inp" , "r" , stdin);
    freopen("new.out" , "w" , stdout);
    cin >> n >> m ;
    int u , v , w;
    for(int i = 1 ; i <= m ; i ++){
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u , w});
    }
    for(int i = 1 ; i <= n ; i ++){
        dis[i] = INF;
        trace[i] = -1;
    }
    dis[1] = 0;
    priority_queue<pair<ll , ll>> qu;
    qu.push({0 , 1});
    while(!qu.empty()){
        u = qu.top().second;
        qu.pop();
        if(vis[u]){
            false;
        }
        for(auto b : adj[u]){
            if(dis[b.first] > dis[u] + b.second){
                dis[b.first] = dis[u] + b.second;
                trace[b.first] = u;
                qu.push({- dis[b.first] , b.first});
            }
        }
    }
    if(dis[n] == INF){
        cout << -1 << '\n';
        return 0;
    }
    vector<int> path;
    int cur = n;
    while(cur != -1){
        path.push_back(cur);
        cur = trace[cur];
    }
    reverse(path.begin() , path.end());
    for(int v : path){
        cout << v << " ";
    }
    return 0;
}