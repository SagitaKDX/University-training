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
const ll N = 1e5 + 5;
int n;
ll c[N], res[N], mx[N];
vector<ll> g[N];

void dfs(int u, int p, map<int, int>& large) {
    res[u] = c[u];
    mx[u] = 1;
    large[c[u]]++;

    for (auto v : g[u]) if (v != p) {
        map<int, int> small;
        dfs(v, u, small);

        if (small.size() > large.size()) {
            swap(large, small);
            res[u] = res[v];
            mx[u] = mx[v];
        }

        for (auto p : small) {
            large[p.first] += p.second;

            int val = large[p.first];
            if (val > mx[u]) {
                mx[u] = val;
                res[u] = p.first;
            }
            else if (val == mx[u]) res[u] += p.first;
        }
    }
}

signed main() {

    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    // freopen("new.inp" , "r" , stdin);
    // freopen("new.out" , "w" , stdout);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> c[i];
    for (int i = 1, x, y; i < n; i++) {
        cin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }

    map<int, int> mp;
    dfs(1, 0, mp);
    for (int i = 1; i <= n; i++) cout << res[i] << " ";

}