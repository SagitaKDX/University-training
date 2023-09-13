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
const ll INF = 1e20 + 7;
const ll MAXN = 1e6 + 7;
const ll MOD = 1e9 + 7;
const int N = 2e5 + 7;
int n = N - 6;
struct item{
    int num ;
    int l , r;
    int laz;
};
item st[N * 4];
void push_down(int id){
    int t;
    t = st[id].laz;
    st[id << 1].laz += t;
    st[id << 1].l += t;
    st[id << 1].r += t;
    st[id << 1 | 1].laz += t;
    st[id << 1 | 1].l += t;
    st[id << 1 | 1].r += t;
    st[id].laz = 0;
    return;
}
void update(int id , int l , int r , int u , int v , int type){
    if(l > v || r < u){
        return;
    }
    if(u <= l && r <= v){
        // type 0 new value
        // type 1 resize the tree 
        if(type == 0){
            st[id].num += 1;
            if(st[id].num == 1){
                st[id].l += 1;
            }
            st[id].r = st[id].l + st[id].num - 1;

        }
        if(type == 1){
            st[id].laz += 1;
            st[id].l += 1;
            st[id].r += 1;   
        }
        return;
    }
    push_down(id);
    int mid = l + r;
    mid >>= 1;
    update(id << 1 , l , mid , u , v, type);
    update(id << 1 | 1 , mid + 1 , r , u , v , type);
    st[id].num += st[id << 1].num + st[id << 1 | 1].num;
    st[id].l = st[id << 1].l;
    st[id].r = st[id << 1 | 1].r;
}
int find(int id ,int l , int r, int pos){
    if(l == r){
        return l;
    }
    push_down(id);
    int mid = l + r;
    mid >>= 1;
    if(st[id << 1].l <= pos && pos <= st[id << 1].r){
        return find(id << 1 , l , mid , pos);
    }
    return find(id << 1 | 1 , mid + 1 , r , pos);
}
int cur = 0;

    void addNum(int num) {
        cur += 1;
        update(1 , 1 , n ,num + 100001 , num + 100001 , 0);
        if(num + 100001 < n){
            update(1 , 1 , n , num + 100001 + 1 , n , 1);
        }
    }
    
    double findMedian() {
        double val = 0;
        if(cur % 2 == 1){
            val = find(1 , 1 , n ,(int) cur / 2 + 1 ) - 100001;
        }else{
            val = find(1 , 1 , n , (int) cur / 2 );
            val -= 100001;
            val += find(1 , 1 , n , (int) cur / 2 + 1) - 100001;
            val /= 2;
        }
        return val;
    }

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    freopen("new.inp" , "r" , stdin);
    freopen("new.out" , "w" , stdout);
    int t;
    cin >> t;
    int type;
    int val;
    while(t--){
        cin >> type;
        if(type == 0){
            cin >> val;
            addNum(val);
        }else{
            cout << findMedian() << '\n';
        }
    }
    return 0;
}
