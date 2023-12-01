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
int n;
int a[MAXN];
int l[MAXN] , r[MAXN];
int ans[MAXN];
signed main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    freopen("new.inp" , "r" , stdin);
    freopen("new.out" , "w" , stdout);
    cin >> n;
    deque<int> dq;
    for(int i = 1 ; i <= n ; i ++){
        cin >> a[i];
    }
    for(int i = 1 ; i <= n ; i ++){
        while(!dq.empty() && a[dq.back()] >= a[i]){
            dq.pop_back();
        }
        if(dq.empty()){
            l[i] = 1;
        }else{
            l[i] = dq.back() + 1;
        }
        dq.push_back(i);
    }
    while(!dq.empty()){
        dq.pop_back();
    }
    for(int i = n ; i >= 1 ; i --){
        while(!dq.empty() && a[dq.back()] >= a[i]){
            dq.pop_back();
        }
        if(dq.empty()){
            r[i] = n;
        }else{
            r[i] = dq.back() - 1;
        }
        dq.push_back(i);
    }
    for(int i = 1 ; i <= n ; i ++){
        int len = r[i] - l[i] + 1;
        ans[len] = max(ans[len] , a[i]);
    }
    for(int i = n ; i >= 1 ; i --){
        ans[i] = max(ans[i + 1] , ans[i]);
    }
    for(int i = 1 ; i <= n ; i ++){
        cout << ans[i] << ' ';
    }
    return 0;

}