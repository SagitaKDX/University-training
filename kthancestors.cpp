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
const ll MAXN = 1e6 + 7;
const ll MOD = 1e9 + 7;
const ll MAXVAL = 1e5 + 7;
struct item{
    int type;
    int u , v;
};
item a[MAXN];
int q;
vector<int> adj[MAXN];
int b[MAXN] ,pos[MAXN] , v[MAXVAL];
int n , cnt , d;

int T[MAXVAL][20] , h[MAXVAL];
bool check[MAXVAL];
void dfs(int u , int p){
    T[u][0] = p;
    h[u] = h[p] + 1;
    if(p != -1)
    for(int i = 1 ; i < 18 ; i ++){
        T[u][i] = T[T[u][i - 1]][i - 1];
    }
    for(int i = 0 ; i < adj[u].size() ; i ++){
        int v = adj[u][i];
        if(v != p && v <= d){
            dfs(v , u);

        }
    }
}

int binarylifting(int u , int k){
    for (int j = 0; (1 << j) <= k; ++j)
        if (k >> j & 1) u = T[u][j];
    return u;
}
int binarysearch(int val){
    int l = 1 , r = cnt;
    int mid;
    while(l <= r){
        mid = (l + r) >> 1;
        if(b[mid] == val) return pos[mid];
        if(b[mid] < val) l = mid + 1;
        else r = mid - 1;
    }
    return 0;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);     
    freopen("new.inp" , "r" , stdin);
    freopen("new.out" , "w" , stdout);
    int t;
    cin >> t;
    int root;
    int type;
    while(t--){
        cin >> n;

        for(int i = 1 ; i <= n; i ++){
            cin >> a[i].u >> a[i].v;
            a[i].type = 3;
            if(a[i].v == 0){
                root = a[i].u;
                continue;
            }
            cnt ++;
            b[cnt] = a[i].v;
            cnt ++;
            b[cnt] = a[i].u;
        }
        cin >> q;
        for(int i = n + 1 ; i <=n + q ; i ++){
            cin >> a[i].type;
            if(a[i].type == 0){
                cin >> a[i].v>> a[i].u;
                cnt ++;
                b[cnt] = a[i].v;
                cnt ++;
                b[cnt] = a[i].u;
            }
            if(a[i].type == 1){
                cin >> a[i].u;
                cnt ++;
                b[cnt] = a[i].u;
            }
            if(a[i].type == 2){
                cin >> a[i].u >> a[i].v;
                cnt++  ;
                b[cnt] = a[i].u;
            }
        }
        sort(b + 1 , b + cnt + 1 );
        d = 1 ;
        for(int i = 1 ; i <= cnt ; i ++){
            if(i > 1 && b[i] != b[i - 1]){
                d ++;
            }
            pos[i] = d;
            v[d] = b[i];
        }
        for(int i = 1 ; i <= n ; i ++){
            if(a[i].v == 0){
                continue;
            }
            a[i].v = binarysearch(a[i].v);
            a[i].u = binarysearch(a[i].u);
            adj[a[i].v].push_back(a[i].u);
            check[a[i].v] = true;
            check[a[i].u] = true;
        }
        for(int i = n + 1 ; i <= n + q ; i ++){
            if(a[i].type == 0){
                a[i].v = binarysearch(a[i].v);
                a[i].u = binarysearch(a[i].u);
                // adj[a[i].v].push_back(a[i].u);
            }
            if(a[i].type == 1){
                a[i].u = binarysearch(a[i].u);
            }
            if(a[i].type == 2){
                a[i].u = binarysearch(a[i].u);
            }
        }
        cout << d << '\n'; 
        root = binarysearch(root);
        dfs(root , -1);
        // for(int i = n + 1 ; i <= n + q ; i ++){
        //     if(a[i].type == 0 && check[a[i].v] == true){
        //         check[a[i].u] = true;

        //     }
        //     if(a[i].type == 1){
        //         check[a[i].u] = false;
        //     }
        //     if(a[i].type == 2){
        //         if(check[a[i].u] == false || h[a[i].u] < a[i].v - 1){
        //             cout << 0 << '\n';
        //         }else{
        //             cout << v[binarylifting(a[i].u , a[i].v)] << '\n';
        //         }
        //     }
        // }
        // for(int i = 1 ; i <= d ; i++){
        //     adj[i].clear();
        // }
        // memset(check , false , sizeof(check));
        // memset(T , 0 , sizeof(T));
        // memset(h , 0 , sizeof(h));
    }
    return 0;
}
