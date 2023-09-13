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
const ll MAXN = 1e5 + 7;
const ll MOD = 1e9 + 7;
vector<pair<int , ll >> adj[MAXN];
int n , m;
bool vis[MAXN];
struct item{
    int node;
    ll val ;
    int cnt;
    int min_num_flight;
    int max_num_flight;
    bool operator < (const item &other) const{
        return val > other.val;
    }
};
item dis[MAXN];
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    // freopen("new.inp" , "r" , stdin);
    // freopen("new.out" , "w" , stdout);
    read(n); read(m);
    int u , v;
    ll c;
    for(int i = 1 ; i <= m ; i ++){
        read(u); read(v); read(c);
        adj[u].push_back({v , c});
    }
    for(int i = 1 ; i <= n ; i ++){
        dis[i].cnt = 0;
        dis[i].max_num_flight = -INF;
        dis[i].min_num_flight = INF;
        dis[i].val = INF;
        dis[i].node = i;
    }
    dis[1].cnt = 1;
    dis[1].max_num_flight = 0;
    dis[1].min_num_flight = 0;
    dis[1].val = 0;
    item k;
    k.cnt = 1;
    k.max_num_flight = 0;
    k.min_num_flight = 0;
    k.node = 1;
    k.val = 0;
    priority_queue<item > qu;
    qu.push(k);
    while(!qu.empty()){
        k = qu.top();
        qu.pop();
        if(vis[k.node]) continue;
        vis[k.node] = true;
        for(pair<int , int > e : adj[k.node]){
            if(dis[e.first].val == dis[k.node].val + e.second){
                dis[e.first].cnt += dis[k.node].cnt % MOD;
                dis[e.first].cnt %= MOD;
                if(dis[e.first].max_num_flight < dis[k.node].max_num_flight + 1){
                    dis[e.first].max_num_flight = dis[k.node].max_num_flight + 1;
                }
                if(dis[e.first].min_num_flight > dis[k.node].min_num_flight + 1){
                    dis[e.first].min_num_flight = dis[k.node].min_num_flight + 1;
                }
            }
            if(dis[e.first].val > dis[k.node].val + e.second){
                dis[e.first].val = dis[k.node].val + e.second;
                dis[e.first].cnt = dis[k.node].cnt ;
                dis[e.first].max_num_flight = dis[k.node].max_num_flight + 1;
                dis[e.first].min_num_flight = dis[k.node].min_num_flight + 1;
                item h;
                h = dis[e.first];
                qu.push(h);
            }
        }
    }
    write(dis[n].val); putchar(' ');
    write(dis[n].cnt); putchar(' ');
    write(dis[n].min_num_flight); putchar(' ');
    write(dis[n].max_num_flight); putchar('\n');
    return 0;
}