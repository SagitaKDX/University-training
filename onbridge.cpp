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
#define ll long long
const ll MAXN = 5e4 + 7;
const ll INF = 1e18 + 7;

struct item{
    int u , v;
};

struct segment_tree{
    int laz , val;
}st[MAXN * 4];


vector<item> canh;
vector<int>adj[MAXN];
int n , m;
int depth[MAXN] , cnt[MAXN] , chainidx[MAXN] , chainhead[MAXN] , posinbase[MAXN];
int T[MAXN][18] , par[MAXN];
int nchain , nbase;
int findpar(int u){
    return par[u] < 0 ?  u : par[u] = findpar(par[u]);
}

bool join(int u , int v){
    u = findpar(u);
    v = findpar(v);
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

void DFS(int u , int pre){
    T[u][0] = pre;
    depth[u] = depth[pre] + 1;
    for(int i = 1 ; i <= 17 ; i ++){
        T[u][i] = T[T[u][i - 1]][i - 1];
    }
    cnt[u] = 1;
    for(int v : adj[u]){
        if(v != pre){
            DFS(v , u);
            cnt[u] += cnt[v];
        }
    }
}

int lca(int u , int v){
    if(depth[u] < depth[v]){
        swap(u , v);
    }
    for(int i = 17 ; i >= 0 ; i --){
        if(depth[T[u][i]] >= depth[v]){
            u = T[u][i] ;
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

void build(int id , int l , int r){
    st[id].laz = 0;
    if(l == r && l != 1){
        st[id].val = 1;
        return ;
    }
    if(l == r && l == 1){
        st[id].val = 0;
        return ;
    }
    int mid = l + r;
    mid >>= 1;
    build(id << 1 , l , mid);
    build(id << 1 | 1 , mid + 1 , r);
    st[id].val = st[id << 1].val + st[id << 1 | 1].val;
}

void pushdown(int id){
    st[id].laz = 0;
    st[id << 1].laz = 1;
    st[id << 1].val = 0;
    st[id << 1 | 1].laz = 1;
    st[id << 1 | 1].val = 0;
}

void update(int id , int l , int r , int u , int v){
    if(l > v || u > r || u > v){
        return ;
    }
    if(u <= l && r <= v){
        st[id].val = 0;
        st[id].laz = 1;
        return;
    }
    if(st[id].laz){
        pushdown(id);
    }
    int mid = l + r;
    mid >>= 1;
    update(id << 1 , l , mid , u , v);
    update(id << 1 | 1 , mid + 1 , r , u , v);
    if(st[id].val != 0){
        st[id].val = st[id << 1].val + st[id << 1 | 1].val;
    }
}

int get(int id , int l , int r , int u , int v){
    if(u > v || l > v || r < u){
        return 0;
    }
    if(u <= l && r <= v){
        return st[id].val;
    }
    if(st[id].laz){
        pushdown(id);
    }
    int mid = l + r;
    mid >>= 1;
    return get(id << 1 , l , mid , u , v) + get(id << 1 | 1 , mid + 1 , r , u , v);
}


void HLD(int u , int pre){
    if(chainhead[nchain] == 0){
        chainhead[nchain] = u;
    }
    chainidx[u] = nchain;
    posinbase[u] = ++nbase;
    int maxvt = -1;
    for(int v : adj[u]){
        if(v != pre){
            if(maxvt == -1 || cnt[maxvt] < cnt[v]){
                maxvt = v;
            }
        }
    }
    if(maxvt != -1){
        HLD(maxvt , u);
    }
    for(int v : adj[u]){
        if(v != pre && v != maxvt){
            nchain ++;
            HLD(v , u);
        }
    }
}

int findup(int u , int v){
    int uchain = chainidx[u];
    int vchain = chainidx[v];
    int sum = 0;
    while(true){
        if(uchain == vchain){
            sum += get(1 , 1 , n ,posinbase[v] + 1 , posinbase[u]);
            update(1 , 1 , n , posinbase[v] + 1 , posinbase[u]);
            
            return sum;
        }
        sum += get(1 , 1 , n , posinbase[chainhead[uchain]] , posinbase[u]);
        update(1 , 1 , n , posinbase[chainhead[uchain]] , posinbase[u]);
        u = T[chainhead[uchain]][0];
        uchain = chainidx[u];        
    }
    return 0;
}

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    freopen("new.inp" , "r" , stdin);
    freopen("new.out" , "w" , stdout);
    int t;
    cin >> t;
    int cur = t;
    while(t--){
        read(n); read(m);
        int u , v;
        canh.clear();
        for(int i = 1 ; i <= n ; i ++){
            cnt[i] = 0;
            par[i] = -1;
            adj[i].clear();
            chainhead[i] = 0;
        }
        int num = n;
        for(int i = 1 ; i <= m ; i ++){
            read(u); read(v);
            u ++;
            v ++;
            if(join(u , v)){
                adj[u].push_back(v);
                adj[v].push_back(u);
                num --;
            }
            canh.push_back({u , v});
        }
        DFS(1 , 0);
        nchain = 0;
        nbase = 0;
        HLD(1 , 0);
        build(1 , 1 , n);
        for(int i = 1 ; i <= n ; i ++){
            par[i] = -1;
        }
        int bridge = 0;
        for(int i = 1 ; i <= m ; i ++){
            if(join(canh[i - 1].u , canh[i - 1].v)){
                bridge ++;
            }else{
                int LCA = lca(canh[i - 1].u , canh[i - 1].v);
                bridge -= findup(canh[i - 1].u , LCA) + findup(canh[i - 1].v , LCA);
            }
            write(bridge);
            putchar('\n');
        }
    }
    return 0;    
}
