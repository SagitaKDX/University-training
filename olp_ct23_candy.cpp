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

const ll MAXN = 2e5 + 7;
int n , q;
int a[MAXN];
ll bit[MAXN][11];
bool check_digit[MAXN][10];
void update(int idx , int id , int val){
    for( ; idx <= n ; idx += idx & (-idx)){
        bit[idx][id] += val;
    }
}
ll get(int idx , int id){
    ll res = 0;
    for( ; idx > 0 ; idx -= idx & (-idx)){
        res += bit[idx][id];
    }
    return res;
}
ll get_range(int l , int r , int id){
    return get(r,  id) - get(l - 1 , id);
}

bool check(ll val , int id){
    if(val % id == 0){
        return true;
    }
    int cur ;
    for( ; val > 0 ;){
        cur = val % 10;
        val /= 10;
        if(cur == id){
            return true;
        }
    }
    return false;
}
signed main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    freopen("new.inp" , "r" , stdin);
    freopen("new.out" , "w" , stdout);
    read(n); read(q);
    for(int i = 1 ; i <= n ; i ++){
        read(a[i]);
        for(int j = 1 ; j <= 9 ; j ++){
            if(check(i , j)){
                update(i , j , a[i]);
                check_digit[i][j] = true;
            }
        }
        update(i , 10 , a[i]);
    }
    int type;
    int l , r , k;
    ll sum = 0;
    for(int i = 1 ; i <= q ; i ++){
        read(type);
        if(type == 1){
            read(l); read(k);
            for(int j = 1 ; j <= 9 ; j ++){
                if(check_digit[l][j]){
                    update(l , j , -a[l]);
                    update(l , j , k);
                }
            }
            update(l , 10 , -a[l]);
            update(l , 10 , k);
            a[l] = k;
        }
        if(type == 2){
            read(l); read(r); read(k);
            sum = get_range(l , r , 10) + get_range(l , r , k);
            write(sum);
            putchar('\n');
        }
    }
    return 0;    
}