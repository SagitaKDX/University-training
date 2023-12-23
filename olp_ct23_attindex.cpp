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

const ll MAXN = 2e5 + 7;
const ll INF = 1e18 + 7;
int p;
string st;
ll pre[MAXN][3];
signed main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    // freopen("new.inp" , "r" , stdin);
    // freopen("new.out" , "w" , stdout);
    cin >> p;
    cin >> st;
    if(p == 2){
        pre[0][1] = 0;
        pre[0][2] = 0;
        pre[0][0] = 0;
        for(int i = 1 ; i <= st.size() ; i ++){
            pre[i][1] = pre[i - 1][1];
            pre[i][2] = pre[i - 1][2];
            pre[i][0] = pre[i - 1][0];
            if(st[i - 1] == '0' || st[i - 1] == '2' || st[i - 1] == '4' || st[i - 1] == '6' || st[i - 1] == '8'){
                pre[i][1] += pre[i - 1][0] + 1;
                pre[i][2] += 1;
            }
            if(1){
                pre[i][0] += 1;
            }
        }
        int q;
        int l , r;
        cin >> q;
        for(int i = 1 ; i <= q ; i ++){
            cin >> l >> r;
            cout << pre[r][1] - pre[l - 1][1] - pre[l - 1][0] * (pre[r][2] - pre[l - 1][2]) << '\n';
        }
        return 0;
    }
    int q;
    cin >> q;
    int l , r;
    int num = 0;
    ll res = 0;
    if(st.size() <= 100 && q <= 100){
        for(int i = 1 ; i <= q ; i ++){
            cin >> l >> r;
            num = 0;
            for(int j = l ; j <= r ; j ++){
                if(st[j - 1] != 0){
                    res = 0;
                    for(int k = j ; k <= r ; k ++){
                        res *= 10;
                        res += st[k - 1] - '0';
                        res %= p;
                        if(res == 0){
                            num ++;
                        } 
                    }  
                }
            }
            cout << num << '\n';
        }
    }
    return 0;    
}
