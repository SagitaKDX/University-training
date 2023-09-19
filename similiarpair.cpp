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
const ll INF = 1e18 + 7;
const ll MAXN = 1e5 + 7;
const ll MOD = 1e9 + 7;
int n , k;
int bit[MAXN];
vector<int > adj[MAXN];
void update(int idx , int val){
    if(idx > n){
        return;
    }
    for(; idx <= n ; idx += idx & (-idx)){
        bit[idx] += val;
    }
    return;
}
ll get(int idx){
    ll sum = 0;

    for(; idx > 0 ; idx -= idx & (-idx)){
        sum += bit[idx] ;
    }

    return sum;
}
ll get_range(int l , int r){
    return get(r) - get(l - 1);
}
ll res = 0;
void DFS(int u , int pre){
    res += get_range(max(u - k , 1) , min(u + k , n));
    update(u , 1);
    for(int v : adj[u]){
        if(v == pre){
            continue;
        }
        DFS(v , u);
    }
    update(u , -1);
}
bool check[MAXN];
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    freopen("new.inp" , "r" , stdin);
    freopen("new.out" , "w" , stdout);
    cin >> n >> k;
    int u , v;
    for(int i = 1 ; i <= n - 1 ; i ++){
        cin >> u >> v;
        adj[u].push_back(v);
        check[v] = true;

    }
    int st =0;
    for(int i = 1 ; i <= n ; i ++){
        if(check[i] == false){
            st = i;
            break;
        }
    }
    DFS(st , 0);
    cout << res << '\n';
    return 0;
}