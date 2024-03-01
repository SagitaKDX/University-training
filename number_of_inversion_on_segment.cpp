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
const ll MAXN = 1e5 + 7 ;
const ll MOD = 1e8;
const ll INF = 1e18 + 7;
int n , m;
int a[MAXN];
struct item{
    int num ;
    ll val;
    int laz;
};
item st[MAXN * 4][41];
void push_down(int id , int type){
    ll t = st[id][type].laz;
    st[id << 1][type].val += st[id << 1][type].num * t;
    st[id << 1 | 1][type].val += st[id << 1 | 1][type].num * t;
    st[id << 1][type].laz += t;
    st[id << 1 | 1][type].laz += t;
    st[id][type].laz = 0;
}

void update(int id , int idx, int l , int r , int u , int v , ll val , int type){
    if(u > r || l > v || l > r){
        return;
    }
    if(type == 1 && st[id][idx].num == 0){
        return;
    }
    if(u <= l && r <= v){
        if(type == 0){
            st[id][idx].num += val;
        }
        if(type == 1){
            if(st[id][idx].num != 0){
                st[id][idx].val += val * st[id][idx].num;
                st[id][idx].laz += val;
            }
        }
        if(type == 2){
            st[id][idx].num = 0;
            st[id][idx].val = 0;
        }
        return;
    }
    if(st[id][idx].laz != 0){
        push_down(id , idx);
    }
    int mid = l + r;
    mid >>= 1;
    update(id << 1 , idx , l , mid , u , v , val , type);
    update(id << 1 | 1 , idx ,  mid + 1 , r , u , v , val , type);
    st[id][idx].val = st[id << 1][idx].val + st[id << 1 | 1][idx].val;
    st[id][idx].num = st[id << 1][idx].num + st[id << 1 | 1][idx].num;
}

ll get_val(int id , int idx , int l , int r , int u , int v , int type){    
    if(l > r){
        return 0;
    }
    if(l > v || r < u){
        return 0;
    }
    if(st[id][idx].num == 0){
        return 0;
    }
    if(u <= l && r <= v){
        return type == 0 ? st[id][idx].num : st[id][idx].val;
    }
    int mid = l + r;
    mid >>= 1;
    if(st[id][idx].laz != 0){
        push_down(id , idx);
    }
    return get_val(id << 1 , idx , l , mid , u , v , type) + get_val(id << 1 | 1 , idx , mid + 1 , r , u , v , type);
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("new.inp" , "r" , stdin);
    freopen("new.out" , "w" , stdout);
    read(n); read(m);
    ll num = 0;
    for(int i = 1 ; i <= n ; i ++){
        read(a[i]);
        num = 0;
        for(int j = 40 ; j >= a[i] ; j --){
            if(j == a[i]){
                update(1 , j , 1 , n , i , i , 1 ,  0); 
                update(1 , j , 1,  n , i , i ,   num , 1);
                break;
            }
            num += get_val(1 , j , 1 , n , 1 , i , 0);
        }
        
    }
    int type  , u , v;
    ll res = 0;
    for(int i = 1 ; i <= m ; i ++){
        read(type); read(u); read(v);
        if(type - 1){
            update(1 , a[u] , 1 , n , u , u , 0 , 2);
            if(u != n){
                for(int j = a[u] - 1 ; j >= 1 ; j --){
                        update(1 , j , 1 , n , u + 1  , n , -1 , 1);
                }
            }
            a[u] = v;
            num = 0;
            for(int j = 40 ; j >= a[u] ; j --){
                if(j == a[u]){
                    update(1 , j , 1 , n , u , u , 1 , 0);
                    update(1 , j , 1 , n , u , u , num , 1);
                    break;
                }
                if(u > 1){
                    num += get_val(1 , j , 1 , n , 1 , u - 1 , 0);
                }
            }
            if(u != n){
                for(int j = a[u] - 1 ; j >= 1 ; j --){
                    if(st[1][j].num != 0){
                        update(1 , j , 1 , n , u + 1  , n , 1 , 1);
                    }
                }
            }
        }else{
            res = 0;
            num = 0;
            for(int j = 40 ; j >= 1 ; j --){
                if(j == 1){
                    res += get_val(1 , j , 1 , n , u , v, 1) ;  
                    res -= get_val(1 , j , 1 , n , u , v , 0) * num;
                    break;
                }else{
                    res += get_val(1 , j , 1 , n , u , v, 1) ;
                    res -= get_val(1 , j , 1 , n , u , v , 0) * num;
                }
                if(u > 1){
                    num += get_val(1 , j , 1 , n , 1 , u - 1 , 0);
                }
            }
            write(res);
            putchar('\n');
        }
    }
    return 0;
}
