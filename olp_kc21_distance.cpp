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
const ll MAXN = 1e5  + 7;
int a[MAXN] , b[MAXN];
struct item{
    int val , pos ;
    bool type;
} c[MAXN * 2];
int n , m , k;
bool cmp(item x , item y){
    if(x.val == y.val) return x.type < y.type;
    return x.val < y.val;
}
ll res[MAXN];
ll st[MAXN * 4];
void build(int id , int l , int r){
    if(l == r){
        st[id] = res[l];
        return ;

    }
    int mid = l + r;
    mid >>= 1;
    build(id << 1 , l , mid);
    build(id << 1 | 1 , mid + 1 , r);
    st[id] = min(st[id << 1] , st[id << 1 | 1]);
}
ll get_min(int id , int l , int r , int u , int v){
    if(v < l || r < u){
        return INF;
    }
    if(u <= l && r <= v){
        return st[id];
    }
    int mid = l + r;
    mid >>= 1;
    return min(get_min(id << 1 , l , mid , u , v) , get_min(id << 1 | 1 , mid + 1 , r , u , v));
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen("new.inp", "r", stdin);
    freopen("new.out" , "w" , stdout);
    cin >> m >> n >> k;
    for(int i = 1 ; i <= m ; i ++){
        cin >> a[i];
        c[i].val = a[i];
        c[i].type = 1;
        c[i].pos = i;
    }
    for(int i = 1 ; i <= n ; i ++){
        cin >> b[i];
        c[i + m].val = b[i];
        c[i + m].type = 0;
        c[i + m].pos = i + m;
    }
    sort(c + 1, c + n + m + 1 ,cmp);
    int cur = -1;
    bool meet = 0;
    for(int i = 1 ; i <= n + m ; i ++){
        if(c[i].type == 0){
            meet = true;
            cur = c[i].val;
        }else{
            if(meet){
                res[c[i].pos] = abs(c[i].val - cur);
            }else{
                res[c[i].pos] = INF;
            }
        }
    }
    cur = - 1;
    meet = 0;
    for(int i = n + m ; i >= 1; i --){
        if(c[i].type == 0){
            meet = true;
            cur = c[i].val;
        }else{
            if(meet){
                res[c[i].pos] = min(1ll* abs(1ll * c[i].val - 1ll * cur) , res[c[i].pos]);
            }else{
                res[c[i].pos] = min(res[c[i].pos] , INF);
            }
        }
    }
    build(1 , 1 , m);
    int l , r; 
    for(int i = 1 ; i <= k ; i ++){
        cin >> l >> r;
        cout << get_min(1 , 1 , m , l , r) << '\n';
    }   
    return 0;
}
/* becareful :
- long long
- check if array size limit
- check if overflow
- check if index negative
- check if index out of bound
- check if special testcase
- check if input is invalid
- check if output is invalid
- check if the variables type is duplicate
*/