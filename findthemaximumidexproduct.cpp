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
int n , d;
int a[MAXN];
struct item{
    ll min_val;
    ll max_val;
};
item st[MAXN * 4];
int Left[MAXN] , Right[MAXN];
int b[MAXN] , pos[MAXN] , v[MAXN];
void build(int id , int l , int r){
    st[id].max_val = -INF;
    st[id].min_val = INF;
    if(l == r){
        return;
    }
    int mid = l + r;
    mid >>= 1;
    build(id << 1, l , mid);
    build(id << 1 | 1 , mid + 1 , r);
}

void update(int id , int l , int r , int pos_st , ll val){
    if(l == r){
        st[id].min_val = val;
        st[id].max_val = val;
        return;
    }
    int mid = l + r;
    mid >>= 1; 
    if(pos_st <= mid){
        update(id << 1 , l , mid , pos_st , val);
    }else{
        update(id << 1 |1 , mid + 1 , r , pos_st , val);
    }
    st[id].min_val = min(st[id << 1].min_val , st[id << 1 | 1].min_val);
    st[id].max_val = max(st[id << 1].max_val , st[id << 1| 1].max_val);
}
ll get_left(int id , int l , int r , int u , int v){
    if(l > v || r < u ){
        return -INF;
    }
    if(u <= l && r <= v){
        return st[id].max_val;
    }
    int mid = l + r;
    mid >>= 1;
    return max(get_left(id << 1 , l , mid , u , v) , get_left(id << 1 | 1 , mid + 1 , r , u , v));
}
ll get_right(int id , int l , int r , int u , int v){
    if(l > v || r < u){
        return INF;
    }
    if(u <= l && r <= v){
        return st[id].min_val;
    }
    int mid = l + r;
    mid >>= 1;
    return min(get_right(id << 1  , l , mid , u , v) , get_right(id << 1 | 1 , mid + 1 , r , u , v));
}
int binarysearch(int val){
    int l = 1 , r = n;
    while(l <= r){
        int mid = l + r;
        mid >>= 1;
        if(b[mid] == val){
            return pos[mid];
        }
        if(val > b[mid]){
            l = mid + 1;
        }else{
            r = mid - 1;
        }
    }
    return 0;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    freopen("new.inp" , "r" , stdin);
    freopen("new.out" , "w" , stdout);
    cin >> n;
    for(int i = 1 ; i <= n ; i ++){
        cin >> a[i];
        b[i] = a[i];
    }
    sort(b + 1 , b + n + 1 );
    d = 1;
    for(int i = 1 ; i <= n ; i ++){
        if(i > 1 && b[i] != b[i - 1]){
            d ++;
        }
        pos[i] = d;
        v[d] = b[i]; 
    }
    build(1 , 1 , d);
    for(int i = 1 ; i <= n ; i ++){
        int z = binarysearch(a[i]);
        if(z == d){
            Left[i] = 0;
            update(1 , 1 , d , z , i);
            continue;
        }
        ll val = get_left(1 , 1 , d , z + 1 , d);
        if(val == -INF){
            Left[i] = 0;
        }else{
            Left[i] = val;
        }
        update(1 , 1 , d , z , i);
    }
    build(1 , 1 , d);
    for(int i = n ; i >= 1 ; i --){
        int z =binarysearch(a[i]);
        if(z == d){
            Right[i] = 0;
            update(1 , 1 , d , z , i);
            continue;
        }
        ll val = get_right(1 , 1 , d , z + 1 , d);
        if(val == INF){
            Right[i] = 0;
        }else{
            Right[i] = val;
        }
        update(1 , 1 , d , z , i);
    }
    ll maxx = -INF;
    for(int i = 1 ; i <= n ; i ++){
        maximize(maxx , 1ll * Left[i] * Right[i]);
    }
    cout << maxx << '\n';
    
    return 0;
}