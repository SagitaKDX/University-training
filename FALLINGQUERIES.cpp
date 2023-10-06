#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
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
const ll MAXN = 2e5 + 7;
const ll MOD = 1e9 + 7;
struct segment_tree{
    int maxx ;
    int laz;
};
int cnt  =  0 , d = 0;
int b[MAXN] , pos[MAXN] , val[MAXN] , n;

segment_tree st[MAXN * 4];
void rebuild(int id , int l , int r){
    st[id].maxx = 0;
    st[id].laz = 0;
    if(l == r){
        return ;
    }
    int mid = l + r;
    mid >>= 1;
    rebuild(id << 1 , l , mid);
    rebuild(id << 1 | 1 , mid + 1 , r);
}
void push_down(int id){
    st[id << 1].maxx = st[id].laz;
    st[id << 1].laz = st[id].laz;
    st[id << 1| 1].maxx = st[id].laz;
    st[id << 1 | 1].laz = st[id].laz;
    st[id].laz = 0;
}
void update(int id , int l , int r , int u , int v , ll val){
    if(l > v || r < u){
        return;
    }
    if(u <= l && r <= v){
        st[id].maxx = val;
        st[id].laz = val;
        return;
    }
    int mid = l + r;
    mid >>= 1;
    if(st[id].laz != 0){
        push_down(id);
    }
    update(id << 1 , l , mid , u , v , val);
    update(id << 1 | 1 , mid + 1 , r , u , v , val);
    st[id].maxx = max(st[id << 1].maxx , st[id << 1 | 1].maxx);
}
ll get(int id , int l , int r , int u , int v){
    if(l > v || r < u){
        return 0;
    }
    if(u <= l && r <= v){
        return st[id].maxx;
    }
    int mid = l + r;
    mid >>= 1;  
    if(st[id].laz != 0){
        push_down(id);
    }
    return max(get(id << 1 , l , mid , u , v) , get(id << 1 | 1 , mid + 1 , r , u , v));
}
int binarysearch_segtree_left(int id , int l , int r , int u , int v , ll val){
    if(l > v || r < u){

    }

}
int binarysearch(int val){
    int l = 1 , r = cnt;
    while(l <= r){
        int mid = l + r;
        mid >>= 1;
        if(val == b[mid]){
            return pos[mid];
        }
        if(val > b[mid]){
            l = mid + 1;
        }else{
            r = mid - 1;
        }
    }
    return 0;
}
class Solution {
public:
    vector<int> fallingSquares(vector<vector<int>>& positions) {
        n = positions.size();
        cnt = 0;
        for(int i = 0 ; i < n ; i ++){
            cnt ++;
            b[cnt] = positions[i][0];
            cnt ++;
            b[cnt] = positions[i][1] + positions[i][0] - 1;
        }
        sort(b + 1,  b + cnt + 1);
        d = 1;
        for(int i = 1 ; i <= cnt ; i ++){
            if(i >= 2 && b[i] != b[i -1]){
                d ++;
            }
            pos[i] = d;
            val[d] = b[i];
        }
        rebuild(1 , 1 , d);
        vector<int> ans;
        for(int i = 1 ; i <= n ; i ++){
            int l = binarysearch(positions[i - 1][0]);
            int r = binarysearch(positions[i - 1][0] + positions[i - 1][1] - 1);
            int maxx = get(1 , 1, d  , l , r);
            update(1 , 1 , d , l , r ,maxx + positions[i - 1][1]);
            ans.push_back(st[1].maxx);
        }
        return ans;
    }
};
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen("new.inp" , "r" , stdin);
    freopen("new.out" , "w" , stdout);
    Solution sg;
    vector<vector<int>> a;
    for(int i = 1 ; i <= 3 ; i ++){
        vector<int > tmp;
        for(int i = 0 ; i < 2 ; i ++){
            int x;
            cin >> x;
            tmp.push_back(x);
        }
        a.push_back(tmp);
    }
    vector<int > ans;
    ans = sg.fallingSquares(a);
    for(int v : ans){
        cout << v << ' ';  
    }
    return 0;

}