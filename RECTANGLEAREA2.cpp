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
struct query{
    int x , y1 , y2;
    int type;
    // type == 0 open
    // type == 1 close
};
struct segtree{
    int num;
    ll val;
};
segtree st[MAXN * 4];
query a[MAXN];
int n;
ll d , b[MAXN] , pos[MAXN] ,val[MAXN];
void rebuild(int id , int l , int r){
    st[id].num = 0;
    st[id].val = 0;
    if(l == r){
        return;
    }
    int mid = l + r;
    mid >>= 1;
    rebuild(id << 1 , l , mid);
    rebuild(id << 1 | 1 , mid + 1 , r);
}
void update(int id , int l , int r , int u , int v , int upd){
    if(l > v || r < u){
        return;
    }
    if(u <= l && r <= v){
        st[id].num += upd;
        if(st[id].num > 0){
            st[id].val = val[r] - val[l] + 1;
            st[id].val %= MOD;
        }else{
            if(l < r){
                st[id].val = st[id << 1].val + st[id << 1 | 1].val;
                st[id].val %= MOD;
            }else{
                st[id].val = 0;
            }
        }
        return;
    }
    int mid = l + r;
    mid >>= 1;
    update(id << 1 ,l , mid , u , v , upd);
    update(id << 1 | 1 , mid + 1 , r , u , v , upd);
    if(st[id].num > 0){
        st[id].val = val[r] - val[l] + 1;
        st[id].val %= MOD;
    }else{
        st[id].val = st[id << 1].val + st[id << 1 | 1].val;
        st[id].val %= MOD;
    }
}
bool cmp(query u , query v){
    if(u.x == v.x) return u.type < v.type;
    return u.x < v.x;
}
int binarysearch(ll value){
    int l = 1 , r = 2 * n;
    while(l <= r){
        int mid = l + r;
        mid >>= 1;
        if(b[mid] == value){
            return pos[mid];
        }
        if(b[mid] > value){
            r = mid - 1;
        }else{
            l = mid + 1;
        }
    }
    return 0;

}
class Solution {
public:
    int rectangleArea(vector<vector<int>>& rectangles) {
        n = rectangles.size();        
        for(int i = 0 ; i < rectangles.size() ; i ++){
            int x1 = rectangles[i][0];
            int y1 = rectangles[i][1];
            int x2 = rectangles[i][2];
            int y2 = rectangles[i][3];
            a[i + 1] = {x1 , y1 , y2 - 1, 0};
            a[n + i + 1] = {x2 , y1 , y2 - 1 , 1};
            b[i + 1] = y1;
            b[i + n + 1] =y2 - 1;
        }
        sort(a + 1 , a + 2 * n + 1 , cmp);
        sort(b + 1 , b + n * 2 + 1);
        d = 1;
        for(int i = 1; i <= n * 2 ; i ++){
            if(i > 1 && b[i] != b[i - 1]){
                d++;
            }
            pos[i] = d;
            val[d] = b[i];
        }
        rebuild(1 , 1 , d);
        ll ans = 0 ;
        for(int i = 1 ; i <=  n * 2 ; i ++){
            ans += (a[i].x - a[i - 1].x) % MOD * st[1].val  % MOD;
            ans %= MOD;
            if(a[i].type == 0){ // open
                update(1 , 1 , d ,binarysearch(a[i].y1) , binarysearch(a[i].y2) , 1);
            }else{
                update(1 , 1 , d ,binarysearch(a[i].y1) , binarysearch(a[i].y2) , -1);
            };
        }
        return ans;
    }
};

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen("new.inp" , "r" , stdin);
    freopen("new.out" , "w" , stdout);
    vector<vector<int>> ngu;
    for(int i = 0 ; i < 1 ; i ++){
        vector<int > ngu2;
        for(int j = 0 ; j < 4 ; j ++){
            int x;
            cin >> x;
            ngu2.push_back(x);
        }
        ngu.push_back(ngu2);
    }
    Solution sg;
    cout << sg.rectangleArea(ngu) << '\n';
    return 0;
}