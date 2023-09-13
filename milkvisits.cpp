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
const ll INF = 1e18 + 7;
const ll MAXN = 1e5 + 7;
vector<int > adj[MAXN];
int chainhead[MAXN];
int n , u , v , q;
int chainind[MAXN];
int nchain , nbase , posinbase[MAXN] , con[MAXN];
int par[MAXN];
int st[MAXN * 4];
int color[MAXN];
int depth[MAXN] , T[MAXN][20] ;

void update(int id , int l , int r ,int pos ,  int val){
    if(l == r){
        st[id] = val;
        return;
    }
    int mid = l + r;
    mid >>= 1;
    if(pos <= mid){
        update(id << 1 , l , mid ,  pos , val);
    }else{
        update(id << 1 | 1 , mid + 1 , r , pos , val);
    }
    st[id] = max(st[id << 1] , st[id << 1 | 1]);
}



int get(int id , int l , int r , int u , int v){
    if(l > v || u > r){
        return 0;
    }
    if(u <= l && r <= v){
        return st[id];
    }
    int mid = l + r;
    mid >>= 1;
    return max(get(id << 1 , l , mid , u , v) , get(id << 1 | 1 ,  mid + 1 , r , u , v));
}

void dfs(int u , int pre ){
    depth[u] = depth[pre] + 1;
    T[u][0] = pre;
    con[u] = 1;
    par[u] = pre;
    for(int i = 1; i < 18; i++)
    T[u][i] = T[T[u][i - 1]][i - 1];
    for(auto v : adj[u]){
			 if(v == pre) continue;

            dfs(v , u );
            con[u] += con[v];   
    }
}


int lca(int u ,int v){
         if(depth[u] < depth[v])
		 swap(u, v);
		 for(int i = 17; i >= 0; i--)
		 if(depth[T[u][i]] >= depth[v])
		 u = T[u][i];
		 if(u == v) return u;
		 for(int i = 17; i >= 0; i--)
			 if(T[u][i] != T[v][i]) {
				 u = T[u][i];
				 v = T[v][i];
			 }
		 return T[u][0];
}



void HLD(int u , int pre){
    if(chainhead[nchain] == 0){
        chainhead[nchain] = u;
    }   
    chainind[u] = nchain;
    posinbase[u] = ++nbase;
    int maxvt = -1;
    for(int i = 0 ; i < adj[u].size() ; i ++){
        int v = adj[u][i];
        if(v != pre){
            if(maxvt == -1 || con[v] > con[maxvt]){
                maxvt = v;
            }
        }
    }
    if(maxvt >  -1){
        HLD(maxvt , u);
    }
    for(int i = 0 ; i < adj[u].size() ; i ++){
        int v = adj[u][i];
        if(v != pre){
            if(v != maxvt){
                nchain ++;
                HLD(v , u);
            }
        }
    }
}

 void updateval(int u , int v){
    int uchain = chainind[u] ;
    int achain = chainind[v];
    while(true){
        if(uchain == achain){
            update(1 , 1 , nbase , posinbase[u] , (color[u]));
            break;
        }
    }
 }



 int findup(int u , int v , int val){
    int uchain = chainind[u];
    int vchain = chainind[v];
    int zz;
    zz = 0;
    int  g;
    while(true){
        if(uchain == vchain){
            g =  get(1 , 1, nbase , posinbase[v] , posinbase[u]);
            zz = max(zz , g);
            return zz;
            break;
        }
        g = get(1 , 1 , nbase , posinbase[chainhead[uchain]] , posinbase[u]);
        zz = max(zz , g);
        if(zz == val){
            return zz;
        }
        u = par[chainhead[uchain]];
        uchain = chainind[u];
    }

 }



struct item{
    int u , v;
    int type;
    int color;
};
int res[MAXN * 2];
bool cmp(item u , item v){
    if(u.color == v.color){
        return u.type < v.type;
    }
    return u.color < v.color;
}
vector<item > query;
signed main(){
    // ios_base::sync_with_stdio(false);
    // cin.tie(0);
    freopen("milkvisits.inp" , "r" , stdin);
    freopen("milkvisits.out" , "w" , stdout);
    read(n); read(q);
    item k;
    for(int i = 1 ; i <= n ; i ++){
        read(color[i]);
        k.color = color[i];
        k.type = i;
        query.push_back(k);
    }
    for(int i = 1 ; i <= n - 1; i ++){
        read(u); read(v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1 , 0);
    nchain = 1;
    HLD(1 , 0);
    int a , b , c;
    for(int i = 1 ; i <= q ; i ++){
        read(a); read(b); read(c);
        k.u = a;
        k.v = b;
        k.color = c;
        k.type = i + n;
        query.push_back(k);
    }    
    sort(ALL(query) , cmp);
    int cur , z;
    for(int i = 0 ; i < query.size() ; i ++){
        if(query[i].type <= n){
            updateval(query[i].type , query[i].type);
        }else{
            cur = lca(query[i].u , query[i].v);
            z = findup(query[i].u , cur , query[i].color);
            if(z  == query[i].color){
                res[query[i].type] = 1;
            }
            z = findup(query[i].v , cur , query[i].color);
            if(z  == query[i].color){
                res[query[i].type] = 1;
            }
        }
    }
    for(int i = n + 1 ; i <= q   + n ; i ++){
        write(res[i]);
    }
    return 0;   
}
