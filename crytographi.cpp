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
const ll MAXN = 2e5 + 7 ;
const ll INF = 1e18 + 7;
int n , m;
ll r;
struct Matrix {
    ll mat[2][2];
    Matrix() {
        memset(mat, 0, sizeof(mat));
    }
    Matrix operator * (const Matrix &other){
        Matrix ans;
        for(int u = 0 ; u < 2 ; u ++){
            for(int v = 0 ; v < 2 ; v ++){
                for(int i = 0 ; i < 2 ; i ++){
                    ans.mat[u][v] += 1ll * mat[u][i] * other.mat[i][v] % r;
                    ans.mat[u][v] %= r;
                }
            }
        }
        return ans;
    }
} st[MAXN * 4] , a[MAXN];
void build(int id , int l , int r){
    if(l == r){
        st[id] = a[l];
        return;
    }
    int mid = l + r;
    mid >>= 1;
    build(id << 1 , l , mid);
    build(id << 1 | 1 , mid + 1 , r);
    st[id] = st[id << 1] * st[id << 1 | 1];
}
Matrix get_matrix(int id , int l , int r , int u , int v){
    if(u > r || v < l){
        Matrix k;
        k.mat[0][0] = 1;

        k.mat[1][1] = 1;
        return k;
    }
    if(u <= l && r <= v){
        return st[id];
    }
    int mid = l + r;
    mid >>= 1;
    Matrix k = get_matrix(id << 1 , l , mid , u , v);
    Matrix h = get_matrix(id << 1 | 1 , mid + 1 , r , u , v);
    return k * h;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // freopen("new.inp" , "r" , stdin);
    // freopen("new.out" , "w" , stdout);
    cin >> r >> n >> m;
    for(int i = 1 ; i <= n ; i ++){
        for(int u = 0 ; u < 2 ; u ++){
            for(int v = 0 ; v < 2 ; v++){
                cin >> a[i].mat[u][v];
            }
        }
    }
    build(1 , 1 , n);
    int u , v;
    Matrix g;
    for(int i = 1 ; i <= m ; i ++){
        cin >> u >> v;
        g = get_matrix(1 , 1 , n , u , v);
        for(int j = 0 ; j < 2 ; j ++){
            for(int k = 0 ; k < 2 ; k ++){
                cout << g.mat[j][k] << " ";
            }
            cout << '\n';
        }
        cout << '\n';
    }
    return 0;
}
