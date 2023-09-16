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
const ll INF = 1e20 + 7;
const ll MAXN = 1e5 + 7;
const ll MOD = 1e9 + 7;
int n , q;
int par[MAXN];
struct item2{
    int u , v , w;
};
ll b[MAXN] , pos[MAXN];
ll res[MAXN];
int binarysearch(ll val){
    int l = 1 , r = n -1;
    while(l <= r){
        int mid = l + r;
        mid >>= 1;
        if(b[mid] == val){
            return pos[mid];
        }
        if(b[mid] < val){
            l = mid + 1;
        }else{
            r = mid - 1;
        }
    }
}
int binarysearch_r(ll val){
    int l = 1 , r = n - 1;
    int save = -1;
    while(l <= r){
        int mid = l + r;
        mid >>= 1;
        if(b[mid] <= val){
            save = pos[mid];
            l = mid + 1;
        }else{
            r = mid - 1;
        }
    }
    return save;
}
int binarysearch_l(ll val){
    int l = 1 , r = n - 1;
    int save = - 1;
    while(l <= r){
        int mid = l + r;
        mid >>= 1;
        if(b[mid] >= val){
            r = mid - 1;
            save = pos[mid];
        }else{
            l = mid + 1;
        }
    }
    return save;
}
bool cmp(item2 u , item2 v){
    return u.w < v.w;
}
int findpar(int u){
    return par[u] < 0 ? u : par[u] = findpar(par[u]); 
}
void joint(int u , int v , ll w){
    u = findpar(u);
    v = findpar(v);
    if(u == v){
        return ;
    }
    int z = binarysearch(w);
    res[z] += abs(par[u]) * abs(par[v]);
    if(par[u] > par[v]){
        swap(u , v);
    }
    par[u] += par[v];
    par[v] = u;
    return;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    // freopen("new.inp" , "r" , stdin);
    // freopen("new.out" , "w" , stdout);
    read(n); read(q);
    vector<item2> canh;
    int u , v , w;
    for(int i = 1 ; i <= n - 1 ; i ++){
        par[i] = -1;
        read(u); read(v); read(w);
        b[i] = w;
        canh.push_back({u , v , w});
    }
    par[n] = -1;
    sort(canh.begin() , canh.end() , cmp);
    sort(b + 1 , b + n );
    int d = 1;
    for(int i = 1 ; i < n ; i ++){
        if(i != 1 && b[i] != b[i - 1]){
            d ++;
        }
        pos[i] = d;
    }
    for(int i = 0 ; i < canh.size(); i ++){
        joint(canh[i].u , canh[i].v , canh[i].w);
    }
    ll l , r;
    for(int i = 1 ; i <= n ; i ++){
        res[i] += res[i - 1];
    }
    for(int i = 1 ; i <= q; i ++){
        read(l); read(r);
        if(r < b[1]){
            cout << 0 << '\n';
            continue;
        }
        if(l > b[n - 1]){
            cout << 0 << '\n';
            continue;
        }
        // cout << z << '\n';
        ll ans = res[binarysearch_r(r)] - res[binarysearch_l(l) - 1];
        write(ans);
        putchar('\n');

    }   
    return 0;
}