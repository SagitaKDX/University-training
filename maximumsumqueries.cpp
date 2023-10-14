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
const ll MAXN = 2e5 + 7;
const ll MOD = 1e9 + 7;
int num2[MAXN] , pos[MAXN];
int res[MAXN] , st[MAXN * 4];
int n , d;
struct offline_queries{
    int x , y , id , type;
};
bool cmp(offline_queries a , offline_queries b){
    if(a.x == b.x){
        if(a.y == b.y){
            return a.type > b.type;
        }
        return a.y > b.y;
    }
    return a.x > b.x;
}
void rebuild(int id , int l , int r ){
    st[id] = 0;
    if(l == r){
        return;
    }
    int mid = (l + r) >> 1;
    rebuild(id << 1 , l , mid);
    rebuild(id << 1 | 1 , mid + 1 , r);
}

void update(int id , int l , int r , int pos , int val){
    if(l == r){
        if(st[id] < val){
            st[id] = val;
        }
        return;
    }
    int mid = (l + r) >> 1;
    if(pos <= mid){
        update(id << 1 , l , mid , pos , val);
    }else{
        update(id << 1 | 1 , mid + 1 , r , pos , val);
    }
    st[id] = max(st[id << 1] , st[id << 1 | 1]);

}

int get(int id , int l , int r , int u , int v){
    if(l > v || r < u){
        return 0;
    }
    if(u <= l && r <= v){
        return st[id];
    }
    int mid = (l + r) >> 1;
    return max(get(id << 1 , l , mid , u , v) , get(id << 1 | 1 , mid + 1 , r , u , v));
}
int binarysearch(int val){
    int l = 1 , r = n;
    int mid ;
    while(l <= r){
        int mid = l + r;
        mid >>= 1;
        if(num2[mid] == val){
            return pos[mid];
        }
        if(num2[mid] > val){
            r = mid - 1;
        }else{
            l = mid + 1;
        }
    }
    return 0;
}
offline_queries q[MAXN * 2];
class Solution {
public:
    vector<int> maximumSumQueries(vector<int>& nums1, vector<int>& nums2, vector<vector<int>>& queries) {
        n = nums1.size();
        for(int i = 0 ; i < n ; i ++){
            num2[i + 1] = nums2[i];
            q[i + 1].type = 1;
            q[i + 1].x = nums1[i];
            q[i + 1].y = num2[i + 1];
        } 
        for(int i = 0 ; i < queries.size() ; i ++){
            q[n + i  + 1].type = 0;
            q[n + i + 1].x = queries[i][0];
            q[n + i + 1].y = queries[i][1];
            q[n + i + 1].id = i + 1;
            num2[n + i + 1] = queries[i][1];
        }
        n += queries.size();
        sort(q + 1 , q + n + 1 , cmp);
        sort(num2 + 1 , num2 + n  + 1 );
        ll sum = 0;
        vector<int > ans;
        d = 1;
        sort(num2 + 1 , num2 + n + 1);
        for(int i = 1 ; i <= n ; i ++){
            if(i > 1 && num2[i] != num2[i - 1]){
                d ++;
            }
            pos[i] = d;
        }
        rebuild(1 , 1 , d);
        for(int i = 1 ; i <= n ; i ++){
            if(q[i].type == 1){
                update(1  , 1 , d , binarysearch(q[i].y) , q[i].x + q[i].y);
            }else{
                res[q[i].id] = get(1 , 1 , d , binarysearch(q[i].y) , d);
            }
        }
        for(int i = 1 ; i <= queries.size() ; i ++){
            ans.push_back(res[i] == 0 ? -1 : res[i]);
        }
        return ans;
    }
};
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    freopen("new.inp" , "r" , stdin);
    freopen("new.out" , "w" , stdout);
    vector<int> nums1 , nums2;
    for(int i = 1 ; i <= 4 ; i ++){
        int x;
        cin >> x;
        nums1.push_back(x);
    }
    for(int i = 1 ; i <= 4 ; i ++){
        int x;
        cin >> x;
        nums2.push_back(x);
    }
    vector<vector<int>> queries;
    for(int i = 1 ; i <= 3 ; i ++){
        vector<int> tmp;
        for(int j = 1 ; j <= 2 ; j ++){
            int x;
            cin >> x;
            tmp.push_back(x);
        }
        queries.push_back(tmp);
    }
    Solution s;
    s.maximumSumQueries(nums1 , nums2 , queries);
    return 0;

}