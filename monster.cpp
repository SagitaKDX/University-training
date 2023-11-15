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

// #define s second
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

const ll MAXN = 1e3 + 7;
const ll INF = 1e18 + 7;
int dx[] = {0 , 1 , -1 , 0};
int dy[] = {1 , 0 , 0 , -1};

struct point{
    int x , y;
};

struct item{
    point cur;
    ll val;
    bool operator < (const item &other) const{
        return val > other.val;
    }
};

ll dis[MAXN][MAXN] , dis2[MAXN][MAXN];
bool a[MAXN][MAXN];
bool visited[MAXN][MAXN];
int n ,m ;

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    freopen("new.inp" , "r" , stdin);
    freopen("new.out" , "w" , stdout);
    cin >> n >> m;
    string st;
    priority_queue<item> qu;
    point cur;
    point start;
    for(int i = 1 ; i <= n ; i ++){
        cin >> st;
        for(int j = 0 ; j < m ; j ++){
            if(st[j] == '#'){
                a[i][j + 1] = 1;
                dis[i][j + 1] = INF;
            }else{
                a[i][j + 1] = 0;
                if(st[j] == 'A'){
                    start.x = i;
                    start.y = j + 1;
                    dis[i][j + 1] = 0;
                    dis2[i][j + 1] = INF;
                    continue;
                }   
                if(st[j] == 'M'){
                    cur.x = i;
                    cur.y = j + 1;
                    dis[i][j + 1] = INF;
                    dis2[i][j + 1] = 0;
                    qu.push({cur , 0});
                    continue;
                }
                dis[i][j + 1] = INF;
                dis2[i][j + 1] = INF;
            }
        }
    }
    ll cur_val = 0;
    point new_node ; 
    while(!qu.empty()){
        cur = qu.top().cur;
        cur_val = qu.top().val;
        qu.pop();
        if(visited[cur.x][cur.y] || dis2[cur.x][cur.y] < cur_val){
            continue;
        }
        visited[cur.x][cur.y] = true;
        for(int i = 0 ; i <= 3 ;i ++){
            new_node.x = cur.x + dx[i];
            new_node.y = cur.y + dy[i];
            if(new_node.x < 1 || new_node.y < 1 || new_node.x > n || new_node.y > m || a[new_node.x][new_node.y]){
                continue;
            }
            if(dis2[new_node.x][new_node.y] > dis2[cur.x][cur.y] + 1){
                dis2[new_node.x][new_node.y] = dis2[cur.x][cur.y] + 1;
                qu.push({new_node , dis2[new_node.x][new_node.y]});
            }
        }
    }
    for(int i = 1 ; i <= n ; i ++){
        for(int j = 1 ; j <= m ; j ++){
            visited[i][j] = false;
        }
        }
    qu.push({start , 0});
    while(!qu.empty()){
        cur = qu.top().cur;
        cur_val = qu.top().val;
        qu.pop();
        if(visited[cur.x][cur.y] || dis[cur.x][cur.y] < cur_val){
            continue;
        }
        visited[cur.x][cur.y] = true;
        for(int i = 0 ; i <= 3 ; i ++){
            new_node.x = cur.x + dx[i];
            new_node.y = cur.y + dy[i];
            if(new_node.x < 1 || new_node.y < 1|| new_node.x > n || new_node.y > m || a[new_node.x][new_node.y]){
                continue;
            }
            if(dis[new_node.x][new_node.y] > dis[cur.x][cur.y] + 1 && dis[cur.x][cur.y] + 1 < dis2[new_node.x][new_node.y]){
                dis[new_node.x][new_node.y] = dis[cur.x][cur.y] + 1;
                qu.push({new_node , dis[new_node.x][new_node.y]});
            }
        }
    }
    bool ok = false;
    for(int i = 1 ; i <= n ; i ++){
        if(a[i][1] != 1 && dis[i][1] != INF && !ok){
            cur.x = i;
            cur.y = 1;
            ok = !ok;
        }
        if(a[i][m] != 1 && dis[i][m] != INF && !ok){
            cur.x = i ;
            cur.y = m;
            ok = !ok;
        }
    }
    for(int i = 1 ; i <= m ; i ++){
        if(a[1][i] != 1 && dis[1][i] != INF && !ok){
            cur.x = 1;
            cur.y = i;
            ok = !ok;
        }
        if(a[n][i] != 1 && dis[n][i] != INF && !ok){
            cur.x = n ;
            cur.y = i;
            ok = !ok;
        }
    }
    if(!ok){
        cout << "NO";
        return 0;
    }
    cout << "YES" << '\n';
    string res;
    while(true){
        for(int j = 0 ; j <= 3 ; j ++){
            new_node.x = cur.x - dx[j];
            new_node.y = cur.y - dy[j];
            if(a[new_node.x][new_node.y]){
                continue;
            }
            if(new_node.x < 1 || new_node.y < 1 || new_node.x > n || new_node.y > m){
                continue;
            }
            if(dis[new_node.x][new_node.y] == dis[cur.x][cur.y] - 1){
                if(j == 0){
                    res = res + 'R';
                } 
                if(j == 1){
                    res = res + 'D';
                }
                if(j == 2){
                    res = res + 'U';
                }
                if(j == 3){
                    res = res + 'L';
                }
                cur = new_node;
                break;
            }
        }
        if(cur.x == start.x && cur.y == start.y){
            break;
        }
    }
    cout << res.size() << '\n' ;
    reverse(res.begin() , res.end());
    cout << res << '\n';
    return 0;    
}