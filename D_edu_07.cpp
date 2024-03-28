#include <bits/stdc++.h>
 
using namespace std;
#define ll long long
#define ld long double
 
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
const ll MAXN = 3e5 + 7 ;
const ll INF = 1e18;
const ll MOD = 1e9 + 7;
struct item{
    ll prefix , suffix;
    ll val_1 , val_2;
    ll prefix_val_2;

};

ll st[MAXN * 4];
void update(int id , int l , int r , int pos , ll val){
    if(l == r){
        st[id] = val;
        return;
    }
    int mid = l + r;
    mid >>= 1;
    if(pos <= mid){
        update(id << 1 , l , mid , pos , val);
    }else{
        update(id << 1 | 1 , mid + 1 , r , pos , val);
    }
    st[id] = max(st[id << 1] , st[id << 1 | 1]);
}

ll get(int id , int l , int r , int u , int v){
    if(l > v || r < u){
        return 0;
    }
    if(u <= l && r <= v){
        return st[id];
    }
    int mid = l + r;
    mid >>= 1;
    return max(get(id << 1 , l , mid , u , v) , get(id << 1 | 1 , mid + 1 , r , u , v));    
}

ll n;
int x;
item a[MAXN];
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    // freopen("new.inp" , "r" , stdin);
    // freopen("new.out" , "w" , stdout);
    cin >> n >> x;  
    ll minn = 0;
    ll cur = 0;
    ll ans = 0;
    for(int i = 1 ; i <= n ; i ++){
        cin >> a[i].val_1;
        a[i].val_2 = a[i].val_1 * x;
        a[i].prefix_val_2 = a[i].val_2 + a[i - 1].prefix_val_2;
        a[i].prefix = a[i - 1].prefix + a[i].val_1;
        cur = 0;
        cur = max(0LL , a[i].prefix - minn);
        ans = max(ans , cur);
        if(i == 1){
            update(1 , 1 , n , i , a[i].prefix_val_2 * -1 + cur);
        }else{
            update(1 , 1 , n , i , -a[i].prefix_val_2 + cur);
        }
        minn = min(minn , a[i].prefix);
    }
    minn = 0;
    cur = 0;
    for(int i = n ; i >= 1 ; i --){
        a[i].suffix = a[i + 1].suffix + a[i].val_1;
        if(i > 1){
            ans = max(ans , cur + a[i].prefix_val_2 + get(1 , 1 , n , 1 , i - 1));
        }else{
            ans = max(ans , cur + a[i].prefix_val_2);
        }
        cur = max(0LL , a[i].suffix - minn);
        minn = min(minn , a[i].suffix);
    }
    cout << ans  << '\n';
    return 0;
}
