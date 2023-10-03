#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
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
const ll MOD = 1e9 + 7;
int par[MAXN];
int n , m , val[MAXN] , cnt[MAXN];
vector<int > adj[MAXN];
int chainhead[MAXN] , chainidx[MAXN] , posinbase[MAXN] , nchain , nbase;
ll ans[MAXN];

struct item{
    ll maxx ;
    int val;
    int laz;
} st[MAXN * 4];

int DFS(int u , int pre){
    cnt[u] = 1;
    par[u] = pre; 
    for(int v : adj[u]){
        if(v == pre) continue;
        cnt[u] += DFS(v , u);
    }
    return cnt[u];
}// done

void push_down(int id){
    int t = st[id].laz;
    st[id].laz = 0;
    st[id << 1].laz += t;
    st[id << 1].val += t;
    st[id << 1 | 1].laz += t;
    st[id << 1 | 1].val += t;
}// done push down lazy 

void update_val(int id , int l , int r , int pos_base , int node_val){
    if(l == r){
        st[id].val = node_val;
        st[id].maxx = -INF;
        st[id].laz = 0;
        return;
    }
    int mid = l + r;
    mid >>= 1;
    if(pos_base <= mid){
        update_val(id << 1 , l ,  mid , pos_base , node_val);
    }
    if(pos_base > mid){
        update_val(id << 1 | 1  , mid + 1 , r , pos_base , node_val);
    }
    st[id].maxx = -INF;
}// done cap nhat gia tri cac dinh 

void delete_node(int id , int l , int r , int pos_base ){
    if(l == r){
        st[id].maxx = pos_base;
        return;
    }
    int mid = l + r;
    mid >>= 1;
    if(st[id].laz != 0){
        push_down(id);
    }
    if(pos_base <= mid){
        delete_node(id << 1 , l , mid , pos_base);
    }else{
        delete_node(id << 1 | 1 , mid + 1 , r , pos_base);
    }
    st[id].maxx = max(st[id << 1].maxx , st[id << 1 | 1].maxx);
}// done xoa node u 

void update_range(int id , int l , int r , int u , int v , ll val){
    if(l > v || r < u){
        return;
    }
    if(u <= l && r <= v){
        st[id].laz += val;
        st[id].val += val;
        return;
    }
    int mid = l + r;
    mid >>= 1;
    if(st[id].laz != 0){
        push_down(id);
    }
    update_range(id << 1 , l , mid , u , v , val);
    update_range(id << 1 | 1 , mid + 1 , r , u , v , val);
}// done cap nhat cac cha tren duong di tu u den goc

ll get_maxx(int id , int l , int r , int u , int v){
    if(l > v || r < u){
        return -INF;
    }
    if(l >= u && r <= v){
        return st[id].maxx;
    }
    int mid = l + r;
    mid >>= 1;
    if(st[id].laz != 0){
        push_down(id);
    }
    return max(get_maxx(id << 1 , l , mid , u , v) , get_maxx(id << 1 | 1 , mid + 1 , r , u , v));
}// tim dinh gan nhat bi xoa tren duong di tu u ve goc (done)

int get_val(int id , int l , int r , int pos){
    if(l == r){
        return st[id].val;
    }
    int mid = l + r;
    mid >>= 1;
    if(st[id].laz != 0){
        push_down(id);
    }
    if(pos <= mid){
        return get_val(id << 1 , l , mid , pos);
    }else{
        return get_val(id << 1 | 1 , mid + 1 , r , pos);
    }
}// done lay gia tri cua cay con co goc la u

void HLD(int u){
    if(chainhead[nchain] == 0) chainhead[nchain] = u;
    chainidx[u] = nchain;
    posinbase[u] = ++nbase;
    update_val(1 , 1 , n , posinbase[u] , cnt[u]);
    int heavychild = -1;
    for(int v : adj[u]){
        if(v == par[u]) continue;
        if(heavychild  == -1 || cnt[heavychild] < cnt[v]){
            heavychild = v;
        }
    }
    if(heavychild != -1){ 
        HLD(heavychild);
    }
    for(int v : adj[u]){
        if(v == par[u] || v == heavychild){
            continue;
        }
        nchain ++;
        HLD(v);
    }
} // done Heavy light decomposition

int  get_par_component(int u , int num){
    int uchain = chainidx[u];
    int last = posinbase[u];
    ll maxx = 0;
    while(true){

        maxx = get_maxx(1 , 1 , n , posinbase[chainhead[uchain]] , posinbase[u]);
        if(maxx == -INF){
            last = posinbase[chainhead[uchain]];
            u = par[chainhead[uchain]];
            if(u == 0){ 
                break;
            }
            uchain = chainidx[u];
        }else{
            if(maxx == posinbase[u]){
                break;
            }
            if(maxx < posinbase[u]){
                last = maxx + 1;
                return last;
            }

        }
    }
    return last;
}
void resize_tree(int u , int num){
    int uchain = chainidx[u];
    int last = posinbase[u];
    ll maxx = 0;
    while(true){

        maxx = get_maxx(1 , 1 , n , posinbase[chainhead[uchain]] , posinbase[u]);
        if(maxx == -INF){
            last = posinbase[chainhead[uchain]];
            update_range(1 , 1 , n , posinbase[chainhead[uchain]] , posinbase[u] , -num);
            if(u == 0){ 
                break;
            }
            u = par[chainhead[uchain]];
            uchain = chainidx[u];
        }else{
            if(maxx == posinbase[u]){
                break;
            }
            if(maxx < posinbase[u]){
                last = maxx + 1;
                update_range(1 , 1 , n , maxx + 1 , posinbase[u] , -num);
                break;
            }

        }
    }
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);     
    freopen("new.inp" , "r" , stdin);
    freopen("new.out" , "w" , stdout);
    cin >> n;
    int u , v;
    for(int i = 1 ; i < n ; i ++){
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        par[i] = - 1;
    }
    par[n] = -1;
    cin >> m;
    for(int i = 1 ; i <= m ; i ++){
        cin >> val[i];
    }
    DFS(1 , 0);
    nchain = 1;
    HLD(1);
    int cur_vertex ;
    int last;
    int numnode = 0;
    for(int i = 1 ; i <= m ; i ++){
        cur_vertex = val[i] ^ ans[i - 1];
        numnode = get_val(1 , 1 , n , posinbase[cur_vertex]);
        last = get_par_component(cur_vertex , numnode);
        ans[i] = get_val(1 , 1 , n , last);
        resize_tree(cur_vertex , numnode);
        delete_node(1 , 1 , n , posinbase[cur_vertex]);
    }
    for(int i = 1 ; i <= m ; i ++){
        cout << ans[i] << '\n';
    }
    
    return 0;
}
