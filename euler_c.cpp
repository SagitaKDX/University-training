#pragma GCC optimize("Ofast")
#pragma optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
 
using namespace std;
#define ll long long
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
const ll MAXN = 2e5 + 7 ;
const ll INF = 1e18;
const ll MOD = 1e9 + 7;
int n , q;
struct item{
    int f,s;
};
vector<item> adj[MAXN];
item edge[MAXN];
int T[MAXN][17];
int sz[MAXN];
int weight[MAXN] , depth[MAXN] ,nchain ,nbase , chainhead[MAXN] , chainidx[MAXN] , posinbase[MAXN];
ll st[MAXN * 4];
void update(int id , int l , int r , int pos , int val){
    if(l == r){
        st[id] = val;
        return;
    }
    int mid = l + r;
    mid >>= 1;
    if(pos <= mid){
        update(id << 1 , l , mid , pos , val);
    }else{
        update(id << 1 | 1 , mid + 1 , r , pos , val);
    }
    st[id] = st[id << 1] + st[id << 1 | 1];
}

ll get_sum(int id , int l , int r , int u , int v){
    if(l > v || r < u || l > r){
        return 0;
    }
    if(u <= l && r <= v){
        return st[id];
    }
    int mid = l + r;
    mid >>= 1;
    ll g = 0;
    ll h = 0;
    if(!(l > v || mid < u )){
         g = get_sum(id << 1 , l , mid , u , v);
    }
    if(!(mid + 1 > v || r < u)){
        g += get_sum(id << 1 | 1, mid + 1 , r , u , v);
    }
    return g;
}


void DFS(int u , int pre){
    T[u][0] = pre;
    depth[u] = depth[pre] + 1;
    for(int i = 1 ; i <= 16 ; i ++){
        T[u][i] = T[T[u][i - 1]][i - 1];
    }
    sz[u] = 1;
    for(item v : adj[u]){
        if(v.f != pre){
            weight[v.f] = v.s;
            DFS(v.f , u);
            sz[u] += sz[v.f];
        }
    }
}

int LCA(int u , int v){
    if(depth[u] <= depth[v]){
        swap(u , v);
    }
    for(int i = 16 ; i >= 0 ; i --){
        if(depth[T[u][i]] >= depth[v]){
            u = T[u][i];
        }
    }
    if(u == v){
        return u;
    }
    for(int i = 16 ; i >= 0 ; i --){
        if(T[u][i] != T[v][i]){
            u = T[u][i];
            v = T[v][i];
        }
    }
    return T[u][0];
}

int v;
void HLD(int u , int pre){
    if(chainhead[nchain] == 0){
        chainhead[nchain] = u;
    }
    chainidx[u] = nchain;
    posinbase[u] = ++nbase;
    update(1 , 1 , n , posinbase[u] , weight[u]);
    int maxvt = -1;
    for(int i = 0 ; i < adj[u].size() ; i ++){
        v = adj[u][i].f;
        if(v != pre){
            if(maxvt == -1 || sz[maxvt] < sz[v]){
                maxvt = v;
            }
        }
    }
    if(maxvt != -1){
        HLD(maxvt , u);
    }
    for(int i = 0 ; i < adj[u].size() ; i ++){
        v = adj[u][i].f;
        if(v != maxvt && v != pre){
            nchain ++;
            HLD(v , u);
        }
    }
}

int uchain , vchain;
ll sum = 0;
ll findup(int u , int v){
    uchain = chainidx[u];
    vchain = chainidx[v];
    sum = 0;
    while(true){
        if(uchain == vchain){
            sum += get_sum(1 , 1 , n , posinbase[v] + 1 , posinbase[u]);
            return sum;
        }
        sum += get_sum(1 , 1,  n , posinbase[chainhead[uchain]], posinbase[u]);
        u = chainhead[uchain];
        u = T[u][0];
        uchain = chainidx[u];
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    // freopen("new.inp" , "r" , stdin);
    // freopen("new.out" , "w" , stdout);
    read(n); 
    int u , v , w;
    for(int i = 1 ; i < n ; i ++){
        read(u); read(v); read(w);
        adj[u].push_back({v , w});
        adj[v].push_back({u , w});
        edge[i].f = u;
        edge[i].s = v;   
    }
    nchain = 1;
    DFS(1 , 0);
    HLD(1 , 0);
    read(q);
    int lca;
    ll sum = 0;
    for(int i = 1; i <= q; i ++){
        read(u); read(v); read(w);
        if(u == 1){
            if(T[edge[v].f][0] == edge[v].s){
                weight[edge[v].f] = w;

                update(1 , 1 , n , posinbase[edge[v].f] , weight[edge[v].f]);
            }else{
                weight[edge[v].s] = w;
                update(1 , 1 , n , posinbase[edge[v].s] , weight[edge[v].s]);
            }
        }else{
            lca = LCA(v , w);
            sum = findup(v , lca);
            sum += findup(w , lca);
            write(sum); putchar('\n');
        }
    }
    return 0;
}
