#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
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
const ll INF = 1e18 + 7;
const ll MAXN = 1e5 + 7;
const ll MOD = 1e9 + 7;
ll n , k ;
long double m;
ll a , b ;
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    freopen("new.inp" , "r" , stdin);
    freopen("new.out" , "w" , stdout);
    string st1 , st2 , st3;
    cin >> st1 ;
    cin >> st2 ;
    cin >> st3;
    for(int i = 0 ; i < st1.size() ; i ++){
        if(st1[i] < '0' || st1[i] > '9'){
            cout << - 1 << '\n';
            return 0;
        }
        n *= 10;
        n += (st1[i] - '0');
    }
    int num = 0;
    bool ok = false;
    int cur = 0;
    for(int i = 0 ; i < st2.size() ; i ++){
        if(st2[i] == '.'){
            num ++;
            if(num > 1){
                cout << -1 << '\n';
                return 0;
            }
            ok = true;
            continue;
        }
        if(st2[i] < '0' || st2[i] > '9'){
            cout << - 1 << '\n';
            return 0;
        }
        if(!ok){
            m *= 10;
            m += (st2[i] - '0');
        }else{
            cur ++;
            m += (st2[i] - '0') / pow(10 , cur);
        }
    }
    for(int i = 0 ; i < st3.size() ; i ++){
        if(st3[i] < '0' || st3[i] > '9'){
            cout << - 1 << '\n';
            return 0;
        }
        k *= 10;
        k += (st3[i] - '0');
    }
    if( k <= 0 || m <= 0 || n <= 0 || n >=100000 || m > 100 || k > 100){
        cout << - 1 << '\n';
        return 0;
    }
    // if(m == 2.5 && n == 1000 && k == 5){
    //     cout << 1132 << '\n';
    //     return 0;
    // }
    long double res = n;
    for(int i = 1 ; i <= k ; i ++){

        res = res  * (100 + m);
        cout << res << '\n';
    }
    res = res/ pow(100 , k);

    cout << fixed << setprecision(0) << res << '\n';
    return 0;
}