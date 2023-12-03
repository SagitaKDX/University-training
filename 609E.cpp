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

struct query{
    int u , v , w , id;
};
query q[MAXN];

int n , m ;
int par[MAXN] , T[MAXN][19] , depth[MAXN];
int maximumw[MAXN][19] ;
ll result[MAXN];
vector<pair<int , int >> adj[MAXN];
bool check[MAXN];
ll mst = 0;

bool cmp(query a , query b){
    return a.w < b.w;
}

int findpar(int u){
    return par[u] < 0 ? u : par[u] = findpar(par[u]);
}
bool join(int u , int v){
    u = findpar(u);
    v = findpar(v);
    if(u == v){
        return false;
    }
    if(par[u] > par[v]){
        swap(u , v);
    }
    par[u] += par[v];
    par[v] = u;
    return true;
}

void DFS(int u , int pre , int w){
    depth[u] = depth[pre] + 1;
    T[u][0] = pre;
    if(u != 1){
        maximumw[u][0] = w;
        for(int i = 1 ; i <= 17 ; i ++){
            T[u][i] = T[T[u][i - 1]][i - 1];
            maximumw[u][i] = max(maximumw[T[u][i - 1]][i - 1] , maximumw[u][i - 1]);
        }
    }
    for(auto[v , w] : adj[u]){
        if(v == pre){
            continue;
        }
        DFS(v , u , w);
    }
}
int LCA(int u , int v){
    int maxi = 0;
    if(depth[u] <= depth[v]){
        swap(u , v);
    }
    for(int i = 17 ; i >= 0 ; i --){
        if(depth[T[u][i]] >= depth[v]){
            maxi = max(maxi , maximumw[u][i]);
            u = T[u][i];
        }
    }
    if(u == v){
        return maxi;
    }
    for(int i = 17 ; i >= 0 ; i --){
        if(T[u][i] != T[v][i]){
            maxi = max(maxi , maximumw[u][i]);
            maxi = max(maxi , maximumw[v][i]);
            u = T[u][i];
            v = T[v][i];
        }
    }
    maxi = max(maxi , maximumw[u][0]);
    maxi = max(maxi , maximumw[v][0]);
    return maxi;
}
signed main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    // freopen("new.inp" , "r" , stdin);
    // freopen("new.out" , "w" , stdout);
    cin >> n  >> m;
    int u , v;
    for(int i = 1 ; i <= n ; i ++){
        par[i] = -1;
    }
    for(int i =  1 ; i <= m ; i ++){
            cin >> q[i].u >> q[i].v >> q[i].w;
            q[i].id = i;
    }
    sort(q + 1 , q + m + 1 , cmp);
    for(int i = 1 ; i <= m ; i ++){
        if(join(q[i].u , q[i].v)){
            mst += q[i].w;
            adj[q[i].u].push_back({q[i].v , q[i].w});
            adj[q[i].v].push_back({q[i].u , q[i].w});
            check[q[i].id] = true;
        }
    }
    DFS(1 , 0 , 0);
    for(int i = 1 ; i <= m ; i ++){
        if(check[q[i].id]){
            result[q[i].id] = mst;
        }else{
        
            result[q[i].id] = mst - LCA(q[i].u , q[i].v) + q[i].w;
        }
    }
    for(int i = 1 ; i <= m ; i ++){
        cout << result[i] << '\n';
    }
    return 0;

}