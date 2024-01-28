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
ll LCM(ll a , ll b){
    return a*b / GCD(a, b);
}
const ll MAXN = 1e5 +7;
int n;
int a[MAXN];
int last_val[MAXN];
bool check[MAXN];
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    freopen("new.inp" , "r" , stdin);
    freopen("new.out" , "w" , stdout);
    cin >> n;
    string st;
    cin >> st;
    for(int i = 1 ; i <= n ; i ++){
        a[i] = st[i - 1] - 'a';
        a[i] ++;
    }
    int res_k = 1;
    int res_l = 1;
    int res_le = 1;
    int res_ri = 1;
    for(int k = 1 ; k <= 26 ; k++){
        for(int i = 1 ; i <= max(n , 26) ; i ++){
            check[i] = false;
            last_val[i] = 0;
        }
        int le = 1;
        last_val[a[1]] = 1;
        check[1] = true;
        int num = 1;
        int max_l = k == 1 ? 1: -1;
        int save_l = k == 1 ? 1 : -1;
        int save_r = k == 1 ? 1 : -1;
        for(int ri = 2 ; ri <= n ; ri ++){
            if(num + (last_val[a[ri]] == 0 ) > k){
                while(le <= ri && num + 1 > k){
                    if(le == ri){
                        break;
                    }
                    if(check[le] ==  true){
                        num --;
                        last_val[a[le]] = 0;
                        check[le] = false;
                    }
                    le ++;
                }
                if(last_val[a[ri]] == 0){
                    num ++;
                    if(num == k){
                        save_l = (ri - le + 1 > max_l) ? le : save_l;
                        save_r = (ri - le + 1 > max_l) ? ri : save_r;
                        max_l =  (ri - le + 1 > max_l) ? ri - le + 1 : max_l;
                    }
                    last_val[a[ri]] = ri;
                    check[ri] = 1;
                }
            }else{
                num += check[last_val[a[ri]]] == 0;
                check[last_val[a[ri]]] = 0;
                check[ri] = 1;
                last_val[a[ri]] = ri;
                if(num == k){
                    save_l = (ri - le + 1 > max_l) ? le : save_l;
                    save_r = (ri - le + 1 > max_l) ? ri : save_r;
                    max_l =  (ri - le + 1 > max_l) ? ri - le + 1 : max_l;
                }
            
            }
        }
        if(max_l != -1){
            if(1ll * res_k * 1ll * (LCM(res_l , max_l) / res_l)  >1ll * k * 1ll * (LCM(res_l , max_l) / max_l)){
                res_k = k;
                res_l = max_l;
                res_le = save_l;
                res_ri = save_r;
            }
        }
    }

    cout << res_le << " " << res_ri << '\n';
    return 0;
}