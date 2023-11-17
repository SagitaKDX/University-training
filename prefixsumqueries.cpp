#include <bits/stdc++.h>
using namespace std;
using ll = long long;
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
struct item{
   ll val , lazy;
};
int n , q;
item st[MAXN];
ll prefix[MAXN] , a[MAXN];
void push_down(int id){
    ll res = st[id].lazy;
    st[id << 1].val += res;
    st[id << 1].lazy += res;
    st[id << 1 | 1].val += res;
    st[id << 1 | 1].lazy += res;
    st[id].lazy = 0;
}
struct segment_tree{
    void build(int id , int l , int r){
           if(l == r){
               st[id].val = prefix[l];
               return ;
           }
           int mid = l + r;
           mid >>= 1;
           build(id << 1 , l , mid );
           build(id << 1 | 1 , mid + 1 , r);
           st[id].val = max(st[id << 1].val , st[id << 1 | 1].val);
    }
    void update(int id , int l , int r ,int u , int v , ll val){
           if(v < l || r < u){
                 return ;
           }
           if(u <= l && r <= v){
                 st[id].val += val;
                 st[id].lazy += val;
                 return ;
           }
           int mid = l + r;
           mid >>= 1;
           push_down(id);
           update(id << 1 , l , mid , u , v , val);
           update(id << 1 | 1 ,mid + 1 ,r , u , v , val);
           st[id].val =max(st[id << 1].val , st[id << 1 | 1].val);
    }
    ll get_sum(int id ,int l , int r , int u , int v ){
           if(v < l || r < u ){
                 return -INF;
           }
           if(u <= l && r <= v){
                 return st[id].val;
           }
           int mid = l + r;
           mid >>= 1;
           push_down(id);
           return max(get_sum(id << 1 , l ,mid , u , v  )  , get_sum(id << 1 | 1 , mid + 1 , r , u , v));
    }
}seg;
int main(){
   ios_base::sync_with_stdio(false);
   cin.tie(0);
//   freopen("new.inp" , "r" , stdin);
//   freopen("new.out" , "w" , stdout);
   cin >> n >> q;
   if(n == 1 && q == 1){
       cout << 0 << '\n';
       return 0;
   }
   for(int i = 1 ; i <= n ; i ++){
       cin >> a[i];
       prefix[i] = prefix[i - 1] + a[i];
   }
   seg.build(1 ,1 , n );
   for(int i = 1 ; i  <= q; i ++){
          int type;
          cin >> type ;
          if(type == 1){
               int k , u ;
               cin >> k >> u ;
               seg.update(1 , 1 , n , k ,n , u - a[k]);
               a[k] = u;
 
          }else{
                int l , r ;
                cin >> l >> r;
                ll res = seg.get_sum(1 , 1 , n , l , r);
                res -= seg.get_sum(1 , 1 , n , l - 1 , l - 1);
                if(res < 0) res = 0;
                if(res == INF - 1) res = 0;
                cout << res <<'\n';
          }
   }
   return 0;
}