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
const ll MAXN = 1e4 + 7;
struct query{
    int type , x , y;
    ll k;
};


int t , n , q , m , d , divseq;
ll a[MAXN];
ll b[MAXN * 2];
int pos[MAXN * 2];
int mark[MAXN];
query qu[MAXN];
ll bit[1000 + 7][200];
int value[1000 + 7];
int binarysearch(ll val){
    int l = 1 , r = m ;
    while(l <= r){
        int mid = l + r;
        mid >>= 1;
        if(b[mid] == val){
            return pos[mid];
        }
        if(b[mid] > val){
            r = mid - 1;
        }else{
            l = mid + 1;
        }
    }
    return 0;
}
void update(int idx ,int id , int val){
    for(; idx <= d ; idx += idx & (-idx)){
        bit[idx][id] += val;
    }
}

ll get(int idx , int id){
    ll res = 0;
    for(; idx > 0 ; idx -= idx & (-idx)){
        res +=bit[idx][id];
    }
    return res;
}

ll get_range(int l , int r , int id){
    return get(r , id) - get(l - 1 , id);
}


bool check(int val , int l , int r , int kth){
    int num = 0;
    if(mark[l] == mark[r]){
        for(int j = l ; j <= r ; j ++){
            if(a[j] < value[val]){
                num ++;
            }
        }
        return num < kth;
    }
    for(int j = l ; mark[j] == mark[l] ; j ++){
        if(a[j] < value[val]){
            num ++;
        }
    }
    for(int j = r ; mark[j] == mark[r] ; j --){
        if(a[j] < value[val]){
            num ++;
        }
    }
    for(int i = mark[l] + 1 ; i <= mark[r] - 1 ; i ++){
        if(val != 1){
            num += get_range(1 , val - 1 , i);
        }
    }
    return num < kth;
}

int find_val(int l , int r , int kth){
    int le = 1 , ri = d;
    int save = 1;
    while(le <= ri){
        int mid = le + ri;
        mid >>= 1;
        if(check(mid ,l , r , kth)){
            le = mid + 1;
            save = mid;
        }else{
            ri = mid - 1;
        }
    }
    return save;
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen("new.inp", "r", stdin);
    freopen("new.out" , "w" , stdout);
    cin >> t;
    while(t--){
        cin >> n;
        
        divseq = sqrt(n);
        m = 0;
        int z = 1;
        for(int i = 1 ; i <= n ; i ++){
            cin >> a[i];
            m ++;
            b[m] = a[i];
            mark[i] = z;
            if(i % divseq == 0){
                z ++;
            }
        }
        cin >> q;
        for(int i = 1 ; i <= q ; i ++){
            cin >> qu[i].type;
            if(qu[i].type == 1){
                cin >> qu[i].x >> qu[i].k;
                m ++;
                b[m] = qu[i].k;
            }else{
                cin >> qu[i].x >> qu[i].y >> qu[i].k;
            }
        }
        sort(b + 1 , b + m + 1);
        pos[1] = 1;
        value[1] = a[1];
        d = 1;
        for(int i = 2 ; i <= m ; i ++){
            if(b[i] != b[i - 1]){
                d ++;
            }
            pos[i] = d;
            value[d] = b[i];
        }
        for(int i = 1 ; i <= mark[n] ; i ++){
            for(int j = 1 ; j <= d ; j ++){
                bit[j][i] = 0;
            }
        }
        int tmp;
        for(int i = 1 ; i <= n ; i ++){
            tmp = binarysearch(a[i]);
            update(tmp ,mark[i] , 1);
        }
        for(int i = 1 ; i <= q ; i ++){
            if(qu[i].type == 1){
                tmp = binarysearch(a[qu[i].x]);
                update(tmp , mark[qu[i].x] , -1);
                a[qu[i].x] = qu[i].k;
                tmp = binarysearch(a[qu[i].x]);
                update(tmp , mark[qu[i].x] , 1);
            }
            if(qu[i].type == 0){
                cout << value[find_val(qu[i].x ,  qu[i].y , qu[i].k)] << '\n';
            }
        }
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