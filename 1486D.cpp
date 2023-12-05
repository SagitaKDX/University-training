#include <bits/stdc++.h>
using namespace std;
#define ll long long
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
const ll MOD = 1e9 + 7;
signed main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    freopen("new.inp" , "r" , stdin);
    freopen("new.out" , "w" , stdout);
    int n , k;
    cin >> n >> k;
    vector<int> a(n);
    for (auto &i : a) cin >> i;
    int l = 1, r = n + 1;
    while (r - l > 1) {
        int m = (l + r) / 2;
        vector<int> b(n);
        for (int i = 0; i < n; ++i)
            if (a[i] >= m) {
                b[i] = 1;
            } else {
                b[i] = -1;
            }
        for (int i = 1; i < n; ++i) b[i] += b[i - 1];
        int mx = b[k - 1];
        int mn = 0;
        for (int i = k; i < n; ++i) {
            mn = min(mn, b[i - k]);
            mx = max(mx, b[i] - mn);
        }
        if (mx > 0) {
            l = m;
        } else {
            r = m;
        }
    }
    cout << l << '\n';
    return 0;

}