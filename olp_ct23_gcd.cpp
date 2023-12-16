#include <bits/stdc++.h>

using namespace std;
typedef long long  ll;
typedef long double ld;


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
const ll INF = 1e18;
const ll MAXN = 1e6 + 7;
const ll MOD=1e9 + 7;
ll a , b , M;
ll fib[MAXN];
ll sum=0;
ll n;
struct Matrix {
    ll mat[2][2];
    Matrix() {
        memset(mat, 0, sizeof(mat));
    }
    Matrix operator * (const Matrix &other){
        Matrix ans;
        for(int u = 0 ; u <= 1 ; u ++){
            for(int v = 0 ; v <= 1;  v++){
                for(int i = 0 ; i <= 1; i ++){
                    ans.mat[u][v] += 1ll * mat[u][i] * 1ll * other.mat[i][v] % M;
                    ans.mat[u][v] %= M;
                }
            }
        }
        return  ans;
    }
};
 
Matrix POW(Matrix x, ll n){
    if (n == 1) return x;
    Matrix ans = POW(x, n / 2);
    ans = ans * ans;
    if (n % 2) return ans * x;
    else return ans;
}
 
ll solve(ll n){
    if (n == 0 || n == 1) return n  ;
    Matrix ans;
    ans.mat[0][0] = 1;
    ans.mat[1][0] = 1;
    ans.mat[0][1] = 1;
    ans.mat[1][1] = 0;
    ans = POW(ans, n - 1);
    return (ans.mat[0][0] % M + ans.mat[0][1]) % M;
}

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    freopen("new.inp" , "r" , stdin);
    freopen("new.out" , "w" , stdout);
    cin >> a >> b >> M;
    if(a <= 50 && b <= 50 && M <= 50){
        fib[0] = 0;
        fib[1] = 1;
        for(int i = 2 ; i <= a ; i ++){
            fib[i] = fib[i - 1] + fib[i - 2];
        }
        ll res = fib[a];
        fib[0] = 0;
        fib[1] = 1;
        for(int i = 2 ; i <= b ; i ++){
            fib[i] = fib[i - 1] + fib[i - 2];
        }
        res = GCD(res , fib[b] );
        cout << res % M << '\n';
        return 0;
    }
    cout << solve(GCD(a , b ) - 1) % M << '\n';
    return 0;    
}