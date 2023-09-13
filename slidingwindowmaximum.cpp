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
const ll BASE = 2e4 + 7;
int n , d = 0;
int b[MAXN] , v[MAXN] , g[MAXN];
struct item{
    int val;
    int num;
};
item st[BASE * 4];
void rebuild(int id , int l , int r){
    st[id].num = 0;
    st[id].val = -INF;
    if(l == r){
        return ;
    }
    int mid = l + r;
    mid >>= 1;
    rebuild(id << 1 , l , mid);
    rebuild(id << 1 | 1 , mid + 1 , r);
}
void update(int id , int l , int r , int pos , int type){
    if(l  == r){
        // type = 0 insert new value
        // type = 1 delete value
        if(type == 0){
            st[id].num += 1;
            st[id].val = g[l];
            // cout << g[pos] << '\n';
        }
        if(type == 1){
            st[id].num -= 1;
            st[id].val = (st[id].num == 0)? -INF : st[id].val;
        }
        return ;
    }
    int mid = l + r;
    mid >>= 1;
    if(pos <= mid){
        update(id << 1 , l , mid , pos , type);
    }else{
        update(id << 1 | 1 , mid + 1 , r , pos , type);
    } 
    st[id].val = max(st[id << 1].val , st[id << 1 | 1].val);
    st[id].num = st[id << 1].num + st[id << 1 | 1].num;
}
int binarysearch(int val){
    int l = 1 , r = n;
    while(l <= r){
        int mid = l + r;
        mid >>= 1;
        if(b[mid] == val){
            return v[mid];
        }
        if(b[mid] > val){
            r = mid - 1;
        }else{
            l = mid + 1;
        }
    }
    return 0;
}
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        n = nums.size();
        for(int i = 0 ; i < nums.size() ; i ++){
            b[i + 1] = nums[i];
        }
        sort(b + 1 , b + n + 1);
        d = 1;
        for(int i = 1 ; i <= n ; i ++){
            if(i >= 2 && b[i] != b[i - 1]){
                d ++;
            }
            v[i] = d;
            g[d] = b[i];
        }
        int z ;
        for(int i = 0 ; i < k ; i ++){
           z = binarysearch(nums[i]);
           update(1 , 1 , d , z , 0);
        }
        vector<int > res;
        res.push_back(st[1].val);
        for(int i = k ; i < nums.size() ; i ++){
            z = binarysearch(nums[i - k]);
            update(1 , 1 , d , z , 1);
            z = binarysearch(nums[i]);
            update(1 , 1 , d , z , 0);
            
            res.push_back(st[1].val);
        }
        for(int i = nums.size() - k ; i  < nums.size() ; i ++){
             z = binarysearch(nums[i]);
            update(1 , 1 , d , z , 1);
        }
        return res;   
    }
};
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    freopen("new.inp" , "r" , stdin);
    freopen("new.out" , "w" , stdout);
    int t , h;
    cin >> t;
    Solution sol;
    vector<int > ve;
    for(int i = 1 ; i <= t ; i ++){
        cin >> h;
        ve.push_back(h);
    }
    ve = sol.maxSlidingWindow(ve , 3);
    for(int i = 0 ; i < ve.size() ; i ++){
        cout << ve[i] << " ";
    }
    return 0;
}
