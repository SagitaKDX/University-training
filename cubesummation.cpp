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
#define bit(x, i) (((x) >> (i)) & 1)
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
const ll INF = 1e5 + 7;
const ll MAXN = 1e2 + 7;
const ll MOD = 1e9;
int n , m;
ll bit[MAXN][MAXN][MAXN];
void update(int x , int y , int z , ll w){
    
    for( ; x <= n ; x += x & (-x)){
        for(int j = y ; j <= n ; j += j & -j){
            bit[x][j][z] += w;
        }
    }   
}
ll get_val(int x , int y , int g , int h , int k){
    ll ans = 0;
    for(int i = g ; i > 0 ; i -= i &(-i)){
        for(int j = h ; j > 0; j -= j & (-j)){
                    ans += bit[i][j][k];
        }
    }
    for(int i = g ; i > 0 ; i -= i &(-i)){
        for(int j = y - 1 ; j > 0 ; j -= j & (-j)){
                    ans -= bit[i][j][k];
        }
    }
    for(int i = x - 1 ; i > 0 ; i -= i & (-i)){
        for(int j = h ; j > 0 ; j -= j &(-j)){
                    ans -= bit[i][j][k];
        }
    }
    for(int i = x - 1 ; i > 0 ; i -= i & (-i)){
        for(int j = y - 1 ; j > 0 ; j -= j & (-j)){
                    ans += bit[i][j][k];
        }
    }
    return ans;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    freopen("new.inp" , "r" , stdin);
    freopen("new.out" , "w" , stdout);
    int t;
    string st;
    cin >> t;
    while(t--){
        cin >> n >> m;
        int x1 , x2 , y1 , y2 , z1 , z2;
        int w;
        for(int i = 1 ; i <= m ; i ++){
            cin >> st;
            if(st[0] == 'U'){
                cin >> x1 >> y1 >> z1 >> w;
                update(x1, y1 , z1 , w - get_val(x1 , y1 , x1 , y1 , z1));
            }else{
                cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
                ll ans = 0;
                for(int g = z1 ;  g <= z2 ; g++){
                    ans += get_val(x1 , y1 , x2 , y2 , g);
                }
                cout << ans << '\n';
            }        
        }
        for(int i = 1 ; i <= n ; i ++){
            for(int j = 1 ; j <= n ; j ++){
                for(int k = 1 ; k <= n ; k ++){
                    bit[i][j][k] = 0;
                }
            }
        }
    }
    return 0;
}