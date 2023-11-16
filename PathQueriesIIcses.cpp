// #pragma GCC optimize("Ofast")
// #pragma optimize("unroll-loops")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native") 
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
const ll INF = 1e18 + 7;
const ll MAXN = 2e5 + 7;
int n , q;
vector<int > adj[MAXN];
int depth[MAXN] , con[MAXN] , nchain , chainhead[MAXN] , chainidx[MAXN] , posinbase[MAXN] , nbase;
struct item{
    int val ;
};
int T[MAXN][18];
int a[MAXN];
item st[MAXN * 4];
int lca(int u ,int v){
         if(depth[u] < depth[v])
		 swap(u, v);
		 for(int i = 17; i >= 0; i--)
		 if(depth[T[u][i]] >= depth[v])
		 u = T[u][i];
		 if(u == v) return u;
		 for(int i = 17; i >= 0; i--)
			 if(T[u][i] != T[v][i]) {
				 u = T[u][i];
				 v = T[v][i];
			 }
		 return T[u][0];
}
 
void update(int id , int l , int r ,int pos ,ll val){
    
    if(l == r){
        st[id].val += val;
        return ;
    }
    int mid = l + r;
    mid >>= 1;
    if(pos <= mid)
        update(id << 1 , l , mid ,pos , val);
    if(pos > mid)
        update(id << 1 | 1 , mid + 1 , r , pos , val);
    st[id].val = max(st[id << 1].val , st[id << 1 | 1].val);
}
 
ll get_val(int id , int l , int r , int u , int v){
    if(l > v || r < u){
        return 0;
    }
    if(u <= l && r <= v){
        return st[id].val;
    }
    int mid = l + r;
    mid >>= 1;
    return max(get_val(id << 1 , l , mid , u , v)  , get_val(id << 1 | 1  , mid + 1 , r , u , v));
    
}
 
void DFS(int u , int pre){
    depth[u] = depth[pre] + 1;
    T[u][0] = pre;
    for(int i = 1 ; i <= 17 ; i ++){
        T[u][i] = T[T[u][i - 1]][i - 1];
    }
    con[u] = 1;
    for(int v : adj[u]){
        if(v == pre) continue;
        DFS(v , u);
        con[u] += con[v];
    }
}
void hld(int u){
    if(chainhead[nchain] == 0) chainhead[nchain] = u;
    chainidx[u] = nchain;
    posinbase[u] = ++nbase;
    update(1 , 1 , n , posinbase[u]  , a[u]);
    int maxvt = -1;
    for(int v : adj[u]){
        if(v == T[u][0]){
            continue;
        }
        if(maxvt == -1 || con[maxvt] < con[v]){
            maxvt = v;
        }
    }
    if(maxvt != -1){
        hld(maxvt);
    }
    for(int v : adj[u]){
        if(v == T[u][0] || v == maxvt){
            continue;
        }
        nchain ++;
        hld(v);
    }
}
int uchain , vchain;
void findup(int u , int v , int val){
    uchain = chainidx[u] ;
    vchain = chainidx[v];
    while(true){
        if(uchain == vchain){
            update(1 , 1 , n ,  posinbase[u] , val);
            break;
        }
    }
    return;
}
ll res = 0;
ll get_up(int u , int v){
    uchain = chainidx[u] ;
    vchain = chainidx[v];
    if(u == v) return a[u];
    res = 0;
    while(true){
        if(uchain == vchain){
            res = max(res , get_val(1 , 1 , n , posinbase[v] , posinbase[u] ));
            break;
        }
        res = max(res , get_val(1 , 1 , n , posinbase[chainhead[uchain]] , posinbase[u] ));
        u = T[chainhead[uchain]][0];
        uchain = chainidx[u];
    }
    return res;
}
signed main(){
    // ios_base::sync_with_stdio(false);
    // cin.tie(0);
    freopen("new.inp" , "r" , stdin);
    freopen("new.out" , "w" , stdout); 
    // cin >> n;
    read(n); read(q);
    int u , v;
    for(int i = 1 ; i <=n ; i ++){
        read(a[i]);
    }
    for(int i = 1  ; i <= n - 1; i ++){
        // cin >> u >> v;
        read(u); read(v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    DFS(1 ,  0);
    hld(1);
    int type , x,  y , z;
    ll cur1 , cur2 ;
    for(int i = 1 ; i <= q;  i ++){
        read(type); 
        if(type == 1){
            read(x); read(y);
            findup(x , x , y - a[x]);
            a[x] = y;
        }else{
            read(x); read(y);
            z = lca(x , y);
            cur1 =get_up(x , z); 
            cur2 = get_up(y , z);
            write(max(cur1 , cur2));
            putchar(' ');
        }
 
    }
    return 0;
}