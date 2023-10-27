#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

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
const ll MAXN=  5e6 + 7;
const ll MOD = 1e9 + 7;
int n , k;
int a[MAXN];
map<int , int >mpa;
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    freopen("new.inp" , "r" , stdin);
    freopen("new.out" , "w" , stdout);
    cin >> n >> k;
    int num = 0;
    for(int i = 1 ; i <= n ; i ++){
        cin >> a[i];
        mpa[a[i] % k] ++;
    }
    for(int i = 1 ; i <= n ; i ++){
        if(a[i] % k == 0 && mpa[a[i] % k] != 0){
            num ++;
            mpa[a[i] % k] = 0;
            continue;
        }
        int tmp = k - a[i] % k;
        if(tmp == a[i] % k){
            if(mpa[tmp] != 1){
                num ++;
                mpa[tmp] = 0;
                continue;
            }else{
                continue;  
            }
        }
        if(mpa[tmp] > mpa[a[i] % k]){
            continue;
        }else{
            num += mpa[a[i] % k];
            // cout << num << " " << a[i] << '\n';
            mpa[a[i] % k] = 0;
            mpa[tmp] = 0;
        }
    }
    cout << num << '\n';
    return 0;
}
