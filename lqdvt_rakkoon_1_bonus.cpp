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
const ll MAXN = 5e3 + 7 ;
const ll MOD = 1e9 + 7;
const ll INF = 1e18 + 7;
int n;
int a[MAXN] , c[MAXN];
ll dp[MAXN][MAXN];
ll prefix[MAXN];
ll mx[MAXN][MAXN];
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    freopen("new.inp" , "r" , stdin);
    freopen("new.out" , "w" , stdout);
    cin >> n;
    for(int i = 1 ; i <= n ; i ++){
        cin >> a[i];
        prefix[i] = prefix[i - 1] + a[i];
        
    }
    for(int i = 1 ; i <= n ; i ++){
        cin >> c[i];
    }
    for(int i = 0 ; i <= n ; i ++){
        for(int j = 0 ; j <= n ; j ++){
            dp[i][j] = -INF;
            mx[i][j] = -INF;
        }
    }
    mx[0][0] = 0;
    dp[0][0] = 0;
    for(int i = 1 ; i <= n ; i ++){
        for(int j = 0 ; j <= n ; j ++){
            if(j >= 1)
                dp[i][j] = dp[i - 1][j - 1];
            if(j + c[i] <= n){
                dp[i][j] = max(mx[i - 1][j + c[i]] + prefix[i] , dp[i][j]);
            }
        }
        for(int j = 0 ; j <= n ; j ++){
            mx[i][j] = max(mx[i - 1][j] , dp[i][j] - prefix[i]); 
        }
    }
    ll ans = -INF;
    for(int i = 0 ; i <= n ; i ++){
        ans = max(ans , dp[n][i]);
    }
    cout << ans << '\n';
    return 0;
}
