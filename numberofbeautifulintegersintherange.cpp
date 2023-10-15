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
int dp[17][17][17][2][21];
int cur_k;
string tostring(int val){
    string res = "";
    if(val == 0){
        return res = "0";
    }
    while(val != 0){
        res += (val % 10) + '0';
        val /= 10;
    }
    reverse(res.begin() , res.end());
    return res;
}
int calc(string st , int idx , int cntodd , int cnteven , bool smaller , bool zero , int mod){
    if(idx == st.length()){
        if(cntodd == cnteven && !zero && mod == 0 ){
            return 1;
        }else{
            return 0;
        }
    }
    if(dp[idx][cntodd][cnteven][smaller][mod] != -1){
        return dp[idx][cntodd][cnteven][smaller][mod];
    }
    int res = 0;
    int limit = (smaller) ? 9 : st[idx] - '0';
    for(int digit = 0 ; digit <= limit ; digit ++){
        if(digit == 0){
            res += calc(st , idx + 1 , cntodd + (digit % 2 == 1) , cnteven + (digit % 2 == 0 && (!zero)) , smaller || (digit < st[idx] - '0'), zero , (mod * 10 + digit) % cur_k);
        }else{
            res += calc(st , idx + 1 , cntodd + (digit % 2 == 1) , cnteven + (digit % 2 == 0) , smaller || (digit < st[idx] - '0'), false , (mod * 10 + digit) % cur_k);
        }
    }
    dp[idx][cntodd][cnteven][smaller][mod] = res;
    return res;
}
int solve(int a){
    string st = tostring(a);
    int ls = st.size() - 1;
    // cout << st << '\n';
    memset(dp , -1 , sizeof(dp));
    return calc(st , 0 , 0 , 0 , 0 , 1,0);
}
class Solution {
public:
    int numberOfBeautifulIntegers(int low, int high, int k) {
        cur_k = k;
        return solve(high) - solve(low - 1);
    }
};
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    freopen("new.inp" , "r" , stdin);
    freopen("new.out" , "w" , stdout);
    int l , r ,k;
    cin >> l >> r >> k;
    Solution s;
    cout << s.numberOfBeautifulIntegers(l , r , k);
    return 0;

}