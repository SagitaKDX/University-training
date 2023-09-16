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
const ll MAXN = 1e6 + 7;
const ll MOD = 1e9 + 7;
const int N = 1e3 + 7;
int n , m , l , r;
int par[MAXN];
struct item{
    int u , v , w;
};
bool cmp(item u , item v){
    return u.w < v.w;
}
int findpar(int u ){
    return  par[u] < 0 ? u : par[u] = findpar(par[u]);
}
bool joint(int u , int v){
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
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    freopen("new.inp" , "r" , stdin);
    freopen("new.out" , "w" , stdout);
    int q;
    read(q);
    int u , v;
    while(q--){
        read(n); read(m); read(l);  read(r);
        vector<item> canh;
        for(int i = 1 ; i <= n + 1 ; i ++){
            par[i] = -1;
            if(i != n + 1){
                canh.push_back({i , n + 1 , l});
            }
        }
        for(int i = 1 ; i <= m ; i ++){
            read(u); read(v);
            canh.push_back({u , v , r});
        }
        sort(canh.begin() , canh.end() , cmp);
        ll res = 0;
        for(int i = 0 ; i < canh.size() ; i ++){
            if(joint(canh[i].u , canh[i].v)){
                res += canh[i].w;
            }
        }
        write(res);
        putchar('\n');
    }
    return 0;
}
