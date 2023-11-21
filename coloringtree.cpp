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

struct query{
    int pos , val ;
    int type;
};

query qu[MAXN * 2];

int n , m , timedfs;
vector<int > adj[MAXN];
int start[MAXN] , endd[MAXN] , color[MAXN] , a[MAXN] , bit[MAXN] ;
map<int , int > mpa;

void update(int idx , int val){
    for( ; idx <= n ; idx += idx & (-idx)){
        bit[idx] += val;
    }
}

int get_value(int idx){
    
    int sum = 0;
    for( ; idx > 0 ; idx -= idx & (-idx)){
        sum += bit[idx];
    }
    return sum;
}

int get_range(int l , int r){
    return get_value(r) - get_value(l - 1);
}

void DFS(int u , int par){
    timedfs ++;
    a[timedfs] = color[u];
    start[u] = timedfs;
    for(int v : adj[u]){
        if(v != par){
            DFS(v , u);
        }
    }
    endd[u] = timedfs;
}

bool cmp(query u , query v){
    if(u.pos == v.pos){
        return u.type < v.type;
    }
    return u.pos < v.pos;
}

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    freopen("new.inp" , "r" , stdin);
    freopen("new.out" , "w" , stdout);
    cin >> n >> m;
    int root;
    cin >> root;
    int u , v;
    for(int i = 1 ; i <= n - 1 ; i ++){
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for(int i = 1 ; i <= n ; i ++){
        cin >> color[i];
    }    
    DFS(root , 0);
    int num = 0;
    /* 
    0 = update_val
    != 0 cal
    */
    for(int i = 1 ; i <= n ; i ++){
        num ++;
        qu[num].type = 0;
        qu[num].pos = start[i];
        qu[num].val = a[start[i]];
    }
    int x;
    for(int i = 1 ; i <= m ; i ++){
        num ++;
        qu[num].type = i;
        cin >> x;
        qu[num].pos = endd[x];
        qu[num].val = start[x];
    }

    sort(qu + 1 , qu + num + 1 , cmp);
    for(int i = 1 ; i <= num ; i ++){
        if(qu[i].type == 0){
            if(mpa[qu[i].val] == 0){
                update(qu[i].pos , 1);
                mpa[qu[i].val] = qu[i].pos;
            }else{
                update(mpa[qu[i].val] , -1);
                update(qu[i].pos , 1);
                mpa[qu[i].val] = qu[i].pos;
            }
        }else{
            start[qu[i].type] = get_range(qu[i].val , qu[i].pos); 
        }
    }
    for(int i = 1 ; i <= m ; i ++){
        cout << start[i] << ' ';
    }
    return 0;    
}