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

const ll MOD = 1e9 + 7;
const ll MAXN = 1e6 + 7;

struct query{
    int type;
    int open;
    int endd;
};
// type = 1 -- > minimum
// type = 0 -- > maximum

bool cmp(query u , query v){
    if(u.open == v.open){
        return u.type < v.type;
    }
    return u.open < v.open;
}

query queries[MAXN * 2];
int n;
int a[MAXN];
int m = 0;
int st[MAXN * 4];

void update(int id , int l , int r , int pos , int val){
    if(l == r){
        st[id] += val;
        return ;
    }
    int mid = l + r;
    mid >>= 1;
    if(pos <= mid){
        update(id << 1 , l , mid , pos , val);
    }else{
        update(id << 1 | 1 , mid + 1 , r , pos , val);
    }
    st[id] = st[id << 1] + st[id << 1 | 1];
}

ll get(int id , int l , int r , int u , int v){
    if(l > v || r < u || l > r){
        return 0;
    }
    if(u <= l && r <= v){
        return st[id];
    }
    int mid = l + r;
    mid >>= 1 ;
    return get(id << 1 , l , mid , u , v) + get(id << 1 | 1 , mid +  1 , r , u , v);
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen("new.inp", "r", stdin);
    freopen("new.out" , "w" , stdout);
    cin >> n;
    for(int i = 1 ; i <= n ; i ++){
        cin >> a[i];
    }
    deque<int > dq;
    int type ;
    int open ;
    int endd;

    for(int i = n ; i >= 1; i --){
        while(dq.size()  && a[dq.back()] > a[i]){
            dq.pop_back();
        }
        if(dq.empty()){
           type = 1;
           open = i;
           endd = n;
           m ++ ;
           queries[m].type = type;
           queries[m].open = open;
           queries[m].endd = endd;
        }else{
            type = 1;
            open = i;
            endd = dq.back() - 1;
            m ++;
            queries[m].type = type;
            queries[m].open = open;
            queries[m].endd = endd;
        }
        dq.push_back(i);
    }
    while(dq.size()){
        dq.pop_back();
    }
    for(int i = 1 ; i <= n ; i ++){
        while(dq.size()  && a[dq.back()] < a[i]){
            dq.pop_back();
        }
        if(dq.empty()){
           type = 0;
           open = 1;
           endd = i;
           m ++ ;
           queries[m].type = type;
           queries[m].open = open;
           queries[m].endd = endd;
        }else{
            type = 0;
            open = dq.back() + 1;
            endd = i;
            m ++;
            queries[m].type = type;
            queries[m].open = open;
            queries[m].endd = endd;
        }
        dq.push_back(i);
    }
    sort(queries + 1 , queries + m + 1 , cmp);
    ll res = 0;
    for(int i = 1 ; i <= m ; i ++){
        if(queries[i].type == 0){
            update(1 , 1 , n , queries[i].endd , 1);
        }else{
            res += get(1 , 1 , n , queries[i].open , queries[i].endd);
        }
    }
    cout << res << '\n';
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