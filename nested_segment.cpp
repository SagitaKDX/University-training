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
const ll MAXN = 1e5 + 7 ;
const ll MOD = 1e8;
const ll INF = 1e18 + 7;
struct item{
    ll val , laz;
};
item st[MAXN * 2 * 4];
ll check[MAXN] , res[MAXN];
int n;

void push_down(int id){
    ll t = st[id].laz;
    st[id << 1].val += t;
    st[id << 1].laz += t;
    st[id << 1 | 1].val += t;
    st[id << 1 | 1].laz += t;
    st[id].laz =0 ; 
}
void update(int id , int l , int r , int u , int v){
    if( u > v || l > v || u > r){
        return;
    }
    if(u <= l && r <= v){
        st[id].val += 1;
        st[id].laz += 1;
        return;
    }
    if(st[id].laz != 0){
        push_down(id); 
    }
    int mid = l + r;
    mid >>= 1;
    update(id << 1 , l , mid , u , v);
    update(id << 1 | 1 , mid + 1 , r , u , v);
    st[id].val = max(st[id << 1].val , st[id << 1 | 1].val);
}

ll get_max(int id , int l , int r , int u , int v){
    if(l > v || u > r){
        return 0LL;
    }
    if(u <= l && r <= v){
        return st[id].val;
    }
    if(st[id].laz != 0){
        push_down(id);
    }
    int mid = l + r;
    mid >>= 1;
    return max(get_max(id << 1 , l , mid , u , v) , get_max(id << 1 | 1 , mid + 1 , r , u , v));
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // freopen("new.inp" , "r" , stdin);
    // freopen("new.out" , "w" , stdout);
    cin >> n;
    int x;
    for(int i = 1 ; i <=  2 * n ; i ++){
        cin >> x;
        if(check[x] == 0){
            check[x] = i;
        }else{
            
            update(1 , 1, 2 * n , 1 , check[x] - 1);
            res[x] = get_max(1 , 1 ,2 * n , check[x] , check[x]);
        }
    }
    for(int i = 1 ; i <= n ; i ++){
        cout << res[i] << ' ';
    }
    return 0;
}
