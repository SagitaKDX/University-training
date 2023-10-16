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
struct point{
    int x,y;
    point(int _x,int _y){
        x=_x;
        y=_y;
    }
    point(){}
};
int n;
bool cmp(point x , point y){
    return x.x < y.x || (x.x == y.x && x.y < y.y );
}
point p[MAXN];
class Solution {
public:
    int maxPoints(vector<vector<int>>& points) {
        n = points.size();
        for(int i = 0 ; i < n ; i ++){
            p[i + 1] = point(points[i][0] , points[i][1]);
        }
        sort(p + 1 , p + n + 1 , cmp);
        int res = 0;
        point k;
        int cur_gcd ;
        for(int i = 1 ; i <= n ; i ++){
            vector<point> v;
            for(int j = 1 ; j <= n ; j ++){
                if(i < j){
                    k.x = p[j].x - p[i].x;
                    k.y = p[j].y - p[i].y;
                    cur_gcd = GCD(k.x , k.y);
                    k.x /= cur_gcd;
                    k.y /= cur_gcd;
                    v.pb(k);
                }else{
                    if(i == j){
                        continue;
                    }else{
                        k = point(p[i].x - p[j].x , p[i].y - p[j].y);
                        cur_gcd = GCD(k.x , k.y);
                        k.x /= cur_gcd;
                        k.y /= cur_gcd;
                        v.pb(k);
                    }
                }
            }
            int num = 1;
            sort(v.begin() , v.end() , cmp);
            for(int j = 0 ; j < v.size() ; j ++){
                if(j > 0 && v[j].x == v[j - 1].x && v[j].y == v[j - 1].y){
                    num ++;
                }else{
                    num = 1;
                }
                res = max(res , num + 1);
            }
        }
        return res;
    }
};
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    freopen("new.inp" , "r" , stdin);
    freopen("new.out" , "w" , stdout);
    vector<vector<int>> v;
    for(int i = 0 ; i < 3 ; i ++){
        vector<int> tmp;
        for(int i =0  ; i < 2 ; i ++){
            int x;
            cin >> x;
            tmp.pb(x);
        }
        v.pb(tmp);
    }
    Solution s;
    cout << s.maxPoints(v);
    return 0;

}