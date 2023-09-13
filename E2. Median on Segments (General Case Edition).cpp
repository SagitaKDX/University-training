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

void minimize(ll &x,long long y){
if(x>y){
    x=y;
}
}

void maximize(ll &x,long long y){
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

ll pow_mod(ll a, long long b, long long m) {
    ll res = 1;
    while(b){
            res = res * (b & 1 ? a : 1) % m;
            a = a * a % m; b >>= 1;
    }
    return res;
}

ll GCD(ll a , long long b){
    while(b != 0 ){
        a = a % b;
        ll tmp = a;
        a = b;
        b = tmp;
    }
    return a;
}

ll minn(ll a ,long long b , long long c ,long long d){
    ll res = a;
    if(res > d) res = d;
    if(res > b) res = b;
    if(res > c) res = c;
    return res;
}
const ll INF = 1e18 + 7;
const ll MAXN = 5e5 + 7;
int n ;
int a[MAXN];
ll greaterCount(int m) {
    vector<int> s(2 * n + 1);
    int sum = n;
    ll result = 0;
    s[sum] = 1;
    ll add = 0;
    for(int i = 1 ; i <= n ; i ++){
        if (a[i] < m)
            sum--, add -= s[sum];
        else
            add += s[sum], sum++;
        result += add;
        s[sum]++;
    }
    return result;
}
signed main(){
    // ios_base::sync_with_stdio(false);
    // cin.tie(0);
    freopen("new.inp" , "r" , stdin);
    freopen("new.out" , "w" , stdout);
    int m;
    read(n); read(m);
    for(int i = 1;  i <= n ; i ++){
        read(a[i]);
    }
    cout << greaterCount(m) - greaterCount(m + 1);

    return 0;
}
