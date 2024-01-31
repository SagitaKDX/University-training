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
const ll MAXN = 2e3 + 7 ;
const ll MOD = 1e9 + 7;
const ll INF = 1e18 + 7;

struct point{
    int x , y;
};

struct priority_qu{
    point p;
    ll dis;
    bool operator < (const priority_qu &other) const{
        return dis > other.dis;
    }
};

point start , endd;

int dx[] = {1 , 0 , 0 , -1};
int dy[] = {0 , 1 , -1 , 0};
int r , s;
int a[MAXN][MAXN];
ll dis[MAXN][MAXN];
point trace[MAXN][MAXN];
bool vis[MAXN][MAXN];

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    freopen("new.inp" , "r" , stdin);
    freopen("new.out" , "w" , stdout);
    cin >> r >> s;
    string st;
    for(int i = 1 ; i <= r ; i ++){
        cin >> st;
        for(int j = 0 ; j < s ; j ++){
            a[i][j + 1] = (st[j] == 'o')? 4 : a[i][j + 1];// start
            a[i][j + 1] = (st[j] == 'x')? 5 : a[i][j + 1];// end
            a[i][j + 1] = (st[j] == '.')? 6 : a[i][j + 1];// empty
            a[i][j + 1] = (st[j] == '<')? 2 : a[i][j + 1];// left
            a[i][j + 1] = (st[j] == '>')? 1 : a[i][j + 1];// right
            a[i][j + 1] = (st[j] == '^')? 3 : a[i][j + 1];// up
            a[i][j + 1] = (st[j] == 'v')? 0 : a[i][j + 1];// down
            if(a[i][j + 1] == 4){
                start.x = i;
                start.y = j + 1;
            }
            if(a[i][j + 1] == 5){
                endd.x = i;
                endd.y = j + 1;
            }
        }
    }
    for(int i = 1 ; i <= r; i ++){
        for(int j = 1 ; j <= s ; j ++){
            dis[i][j] = INF;
            vis[i][j] = false;
        }
    }
    priority_queue<priority_qu> pq;
    dis[start.x][start.y] = 0;
    pq.push({start , 0});
    while(!pq.empty()){
        point k = pq.top().p;
        pq.pop();
        if(vis[k.x][k.y]) {
            continue;
        }
        vis[k.x][k.y] = true;
        if(k.x == endd.x && k.y == endd.y){
            break;
        }
        for(int i = 0 ; i < 4 ; i ++){
            point v;
            v.x = k.x + dx[i];
            v.y = k.y + dy[i];
            if(v.x < 1 || v.y < 1 || v.x > r || v.y > s){
                continue;
            }
            if(dis[k.x][k.y] + (a[k.x][k.y] != i && k.x != start.x && k.y != start.y) < dis[v.x][v.y]){
                dis[v.x][v.y] = dis[k.x][k.y] + (a[k.x][k.y] != i && (k.x != start.x || k.y != start.y));
                trace[v.x][v.y] = k;
                pq.push({v , dis[v.x][v.y]});
            }
        }
    }
    cout << dis[endd.x][endd.y] << '\n';
    point base = endd;
    while(base.x != start.x || base.y != start.y){
        int valx = base.x - trace[base.x][base.y].x;
        int valy = base.y - trace[base.x][base.y].y;
        if(trace[base.x][base.y].x == start.x && trace[base.x][base.y].y == start.y){
            break;
        }
        for(int i = 0 ; i < 4 ; i ++){
            if(valx == dx[i] && valy == dy[i]){
               if(a[trace[base.x][base.y].x][trace[base.x][base.y].y] != i){
                    a[trace[base.x][base.y].x][trace[base.x][base.y].y] = i;
               }
            }
        }
        base = trace[base.x][base.y];
    }
    for(int i = 1 ; i <= r ; i ++){
        for(int j = 1 ; j <= s ; j ++){
            if(a[i][j] == 0){
                cout << 'v';
            }
            if(a[i][j] == 1){
                cout << '>';
            }
            if(a[i][j] == 2){
                cout << '<';
            }
            if(a[i][j] == 3){
                cout  << '^';
            }
            if(a[i][j] == 4){
                cout << 'o';
            }
            if(a[i][j] == 5){
                cout << 'x';
            }
            if(a[i][j] == 6){
                cout << '.';
            }
        }
        cout << '\n';
    }

    return 0;
}