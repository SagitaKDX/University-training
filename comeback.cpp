// #pragma GCC optimize("Ofast")
// #pragma optimize("unroll-loops")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
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
const long long INF = 1e18 + 7;
const int MAXN=  2e5 + 7;
const int MOD = 1e9 + 7;
struct seg_tree{
    ll val;
    ll laz;
} st[MAXN * 4];
int n , q;
struct item{
    int type;
    int val;
} qu[MAXN];

vector<ll> ans;
void build(int id , int l , int r){
    st[id].val = 0;
    st[id].laz = 0;
    if(l == r){
        return;
    }
    int mid = l + r;
    mid >>= 1;
    build(id << 1 , l , mid); build(id << 1 | 1 , mid + 1 , r);    
}

void push_down(int id ,int l , int r , int mid){
    if(st[id << 1].val != 0){
        st[id << 1].laz += st[id].laz;
        st[id << 1].val += st[id].laz;
    }
    if(st[id << 1 | 1].val != 0){
        st[id << 1 | 1].val += st[id].laz;
        st[id << 1 | 1].laz += st[id].laz;
    }
    st[id].laz = 0;
}

void update_point(int id , int l , int r , int pos , int val){
    if(l == r){
        st[id].val += val;
        return;
    }
    int mid = l + r;
    mid >>= 1; 
    if(st[id].laz != 0){
        push_down(id , l , r , mid);
    }
    if(pos <= mid){
        update_point(id << 1 , l , mid , pos , val);
    }else{
        update_point(id << 1 | 1 , mid + 1 , r , pos , val);
    }
    st[id].val = max(st[id << 1].val , st[id << 1 | 1].val);
}
void update_range(int id , int l , int r , int u , int v , int val){
    if(u > r || l > v){
        return ;
    }
    if(u <= l && r <= v){
        if(st[id].val != 0){
            st[id].val += val;
            st[id].laz += val;
        }
        return ;
    }
    int mid = l + r;
    mid >>= 1;
    if(st[id].laz != 0){
        push_down(id , l , r , mid);
    }
    if(st[id << 1].val != 0)
        update_range(id << 1 , l , mid , u , v , val);
    if(st[id << 1 | 1].val != 0)
        update_range(id << 1 | 1 , mid + 1, r , u , v , val);
    st[id].val = max(st[id << 1].val , st[id << 1 | 1].val);
}

void query(int id , int l , int r , int u , int v , int p){
    if(l > v || r < u || st[id].val  < p){
        return;
    }
    if(l == r){
        if(st[id].val == p){
            st[id].val = 0;
        }
        return;
    }
    int mid = l + r;
    mid >>=1;
    if(st[id].laz != 0){
        push_down(id , l , r , mid);
    }
    if(!(st[id << 1].val < p))
        query(id << 1 , l , mid , u , v , p);
    if(!(st[id << 1 | 1].val < p))
        query(id << 1 | 1 , mid + 1 , r , u , v , p);
    st[id].val = max(st[id << 1].val , st[id << 1 | 1].val);
}

void get(int id , int l , int r){
    if(st[id].val == 0){
        return;
    }
    if(l == r){
        ans.push_back(st[id].val);
        return ;
    }
    int mid = l + r;
    mid >>= 1;
    if(st[id].laz != 0){
        push_down(id , l , r , mid);
    }
    
    if(st[id << 1].val != 0){
        get(id << 1 , l , mid);
    }
    if(st[id << 1 | 1].val != 0){
        get(id << 1 | 1 , mid + 1 , r);
    }
    return;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    freopen("new.inp" , "r" , stdin);
    freopen("new.out" , "w" , stdout);
    read(q);
    n = 0;
    for(int i = 1 ; i <= q ; i ++){
        read(qu[i].type); read(qu[i].val);
        if(qu[i].type == 1){
            n ++;
        }
    }
    build(1 , 1 , n);
    int num = 0;
    for(int i = 1 ; i <= q; i ++){
        if(qu[i].type == 1){
            num ++;
            update_point(1 , 1 , n , num , qu[i].val);
        }
        if(qu[i].type == 2){
            update_range(1 , 1, n , 1 , num , qu[i].val);
        }
        if(qu[i].type == 3){
            query(1 , 1 , n , 1 , num , qu[i].val);
        }
    }
    get(1 , 1 , n);
    cout << ans.size() << '\n';
    for(ll v : ans){
        cout << v  << " ";
    }
    return 0;
}
