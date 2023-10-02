#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
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
const ll INF = 1e18 + 7;
const ll MAXN = 75e3 + 7;
const ll MOD = 1e9 + 7;
const ll MAXVAL = 1000000000;
int n , q , k;
struct item{
    int l , r ;
} query[MAXN];
ll a[MAXN];
struct seg_tree{
    int val , laz;
} st[MAXN * 4];
void rebuild(int id , int l , int r){
    st[id].val = 0;
    st[id].laz = 0;
    if(l == r) return;
    int mid = l + r;
    mid >>= 1;
    rebuild(id << 1 , l , mid);
    rebuild(id << 1 | 1 , mid + 1 , r);
}
void push_down(int id , int l , int r , int mid){
    int t = st[id].laz;
    st[id].laz = 0;
    if(t == -1){
        st[id << 1].val = 0;
        st[id << 1].laz =-1;
        st[id << 1 | 1].val = 0;
        st[id << 1 | 1].laz = -1;
    }else{
        st[id << 1].laz  = 1;
        st[id << 1].val = (mid - l + 1) ;
        st[id << 1 | 1].laz = 1;
        st[id << 1 | 1].val = (r - mid);
        return;
    }
}
void update(int id , int l , int r , int u , int v , int val){
    if(l > v || r < u) return;
    if(u <= l && r <= v){
        if(val == -1){
            st[id].val = 0;
            st[id].laz = -1;
        }else{
            st[id].val = (r - l + 1);
            st[id].laz = 1;
        }
        return;
    }
    int mid = l + r;
    mid >>= 1;
    if(st[id].laz != 0){
        push_down(id , l , r , mid);
    }
    update(id << 1 , l , mid , u , v , val);
    update(id << 1 | 1 , mid + 1, r , u , v , val);
    st[id].val = st[id << 1].val + st[id << 1 | 1].val;
}
ll get(int id , int l , int r , int u , int v){
    if(l > v ||  r < u) return 0;
    if(u <= l && r <= v){
        return st[id].val;
    }
    int mid = l + r;
    mid >>= 1;
    if(st[id].laz != 0){
        push_down(id , l , r , mid);
    }
    return get(id << 1 , l , mid , u , v) + get(id << 1 | 1 , mid + 1 , r , u , v);
}
bool check(int val){
    rebuild(1 , 1 , n);
    for(int i = 1 ; i <= n ; i ++){
        if(a[i] >= val){
            update(1 , 1 , n , i , i , 1);
        }else{
            update(1 , 1 , n , i , i , -1);
        }
    }
    for(int i = 1 ; i <= q ; i ++){
        int cnt =(query[i].r - query[i].l + 1) - get(1 , 1 ,  n , query[i].l , query[i].r);
        update(1 , 1 , n , query[i].l , query[i].l + cnt -1  , -1);
        update(1 , 1 , n , query[i].l + cnt , query[i].r , 1);
    }
    return get(1 , 1 , n , k , k) == 1;
    
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);     
    freopen("new.inp" , "r" , stdin);
    freopen("new.out" , "w" , stdout);
    cin >> n  >> q >> k ;
    k ++;
    for(int i = 1 ; i <= n ; i ++){
        cin >> a[i];
    }
    for(int i = 1 ; i <=q ; i ++){
        cin >> query[i].l >> query[i].r;
        query[i].l ++;
        query[i].r ++;
    }
    int l = -MAXVAL , r = MAXVAL;
    ll save = -1;
    while(l <= r){
        int mid = l + r; 
        mid >>= 1;
        if(check(mid)){
            save = mid;
            l = mid + 1;
        }else{
            r = mid - 1;
        }
    }
    cout << save << '\n';
    return 0;
}
