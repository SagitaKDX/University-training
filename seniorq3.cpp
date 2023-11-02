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
const ll INF = 1e18;
const ll MAXN = 1e6 + 7;
ll f[MAXN] , maxl[MAXN] , maxr[MAXN] ,m , n ;
struct item{
    ll dp , pos;
};
int main(){
    // freopen("new.inp" , "r" , stdin);
    // freopen("new.out" , "w" , stdout);
    ll res = 0;
    read(n);
    for(int i = 0 ; i < n ; i ++){
        string st;
        getline(cin , st);
        m = st.size();
        for(int j = 0 ; j < st.size() ; j ++){
            if(st[j] == 'A'){
                f[j] ++;
            }
            if(st[j] == 'R'){
                f[j] = 0;
            }
        }
        vector<item>q;
        for(int i =  0 ; i < m ; i ++){
            while(!q.empty() && q.back().dp >= f[i]){
                q.pop_back();
            }
            maxl[i] = (q.empty())? -1 : q.back().pos;
            q.push_back({f[i] , i});
        }
        q.clear();
        for(int i = m - 1 ; i >= 0 ; i --){
            while(!q.empty() && q.back().dp >= f[i]){
                q.pop_back();
            }
            maxr[i] = (q.empty()) ? m : q.back().pos;
            q.push_back({f[i] , i});
        }
        for(int i = 0 ; i < m ; i ++){
            maximize(res , f[i] * (maxr[i] - maxl[i] - 1));
        }

    }
    write(res);
    return 0;
}
