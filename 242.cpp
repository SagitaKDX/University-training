#include<bits/stdc++.h>
using namespace std;
#define ll long long
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
long long GCD(ll a , ll b){
    while(b != 0 ){
         a = a % b;
         long long tmp = a;
         a = b;
         b = tmp;
    }
    return a;
}
#define BIT(x, i) (((x) >> (i)) & 1)
#define MASK(i) (1LL << (i))
#define ONBIT(x, i) ((x) | MASK(i))
const ll MAXN = 1e5 + 7;
const ll MOD = 1e9 + 7;
int a[MAXN];
int m , n;
struct item{
    int val , laz;
} st[MAXN * 4][21];

void push_down(int id ,int powe , int l , int r , int mid){
    int t = st[id][powe].laz;
    st[id << 1][powe].val = (mid - l + 1) - st[id << 1][powe].val;
    st[id << 1][powe].laz = st[id << 1][powe].laz ^ t;
    st[id << 1 | 1][powe].val = (r - mid) - st[id << 1 | 1][powe].val;
    st[id << 1 | 1][powe].laz = st[id << 1 | 1][powe].laz ^ t;
    st[id][powe].laz = 0;
}

void add_val(int id , int powe , int l , int r , int pos , int val){
    if(l == r){
        st[id][powe].val += val;
        return;
    }
    int mid = l + r;
    mid >>= 1;
    if(pos <= mid){
        add_val(id << 1, powe , l , mid , pos , val);
    }else{
        add_val(id << 1 | 1 , powe , mid + 1 , r , pos , val);
    }
    st[id][powe].val = st[id << 1][powe].val  + st[id << 1 | 1][powe].val;
}

void update(int id , int powe , int l , int r , int u , int v , int val){
    if(u > r || l > v){
        return ;
    }
    if(u <= l && r <= v){
        st[id][powe].val = (r - l + 1) - st[id][powe].val;
        st[id][powe].laz = st[id][powe].laz ^ 1;
        return ;
    }
    int mid = l + r;
    mid >>= 1;
    if(st[id][powe].laz){
        push_down(id , powe , l , r , mid);
    }
    update(id << 1 , powe , l , mid , u , v , val);
    update(id << 1 | 1 , powe , mid + 1 , r , u , v, val);
    st[id][powe].val = st[id << 1][powe].val + st[id << 1 | 1][powe].val;
}


int get(int id , int powe ,int l , int r , int u , int v){
    if(l > v || u > r){
        return 0;
    }
    if(u <= l && r <= v){
         return st[id][powe].val;
    }
    int mid = l + r;
    mid >>= 1;
    if(st[id][powe].laz){
        push_down(id , powe , l , r , mid);   
    }
    return get(id << 1 ,powe ,l ,mid ,u ,v) + get(id << 1 | 1 , powe , mid + 1 , r , u , v);
}

void process(int pos , int val){
    int num = val; 
    int cal = 0;
    while(val != 0){
        num = val % 2;
        add_val(1 , cal , 1 , n , pos , num);
        cal ++;
        val /= 2;
    }
}
int main(){
    // ios_base::sync_with_stdio(false);
    // cin.tie(0);
    freopen("new.inp" , "r" , stdin);
    freopen("new.out" , "w" , stdout);
    read(n);
    for(int i = 1 ; i <= n ; i++){
        read(a[i]);
        process(i , a[i]);
    }
    int m;
    read(m);
    int type;
    int l , r , val;
    int num , cal;
    cal = 0;
    for(int i = 1 ; i <= m ; i ++){
        read(type);
        if(type == 2){
            cal = 0;
            read(l); read(r); read(val);
            while(val != 0){
                if(val % 2){
                    update(1 , cal , 1 , n , l , r , 1);
                }
                cal += 1;
                val /= 2;
            }
        }else{
            read(l); read(r);
            ll sum = 0;
            for(int j = 0 ; j <= 20 ; j ++){
                sum += pow_mod(2 , j , MOD) * get(1 , j , 1 , n , l , r); 
            }
            write(sum);
            putchar('\n');
        }
    }

    return 0;
}
