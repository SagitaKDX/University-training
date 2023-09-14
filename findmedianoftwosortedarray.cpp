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
const int INF = 1e6 + 7;
const ll MOD = 1e9 + 7;
const ll MAXN = 1e5 + 7;
const ll BASE = 2e3 + 7;
struct item{
    int l , r;
    int laz;
    int num;
};
item st[BASE * 4];
int b[BASE] ,  v[BASE] , pos[BASE];
void push_down(int id){
    int t;
    t = st[id].laz;
    st[id << 1].laz += t;
    st[id << 1].l += t;
    st[id << 1].r += t;
    st[id << 1 | 1].laz += t;
    st[id << 1 | 1].l += t;
    st[id << 1 | 1].r += t;
    st[id].laz = 0;
    return;
}
void rebuild(int id , int l , int r){
    st[id].l = 0;
    st[id].r = 0;
    st[id].num = 0;
    st[id].laz = 0;
    if(r == l){
        return;
    }
    int mid = l + r;
    mid >>= 1;
    rebuild(id << 1 , l , mid);
    rebuild(id << 1 | 1 , mid + 1 , r);
}
void update(int id , int l , int r , int u , int v , int type){
    if(u > r || l > v){
        return;
    }
    if(u <= l && r <= v){
        // 0 add newvalue
        // 1 resize the tree
        if(type == 0){
            st[id].num ++;
            if(st[id].num == 1){
                st[id].l += 1;
            }
            st[id].r = st[id].l + st[id].num - 1;
        }
        if(type == 1){
            st[id].l += 1;
            st[id].r += 1;
            st[id].laz += 1;
        }
        return;
    }
    push_down(id);
    int mid = l + r;
    mid >>= 1;
    update(id << 1 , l , mid , u , v , type);
    update(id << 1 | 1 , mid + 1 , r , u , v , type);
    st[id].num = st[id << 1].num + st[id << 1 | 1].num;
    st[id].l = st[id << 1].l;
    st[id].r = st[id << 1 | 1].r;
}
int find(int id ,int l , int r, int pos){
    if(l == r){
        return l;
    }
    push_down(id);
    int mid = l + r;
    mid >>= 1;
    if(st[id << 1].l <= pos && pos <= st[id << 1].r){
        return find(id << 1 , l , mid , pos);
    }
    return find(id << 1 | 1 , mid + 1 , r , pos);
}
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size() + nums2.size() ;
        for(int i = 0 ; i < nums1.size() ; i ++){
            b[i + 1] = nums1[i];
        }
        for(int i = 0 ; i < nums1.size() ; i ++){
            b[i + 1 + nums1.size()] = nums2[i];
        }
        sort(b + 1 , b + n + 1);
        int d = 1;
        for(int i = 1 ; i <= n ; i ++){
            if(i >= 2 && b[i] != b[i - 1]){
                d++;
            }
            v[d] = b[i];
            pos[i] = d;
        }
        rebuild(1 , 1 , d);
        for(int i = 1 ; i <= n ; i ++){
            update(1 , 1 ,d ,pos[i] , pos[i] , 0);
            if(pos[i] < d){
                update(1 , 1 , d , pos[i] + 1 , d , 1);
            }
        }
        double cur = 0;
        if(n % 2 == 1){
            cur = v[find(1 , 1 , d , (n / 2) + 1)];
        }else{
            cur = v[find(1 , 1 , d , (n / 2))];
            cur += v[find(1 , 1 , d , (n / 2) + 1)];
            cur /= 2;
        }
        return cur;
    }
};
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    freopen("new.inp" , "r" , stdin);
    freopen("new.out" , "w" , stdout);
    int x;
    Solution ngu;
    vector<int > v1 , v2;
    for(int i = 1 ; i <= 2 ; i ++){
        cin >> x;
        v1.push_back(x);
    }
    for(int i = 1 ; i <= 2 ; i ++){
        cin >> x;
        v2.push_back(x);
    }
    cout << ngu.findMedianSortedArrays(v1 , v2);
    return 0;
}
