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
const ll MAXN = 1e5 + 7 ;
const ll MOD = 1e9 + 7;
const ll INF = 1e18 + 7;
int n , q , z;
vector<int> adj[MAXN];
int endd[MAXN];
int start[MAXN];
int timeDFS;
int val[MAXN];
struct query{
    int type , u;
    int l , r;
} qu[MAXN];
int b[MAXN]; 

struct segtree{
    int val;
    int laz;
};
segtree st[MAXN * 4];

void DFS(int u , int par){
    timeDFS++;
    start[u] = timeDFS;
    for(int v : adj[u]){
        if( v != par){
            DFS(v , u);
        }
    }    
    endd[u] = timeDFS;
}
void rebuild(int id , int l , int r){
    if(l == r){
        st[id].val = b[l];
        st[id].laz = 0;
        return;
    }
    st[id].laz = 0;
    int mid = l + r;
    mid >>= 1;
    rebuild(id << 1 , l , mid);
    rebuild(id << 1 | 1 , mid + 1 , r);
    st[id].val = st[id << 1].val + st[id << 1 | 1].val;
}

void push_down(int id , int l , int r , int mid){
    if(st[id].laz == 1){
        st[id << 1].val = mid - l + 1;;
        st[id << 1].laz = 1;
        st[id << 1 | 1].val = r - mid;
        st[id << 1 | 1].laz = 1;
    }else{
        st[id << 1].val = 0;
        st[id << 1].laz = -1;
        st[id << 1 | 1].val = 0;
        st[id << 1 | 1].laz = -1;
    }
    st[id].laz = 0;
}

void update(int id , int l , int r , int u , int v , int type){
    if(l > v || r < u){
        return ;
    }
    if(u <= l && r <= v){
        if(type == 1){
            st[id].val = r - l + 1;
            st[id].laz = 1;
        }else{
            st[id].val = 0;
            st[id].laz = -1;
        }
        return;
    }
    int mid = l + r;
    mid >>= 1;
    if(st[id].laz != 0){
        push_down(id , l , r , mid);   
    }
    update(id << 1 , l , mid , u , v , type);
    update(id << 1 | 1 , mid + 1 , r , u , v , type);
    st[id].val = st[id << 1].val + st[id << 1 | 1].val;
}

int get(int id , int l , int r , int u , int v){
    if(l > v || r < u){
        return 0;
    }
    if(u <= l && r <= v){
        return st[id].val;
    }
    int mid = l + r;
    mid >>= 1;
    if(st[id].laz != 0){
        push_down(id , l , r , mid);
    }
    return get(id << 1 , l , mid , u , v) + get(id << 1 | 1 , mid + 1 , r , u , v);
}

bool check(int cur , int pos){
    for(int i = 1 ; i <= n ; i ++){
        b[start[i]] = val[i] < cur ? 0 : 1;
    }
    rebuild(1 , 1 , n);
    int num = 0;
    for(int i = 1 ; i <= q ; i ++){
        if(qu[i].type == 1){
            num = get(1 , 1, n , qu[i].l , qu[i].r);
            // cout << num << '\n';
            if(num <  qu[i].r - qu[i].l + 1){
                update(1 , 1 , n , qu[i].r - num + 1 , qu[i].r , 1);
                update(1 , 1 , n , qu[i].l , qu[i].r - num , -1);
            }
        }else{
            num = get(1 , 1 , n , qu[i].l , qu[i].r);
            if(num < qu[i].r - qu[i].l + 1 ){
                update(1 , 1 , n , qu[i].l , qu[i].l + num - 1 , 1);
                update(1 , 1 , n , qu[i].l + num , qu[i].r , -1);
            }
        }
    }
    return get(1, 1, n , pos , pos) == 1;
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    // freopen("new.inp" , "r" , stdin);
    // freopen("new.out" , "w" , stdout);
    int u , v;
    cin >> n ;
    for(int i = 1 ; i <= n ; i ++){
        cin >> val[i];
    }
    for(int i = 1 ; i <= n - 1 ; i ++){
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    DFS(1 , 0);
    cin >> q;
    for(int i =  1 ; i <= q ; i ++){
        cin >> qu[i].type >> qu[i].u;
        qu[i].l = start[qu[i].u];
        qu[i].r = endd[qu[i].u]; 
    }
    cin >> z;
    while(z--){
        cin >> u;
        int l = 1;
        int r = MOD - 7;
        int save = -1;
        while(l <= r){
            int mid = l + r;
            mid >>= 1;
            if(check(mid , u)){
                l = mid + 1;
                save = mid;
            }else{
                r = mid - 1;
            }
        }
        cout << save << '\n';
    }
    return 0;
}