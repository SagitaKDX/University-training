#pragma GCC optimize("Ofast")
#pragma optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
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

const ll MAXN = 3e5 + 7;
const ll MAXQ = 5e4 + 7;
const ll INF = 1e18 + 7;
struct query{
    int l , r , type ;
} qu[MAXQ];

struct segment_tree{
    int val1 , val2;
    int laz1 , laz2;
} st[MAXN * 4];

int n , q;
int a[MAXN] , result[MAXQ];


int temp ;
void pushdown(int id , int l , int r , int mid){
    temp = st[id].laz1 ;
    st[id].laz1 = 0;
    if(temp == 1){
        st[id << 1].val1 = (mid - l + 1);
        st[id << 1].laz1 = 1;
        st[id << 1 | 1].val1 = (r - mid);
        st[id << 1 | 1].laz1 = 1;
    }
    if(temp == -1){
        st[id << 1].val1 = 0;
        st[id << 1].laz1 = -1;
        st[id << 1 | 1].val1 = 0;
        st[id << 1 | 1].laz1 = -1;
    }
    temp = st[id].laz2 ;
    st[id].laz2 = 0;
    if(temp == 1){
        st[id << 1].val2 = (mid - l + 1);
        st[id << 1].laz2 = 1;
        st[id << 1 | 1].val2 = (r - mid);
        st[id << 1 | 1].laz2 = 1;
    }
    if(temp == -1){
        st[id << 1].val2 = 0;
        st[id << 1].laz2 = -1;
        st[id << 1 | 1].val2 = 0;
        st[id << 1 | 1].laz2 = -1;
    }
    return;
}
void update(int id , int l , int r , int u , int v , int val , int type){
    if(l > r || u > r || l > v){
        return;
    }
    if(u <= l && r <= v){
        if(type == 1){
            if(val == -1){
                st[id].val1 = 0;
                st[id].laz1 = -1;
            }else{
                st[id].val1 = (r - l + 1);
                st[id].laz1 = 1;
            }
        }else{
            if(val == -1){
                st[id].val2 = 0;
                st[id].laz2 = -1;
            }else{
                st[id].val2 = (r - l + 1);
                st[id].laz2 = 1;
            }
        }
        return ;
    }
    int mid = l + r;
    mid >>= 1;
    if(st[id].laz1 != 0 || st[id].laz2 != 0){
        pushdown(id , l , r , mid);
    }
    update(id << 1 , l , mid , u , v , val , type);
    update(id << 1 | 1 , mid + 1 , r , u , v , val , type);
    st[id].val1 = st[id << 1].val1 + st[id << 1 | 1].val1;
    st[id].val2 = st[id << 1].val2 + st[id << 1 | 1].val2;
}

int get(int id , int l , int r , int u , int v , int type){
    if(l > v || u > r){
        return 0;
    }
    if(u <= l && r <= v){
        return (type == 1) ? st[id].val1  : st[id].val2 ;
    }
    int mid = l + r;
    mid >>= 1;
    if(st[id].laz1 != 0 || st[id].laz2 != 0){
        pushdown(id , l , r , mid);
    }
    if(type == 1){
        if(st[id << 1].laz1 == -1){
            if(st[id << 1 | 1].laz1 == -1){
                return 0;
            }else{
                return get(id << 1 | 1 , mid + 1 , r , u , v , type);
            }
        }else{
            if(st[id << 1 | 1].laz1 == -1){
                return get(id << 1 , l  , mid , u , v , type);
            }else{
                return get(id << 1 | 1 , mid + 1 , r , u , v , type) + get(id << 1 , l , mid , u , v , type);
            }
        }
    }
    if(type == 2){
        if(st[id << 1].laz2 == -1){
            if(st[id << 1 | 1].laz2 == -1){
                return 0;
            }else{
                return get(id << 1 | 1 , mid + 1 , r , u , v , type);
            }
        }else{
            if(st[id << 1 | 1].laz2 == -1){
                return get(id << 1 , l  , mid , u , v , type);
            }else{
                return get(id << 1 | 1 , mid + 1 , r , u , v , type) + get(id << 1 , l , mid , u , v , type);
            }
        }
    }
    // return get(id << 1 , l , mid , u , v , type) + get(id << 1 | 1 , mid + 1 , r , u , v , type);
}


signed main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    freopen("mexquery.inp" , "r" , stdin);
    freopen("mexquery.out" , "w" , stdout);
    read(n);
    for(int i = 1 ; i <= n ; i ++){
        read(a[i]);    
    }
    read(q);
    int type;
    int g = 0;
    for(int i = 1;  i <= q; i ++){
        read(type);
        if(type == 1){
            read(qu[i].l); read(qu[i].r); read(qu[i].type);
        }
        if(type == 2){
            read(qu[i].l); read(qu[i].r);
            qu[i].type = 3;
            g ++;
        }
        result[i] = -1;
    }
    int num0 = 0;
    int num1 = 0;
    int num2 = 0;
    for(int k = 0 ; k <= 30 && g > 0 ; k ++){
        update(1 , 1 , n , 1 , n , -1 , 1);
        update(1 , 1 , n , 1 , n , -1 , 2);
        for(int i = 1 ; i <= n ; i ++){
            if(a[i] > k){
                update(1 , 1 , n , i , i , 1 , 1);
            }
            if(a[i] == k){
                update(1 , 1 , n , i , i , 1 , 2);
            }
        }
        for(int i = 1 ; i <= q ; i ++){
            if(qu[i].type == 1){
                num1 = get(1 , 1 , n , qu[i].l , qu[i].r , 1);
                if(num1 != 0){
                    update(1 , 1 , n , qu[i].l , qu[i].r , -1 , 1);
                }
                num2 = get(1 , 1 , n , qu[i].l , qu[i].r , 2);
                if(num2 != 0){
                    update(1 , 1 , n , qu[i].l , qu[i].r , -1 , 2);
                }
                num0 = qu[i].r - qu[i].l + 1;
                num0 = num0 - num1 - num2;
                if(num2 != 0){
                    update(1 , 1,  n , qu[i].l + num0  , qu[i].l + num0 - 1 + num2 , 1 , 2);
                }
                if(num1 != 0){
                    update(1 , 1,  n , qu[i].l + num0 + num2, qu[i].r , 1 , 1);
                }
            }
            if(qu[i].type == 2){
                num1 = get(1 , 1 , n , qu[i].l , qu[i].r , 1);
                if(num1 != 0){
                    update(1 , 1 , n , qu[i].l , qu[i].r , -1 , 1);
                }
                num2 = get(1 , 1 , n , qu[i].l , qu[i].r , 2);
                if(num2 != 0){
                    update(1 , 1 , n , qu[i].l , qu[i].r , -1 , 2);
                }
                num0 = qu[i].r - qu[i].l + 1;
                num0 = num0 - num1 - num2;
                if(num1 != 0){
                    update(1 , 1,  n , qu[i].l  , qu[i].l + num1 - 1 , 1 , 1);
                }
                if(num2 != 0){
                    update(1 , 1,  n , qu[i].l + num1 , qu[i].l + num1 + num2 - 1 , 1 , 2);
                }
            }
            if(qu[i].type == 3){
                if(result[i] != -1){
                    continue;
                }
                if(!get(1 , 1 , n , qu[i].l , qu[i].r , 2)){
                    if(result[i] == -1){
                        result[i] = k; 
                        g--;
                    }
                }
            }
        }
    }
    for(int i = 1 ; i <= q ; i ++){
        if(qu[i].type == 3){
            if(result[i] == -1){
                write(31);
            }else{
                write(result[i]);
            }
            putchar('\n');
        }
    }

    return 0;    
}
