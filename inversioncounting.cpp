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
const ll MAXN = 25e4 + 7;
const ll MAXVAL = 5e4 + 7;
int n , d;
int a[MAXN];
int mark[MAXN] ;
int cur = 1;
ll bit[MAXVAL][507];  
ll bit2[MAXVAL];
ll inv = 0;
void update(int idx , int id , int val){
    for( ; idx <= MAXVAL - 6 ; idx += idx & -idx){
        bit[idx][id] += val;
    }
}

ll getvalue(int idx , int id){
    ll sum = 0 ;
    for( ; idx > 0 ; idx -= idx & -idx){
        sum += bit[idx][id] ;
    }
    return sum;
}

ll get_range(int l , int r , int id){
    if(l > r){
        return 0;
    }
    return getvalue(r , id)  - getvalue(l - 1 , id);
}

void update2(int idx  , int val){
    for( ; idx <= MAXVAL - 6 ; idx += idx & -idx){
        bit2[idx] += val;
    }
}

ll get_value2(int idx){
    ll sum = 0;
    for( ; idx > 0 ; idx -= idx & (-idx)){
        sum += bit2[idx];        
    }
    return sum;
}

ll get_range2(int l , int r){
    return  get_value2(r) - get_value2(l - 1);
}

int main(){
    // ios_base::sync_with_stdio(false);
    // cin.tie(0);
    freopen("new.inp" , "r" , stdin);
    freopen("new.out" , "w" , stdout);
    read(n);
    int divseq = sqrt(n);
    for(int i = 1; i <= n ; i ++){
        read(a[i]);
        mark[i] = cur;
        if(i % divseq == 0){
            cur ++;
        }
        inv += get_range2(a[i] + 1 , MAXVAL - 6);
        update2(a[i] , 1);
        update(a[i] , mark[i] , 1);
    }

    int q;
    read(q);
    int x , y;
    ll num = 0;
    while(q--){
        read(x); read(y);
        num = 0;
        for(int i = x - 1 ; mark[i] == mark[x] ; i --){
            if(a[i] > a[x]){
                num ++;
            }
        }
        for(int i = x + 1 ; mark[i] == mark[x] ; i ++){
            if(a[i] <  a[x]){
                num ++;
            }
        }
        for(int i = 1 ; i < mark[x] ; i ++){
            num += get_range(a[x] + 1 , MAXVAL - 6 , i);
        }
        for(int i = mark[x] + 1 ; i <= mark[n] ; i ++){
            num +=  get_range(1 , a[x] - 1 , i);
        }
        update(a[x] , mark[x] , -1);
        inv -= num ;
        a[x] = y;
        num = 0;
        for(int i = x - 1 ; mark[i] == mark[x] ; i --){
            if(a[i] > a[x]){
                num ++;
            }
        }
        for(int i = x + 1 ; mark[i] == mark[x] ; i ++){
            if(a[i] <  a[x]){
                num ++;
            }
        }
        for(int i = 1 ; i < mark[x] ; i ++){
            num += get_range(a[x] + 1 , MAXVAL - 6 , i);
        }
        for(int i = mark[x] + 1 ; i <= mark[n] ; i ++){
            num +=  get_range(1 , a[x] - 1 , i);
        }
        inv += num;
        update(a[x] , mark[x] , +1);
        write(inv);
        putchar('\n');
    }
    
    return 0;
}