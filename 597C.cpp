#include <bits/stdc++.h>
using namespace std;
#define ll long long
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
const ll MOD = 1e9 + 7;
ll bit[MAXN][12];
int n , k;
int a[MAXN];
void update(int idx , int id , ll val){
    for( ; idx <= n ; idx += idx & (-idx)){
        bit[idx][id] += val;
    }
}

ll get(int idx , int id){
    ll sum = 0 ;
    for( ; idx > 0 ; idx -= idx & (-idx)){
        sum += bit[idx][id];
    }
    return sum;
}

ll get_range(int l , int r , int id){
    return get(r , id) - get(l - 1 , id);
}

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    freopen("new.inp" , "r" , stdin);
    freopen("new.out" , "w" , stdout);
    cin >> n  >> k;
    k ++ ;
    for(int i = 1 ; i <= n ; i ++){
        cin >> a[i];
    }
    ll tmp = 0;
    ll sum = 0;
    for(int i = 1 ; i <= n ; i ++){
        update(a[i] , 1 , 1);
        for(int j = 2; j <= k ; j ++){
            if(a[i] > 1){
                tmp = get_range(1 , a[i] - 1 , j - 1);
                update(a[i] , j  , tmp);
            }
        }
    }
    for(int i = 1 ; i <= n ; i ++){
        tmp = get_range(a[i] , a[i] , k);
        sum += tmp;
    }
    (k == 1) ? cout << n : cout << sum;
    return 0;

}