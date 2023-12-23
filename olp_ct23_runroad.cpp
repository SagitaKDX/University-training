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

const ll MAXN = 2e5 + 7;
const ll INF = 1e18 + 7;
int n , t;
ll h[MAXN] ;
vector<int > adj[MAXN];
int T[MAXN][18];
int depth[MAXN];
ll maximum[MAXN][18];
void DFS(int u , int pre){
    depth[u] = depth[pre] + 1;
    T[u][0] = pre;
    for(int i = 1 ; i <= 17 ; i ++){
        T[u][i] = T[T[u][i - 1]][i - 1];
    }
    maximum[u][0] = max(h[u] , h[pre]);
    for(int i = 1 ; i <= 17 ; i ++){
        maximum[u][i] = max(maximum[u][i - 1] , maximum[T[u][i - 1]][i - 1]);
    }
    for(int v : adj[u]){
        if(v != pre){
            DFS(v , u);
        }
    }
}
int findlca(int u , int v){
    if(depth[u] <= depth[v]){
        swap(u , v);
    }
    for(int i = 17 ; i >= 0 ; i --){
        if(depth[T[u][i]] >= depth[v]){
            u = T[u][i];
        }
    }
    if(u == v){
        return u;
    }
    for(int i = 17 ; i >= 0 ; i --){
        if(T[u][i] != T[v][i]){
            u = T[u][i];
            v = T[v][i];
        }
    }
    return T[u][0];
}
ll findmax(int u , int v){
    if(depth[u] <= depth[v]){
        swap(u , v);
    }
    ll res = max(h[u] , h[v]);
    for(int i = 17 ; i >= 0 ; i --){
        if(depth[T[u][i]] >= depth[v]){
            res = max(res , maximum[u][i]);
            u = T[u][i];
        }
    }
    if(u == v){
        return res;
    }
    for(int i = 17 ; i >= 0; i --){
        if(T[u][i] != T[v][i]){
            res = max(res , maximum[u][i]);
            res = max(res , maximum[v][i]);
            u = T[u][i];
            v = T[v][i];
        }
    }
    res = max(res ,h[T[u][0]]);
    return res;
}
ll solve(int u , int v){
    return depth[u] + depth[v] - 2 * depth[findlca(u , v)];
}
signed main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    freopen("new.inp" , "r" , stdin);
    freopen("new.out" , "w" , stdout);
    cin >> n >> t;
    for(int i = 1 ; i <= n ; i ++){
        cin >> h[i];    
    }
    int u , v;
    for(int i = 1 ; i < n ; i ++){
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    memset(maximum , -INF , sizeof(maximum));
    h[0] = - INF;
    DFS(1 , 0);
    ll dis = 0;
    for(int i = 3 ; i <= n ; i ++){
        for(int j = i - 1 ; j >= 1 ; j --){
            for(int k = j - 1 ; k >= 1 ; k --){
                ll res = max({findmax(i , j) , findmax(j , k) , findmax(k , i)});
                if(res == t){
                    dis += solve(i , j) + solve(j , k) + solve(k , i);
                    // cout << i << " " << j << " " << k <<" " << solve(i , j) + solve(j , k) + solve(k , i)<< '\n';     
                }
            }
        }
    }
    cout << dis << '\n';
    return 0;    
}