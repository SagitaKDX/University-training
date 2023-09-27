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
const ll MAXN = 1e3 + 7;
int m ,n;
int a[MAXN][MAXN];
int q;
ll sum[MAXN][MAXN];
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    freopen("new.inp" , "r" , stdin);
    freopen("new.out" , "w" , stdout);
    read(m); read(n);
    for(int i = 1 ; i <= m ; i ++){
        for(int j = 1 ; j <= n ; j ++){
            read(a[i][j]);
            a[i + m][j] = a[i][j];
            a[i + m][j + n] = a[i][j];
            a[i][j + n] = a[i][j];
        }
    }
    for(int i = 1 ; i <= 2 * m ; i ++){
        for(int j = 1 ; j <= 2 * n ; j ++){
            sum[i][j] = sum[i - 1][j] + sum[i][j -1] + a[i][j] - sum[i - 1][j - 1];
        }
    }
    read(q);
    int type = 0;
    int hx = 1 , hy = 1;
    int r , d;
    int x , y , u , v;
    for(int i = 1 ;i <= q ; i ++){
        read(type);
        if(type == 0){
            read(r); read(d);
            hx += d;
            hy += r;
            hx %= m;
            hy %= n;
            if(hx == 0){
                hx = m;
            }
            if(hy == 0){
                hy = n;
            }
        }else{
            read(u); read(v); read(x); read(y);
            u = hx + u - 1;
            v = hy + v - 1;
            x = hx + x - 1;
            y = hy + y - 1;
            write(sum[x][y] + sum[u - 1][v - 1] - sum[x][v - 1] - sum[u - 1][y]);
            putchar('\n');
        }
    }
    return 0;
}