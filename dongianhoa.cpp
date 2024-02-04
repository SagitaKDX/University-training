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
const ll MAXN = 1e3 + 7 ;
const ll MOD = 1e9 + 7;
const ll INF = 1e18 + 7;
struct item{
    int u , v , w;
    int id;
};

bool cmp(item u , item v){
    return u.w  <  v.w;
}

int par[MAXN];

int findpar(int u){
    return par[u] < 0 ? u : par[u] = findpar(par[u]);
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

int n , m;
int u , v , w;
bool check[MAXN];
item edge[MAXN];

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    freopen("new.inp" , "r" , stdin);
    freopen("new.out" , "w" , stdout);
    cin >> n >> m;
    for(int i = 1 ; i <= m ; i ++){
        cin >> u >> v >> w;
        edge[i].u = u;
        edge[i].v = v;
        edge[i].w = w;      
        edge[i].id = i;
    }
    int numtplt = 0;
    ll res = INF;
    int l = -1 , r = -1;
    sort(edge + 1 , edge + m + 1 , cmp);
    for(int i =  1 ; i <= m ; i ++){
        for(int j = 1 ; j <= n ; j ++){
            par[j] = -1;
        }
        numtplt = n;
        for(int j = i ; j <= m ; j ++){
            if(join(edge[j].u , edge[j].v)){
                numtplt --;
            }
            if(numtplt == 1){
                if(res > edge[j].w - edge[i].w){
                    res = edge[j].w - edge[i].w;
                    l = i;
                    r = j;
                }
                break;
            }
        }
    }
    if(res == INF){
        cout << "NO";
    }else{
        cout << "YES" << '\n';
        cout << res << '\n';
        int num = 0;
        for(int i = 1 ; i <= n ; i ++){
            par[i] = -1;
        }
        for(int i = l ; i <=r ; i ++){
            if(join(edge[i].u , edge[i].v)){
                check[edge[i].id] = true;
                num ++;
            }
        }
        cout << m - num << ' ';
        for(int i = 1 ; i <= m ; i ++){
            if(check[i] == false){
                cout << i <<" ";
            }
        }
    }
    return 0;
}