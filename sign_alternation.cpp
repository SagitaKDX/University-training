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
const ll MAXN = 2e5 + 7 ;
const ll MOD = 1e8;
const ll INF = 1e18 + 7;
int n , m;
ll st[MAXN * 4][2];
int a[MAXN];
void build(int id , int l , int r){
    if(l == r){
        st[id][l % 2] = a[l];
        return;
    }
    int mid = l + r;
    mid >>= 1;
    build(id << 1 , l , mid);
    build(id << 1 | 1 , mid + 1 , r);
    st[id][0] = st[id << 1][0] + st[id << 1 | 1][0];
    st[id][1] = st[id << 1][1] + st[id << 1 | 1][1];
}

void update(int id , int type , int l , int r , int pos , int val){
    if(l == r){
        st[id][type] = val;
        return;
    }
    int mid = l + r;
    mid >>= 1;
    if(pos <= mid){
        update(id << 1 , type , l , mid , pos , val);
    }else{
        update(id << 1 | 1 , type , mid + 1 , r , pos , val);
    }
    st[id][type] = st[id << 1][type] + st[id << 1 | 1][type];
}

ll get(int id , int type , int l , int r , int u , int v){
    if(l > v || r < u){
        return 0;
    }
    if(u <= l && r <= v){
        return st[id][type];
    }
    int mid = l + r;
    mid >>= 1;
    return get(id << 1 , type , l , mid , u , v) + get(id << 1 | 1 , type , mid + 1 , r , u , v);
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // freopen("new.inp" , "r" , stdin);
    // freopen("new.out" , "w" , stdout);
    cin >> n;
    for(int i = 1 ; i <= n ; i ++){
        cin >> a[i];
    }
    build(1 , 1, n);
    cin >> m;
    int type;
    int u , v;
    for(int i = 1 ; i <= m ; i ++){
        cin >> type >> u >> v;
        if(type){
            cout << get(1 , u % 2 , 1 , n , u , v) - get(1 , !(u % 2) , 1 , n , u , v) << '\n';
            // cout << get(1 , u % 2 , 1 , n , u , v) << '\n';
        }else{
            update(1 , u % 2 , 1 , n , u , v);
        }
    }
    return 0;
}
