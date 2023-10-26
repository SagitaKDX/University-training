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
const ll MOD = 1e9 + 7;
const ll MAXN = 2e5 + 7;
int n ;
struct item{
    int v;
    int c1 , c2;
    int id;
};
vector<item> adj[MAXN];
int depth[MAXN];
ll w[MAXN] , z;
int T[MAXN][20];
ll num[MAXN];
ll edge_val[MAXN];
ll sum = 0;
void DFS(int u , int pre){  
    T[u][0] = pre;
    depth[u] = depth[pre] + 1;
    for(int i = 1 ; i <= 19 ; i ++){
        T[u][i] = T[T[u][i - 1]][i - 1];
    }
    for(item  v : adj[u]){
        if(v.v == pre){
            continue;   
        }
        DFS(v.v , u);
    }
}
int LCA(int u , int v){
    if(depth[u] <= depth[v]){
        swap(u , v);
    }
    for(int i = 19 ;i >= 0 ; i --){
        if(depth[T[u][i]] >= depth[v]){
            u = T[u][i];
        }
    }
    if(u == v){
        return u;
    }
    for(int i = 19; i >= 0 ; i--){
        if(T[u][i] != T[v][i]){
            u = T[u][i];
            v = T[v][i];
        }
    }
    return T[u][0];
}

int update(int u , int pre ){
    int cur =  num[u];
    for(item v : adj[u]){

        if(v.v == pre){
            continue;
        }
        z = update(v.v , u);
        if(v.c1 * z < v.c2){
            edge_val[v.id] = v.c1;
        }else{
            edge_val[v.id] = 0;
            sum += v.c2;
        }
        cur += z;
    }
    return cur;
}
void build_new_tree(int u , int pre){
    for(item v : adj[u]){
        if(v.v == pre){
            continue;
        }
        w[v.v] = w[u] + edge_val[v.id];
        build_new_tree(v.v , u);
    }
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen("new.inp", "r", stdin);
    freopen("new.out" , "w" , stdout);
    cin >> n;
    int u , v , c1 , c2;
    for(int i = 1 ; i <=  n - 1 ; i ++){
        cin >> u >> v >> c1 >> c2 ;
        adj[u].push_back({v ,c1 , c2 , i});
        adj[v].push_back({u , c1 , c2 , i});
    }
    DFS(1 , 0);
    int lca = 0;
    for(int i  = 1 ; i <= n - 1; i ++){
        lca = LCA(i , i + 1);
        if(lca != i && lca != i + 1){
            num[lca] -=2;
            num[i] ++;
            num[i + 1] ++;
        }else{
            num[lca] --;
            if(i != lca){
                num[i] ++;
            }else{
                num[i + 1] ++;
            }
        }
    }
    update(1 ,0);
    build_new_tree(1 , 0);
    for(int i = 1 ; i <= n - 1 ; i ++){
        lca = LCA(i , i + 1);
        sum += w[i] + w[i + 1] - 2 * w[lca] ;
    }
    cout << sum << '\n';

    return 0;
}
/* becareful :
- long long
- check if array size limit
- check if overflow
- check if index negative
- check if index out of bound
- check if special testcase
- check if input is invalid
- check if output is invalid
- check if the variables type is duplicate
*/