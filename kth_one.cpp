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
    int l , r;
    int laz ;
} st[MAXN * 4];
int a[MAXN] , n , m;

void push_down(int id){
    st[id << 1].laz += st[id].laz;
    st[id << 1].l += st[id].laz;
    st[id << 1].r += st[id].laz;
    st[id << 1 | 1].laz += st[id].laz;
    st[id << 1 | 1].l += st[id].laz;
    st[id << 1 | 1].r += st[id].laz;
    st[id].laz = 0;
}
void update(int id , int l , int r , int u , int v , int val , int type){
    if(l > v || u > r){
        return;
    }
    if(u <= l && r <= v){
        // type = 0 , new "1" 
        // type = 1 , change "1" to 0
        // type = 2 , update range
        if(type == 0){
            st[id].l += 1;
            st[id].r += 1;
            st[id].laz = 1;
            return;
        }
        if(type == 1){
            st[id].l -= 1;
            st[id].r -= 1;
            st[id].laz = -1;
        }
        if(type == 2){
            st[id].l += val;
            st[id].r += val;
            st[id].laz += val;
        }
        return ;
    }
    if(st[id].laz != 0){
        push_down(id);
    }
    int mid = l + r;
    mid >>= 1;
    update(id << 1 , l , mid , u , v , val , type);
    update(id << 1 | 1, mid + 1 , r , u , v , val , type);
    st[id].l = st[id << 1].l ;
    st[id].r = st[id << 1 | 1].r;
}

int find(int id , int l , int r , int k){
    if(l == r){
        return l;
    }
    if(st[id].laz != 0){
        push_down(id);
    }
    int mid = l + r;
    mid >>= 1;
    if(st[id << 1].l <= k && k <= st[id << 1].r){
        return find(id << 1 , l , mid , k);
    }else{
        return find(id << 1 | 1 , mid + 1 , r , k);
    }
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // freopen("new.inp" , "r" , stdin);
    // freopen("new.out" , "w" , stdout);
    cin >> n >> m;
    for(int i = 1 ; i <= n ; i ++){
        cin >> a[i];
        if(a[i] == 1){
            update(1 , 1, n , i , i , 1 , 0);
            if(i < n){
                update(1 , 1 , n , i + 1 , n , 1 , 2);
            }
        }
    }
    int type , u , v;
    for(int i = 1 ; i <= m ; i ++){
        cin >> type >> u;
        u ++;
        if(type - 1){
            cout << find(1 , 1 , n , u) - 1 << '\n';
        }else{
            a[u] = !a[u];
            if(a[u] == 0){
                update(1 , 1, n , u , u , -1 , 1);
                if(u < n)
                    update(1 , 1, n , u + 1 , n , -1 , 2);
            }else{
                update(1 , 1, n ,u  , u , 1 , 0);
                if(u < n){
                    update(1 , 1, n , u + 1 , n , 1 , 2);
                }
            }
        }
    }
    return 0;
}
