#include <bits/stdc++.h>
#include<vector>
using namespace std;

using ll = long long;
using db = long double; // or double, if TL is tight
using str = string; // yay python!

using pi = pair<int,int>;
using pl = pair<ll,ll>;
using pd = pair<db,db>;

using vi = vector<int>;
using vb = vector<bool>;
using vl = vector<ll>;
using vd = vector<db>;
using vs = vector<str>;
using vpi = vector<pi>;
using vpl = vector<pl>;
using vpd = vector<pd>;

#define tcT template<class T
#define tcTU tcT, class U
// ^ lol this makes everything look weird but I'll try it
tcT> using V = vector<T>;
tcT, size_t SZ> using AR = array<T,SZ>;
tcT> using PR = pair<T,T>;

// pairs
#define mp make_pair
#define f first
#define s second

// vectors
// oops size(x), rbegin(x), rend(x) need C++17
#define sz(x) int((x).size())
#define bg(x) begin(x)
#define all(x) bg(x), end(x)
#define rall(x) x.rbegin(), x.rend()
#define sor(x) sort(all(x))
//#define rsz resize
#define ins insert
#define ft front()
#define bk back()
#define pb push_back
#define eb emplace_back
#define pf push_front
#define rtn return

#define lb lower_bound
#define ub upper_bound
tcT> int lwb(V<T>& a, const T& b) { return int(lb(all(a),b)-bg(a)); }

// loops
#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i,a) ROF(i,0,a)
#define rep(a) F0R(_,a)
#define each(a,x) for (auto& a: x)
#include<bits/stdc++.h>

using namespace std;

//Vtype
using ll = long long;
using ld = long double;
using str = string;

//Vpairs
using pi = pair<int,int>;
using pl = pair<ll,ll>;
using pd = pair<db,db>;

//Vvector
using vi = vector<int>;
using vb = vector<bool>;
using vl = vector<ll>;
using vd = vector<db>;
using vs = vector<str>;
using vpi = vector<pi>;
using vpl = vector<pl>;
using vpd = vector<pd>;
#define pb push_back
#define sz size()

//pairs
#define mp make_pair
#define f first
#define s second

// loops
#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i,a) ROF(i,0,a)
#define cont continue
#define bre break
#define fastio ios_base::sync_with_stdio(false); cin.tie(0);
// FILE I/O
void setIn(str s) { freopen(s.c_str(),"r",stdin); }
void setOut(str s) { freopen(s.c_str(),"w",stdout); }
void setIO(str s) {
    setIn(s+".inp"); setOut(s+".out");
}
#define N 402
int C[N][N];
int T[N][N];


int main() {
    fastio;
    setIO("new");
    FOR(i,1,N+1) FOR(j,1,N+1) C[i][j] = 1e9;
    FOR(i,1,N+1) C[i][i] = 0;
    int n, m, q;
    cin >> n >> m ;
    FOR(i,1,m+1){
        int u, v, w;
        cin >> u >> v >> w;
        C[u][v] = w;
        T[u][v] = v;
        T[v][u] = u;
    }

    FOR(k,1,n+1) FOR(i,1,n+1) FOR(j,1,n+1) {
        if (C[i][j] > C[i][k] + C[k][j]) {
            C[i][j] = C[i][k] + C[k][j];
            T[i][j] = T[i][k];
        }
    }
    cin >> q;
    FOR(i,1,q+1) {
        int u,v;
        cin  >> u >> v;
        cout << C[u][v];
        if(C[u][v] == 1e9){
            cout << - 1 << '\n';
            cont;
        }
        cout << '\n';
    }
}
