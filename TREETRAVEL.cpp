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
const ll MOD = 1e9 + 7;
const ll INF = 1e18 + 7;
const ll MAXN = 1e5 + 7;
int  n;
vector<int > adj[MAXN];
int par[MAXN];
int depth[MAXN];
int con[MAXN];
int nbase , nchain = 0;
int posinbase[MAXN] , chainidx[MAXN] , chainhead[MAXN];
void DFS(int u , int pre){
    con[u] = 1;
    par[u] = pre;    
    for(int v  : adj[u]){
        if(v == pre) continue;
        DFS(v , u);
        con[u] += con[v];
    }
}
struct item{
    ll val , laz;
} st[MAXN * 4];
void push_down(int id){
    st[id << 1].val += st[id].laz;
    st[id << 1].val %= MOD;
    st[id << 1 | 1].val += st[id].laz;
    st[id << 1 | 1].val %= MOD;
    st[id << 1].laz += st[id].laz;
    st[id << 1].laz %= MOD;
    st[id << 1 | 1].laz += st[id].laz;
    st[id << 1 | 1].laz %= MOD;
    st[id].laz = 0;
}
void update(int id , int l , int r , int u , int v , ll val){
    if(l > v || r < u){
        return;
    }
    if(u <= l && r <= v){
        st[id].laz += val;
        st[id].laz %= MOD;
        st[id].val += val;
        st[id].val %= MOD;
        return;
    }
    int mid = l + r;
    mid >>= 1;
    push_down(id);
    update(id << 1 , l , mid , u , v , val);
    update(id << 1 | 1 , mid + 1 , r , u ,v , val);
}

ll get(int id , int l , int r , int pos){
    if(l == r){
        return st[id].val;
    }
    int mid = l + r;
    mid >>= 1;
    push_down(id);
    if(pos <= mid){
        return get(id << 1 , l , mid , pos);
    }else{
        return get(id << 1 | 1  , mid + 1 , r , pos);
    }
    
}
void HLD(int u , int pre){
    if(chainhead[nchain] == 0){
        chainhead[nchain] = u;
    }
    chainidx[u] = nchain;
    posinbase[u] = ++nbase;
    int maxvt = -1;
    for(int v : adj[u]){
        if(v == pre) continue;
        if(maxvt == -1 || con[maxvt] < con[v]){
            maxvt = v;
        }
    }
    if(maxvt == -1){
        return;
    }
    HLD(maxvt , u);
    for(int v : adj[u]){
        if(v == pre || v == maxvt) continue;
        nchain ++;
        HLD(v , u);
    }
}


void findup(int u , int v , ll val){
    int uchain = chainidx[u];
    int vchain = chainidx[v];
     while(true){
        if(uchain == vchain){
            update(1 , 1 , n , posinbase[v] , posinbase[u] , val);
            break;
        }
        update(1 , 1 , nbase , posinbase[chainhead[uchain]] , posinbase[u] , val);
        u = par[chainhead[uchain]];
        uchain = chainidx[u];
    }
}

ll kq[MAXN];
signed main(){
    // ios_base::sync_with_stdio(false);
    // cin.tie(0);
    freopen("new.inp" , "r" , stdin);
    freopen("new.out" , "w" , stdout);
    read(n);
    int root;
    int x;
    for(int i = 1 ; i <= n ; i ++){
        read(x);
        if(x == 0){
            root = i;
        }else{
            adj[x].push_back(i);
            adj[i].push_back(x);
        }
    }
    DFS(root , 0);
    HLD(root , 0);
    for(int i  = 1 ; i <= n ; i ++){
        update(1 , 1,  n , posinbase[i] , posinbase[i] , 1);
    }
    ll val = 0;
    for(int i = 1 ; i <= n ; i ++){
        read(val);
        ll res = get(1 , 1 , n ,posinbase[val]);
        kq[val] = res;
        findup(val , root , res);
    }
    for(int i = 1 ; i <= n ; i ++){
        write(kq[i]); putchar(' ');
    }
    return 0;
}