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
int n;
string st;
int bit[MAXN][26];
char a[MAXN];
void update(int idx ,int type , int val){
    for( ; idx <= n ; idx += idx &(-idx)){
        bit[idx][type] += val;
    }
}
int get(int idx , int type){
    int sum = 0;
    for(; idx > 0 ; idx -= idx &(-idx)){
        sum += bit[idx][type];
    }
    return sum;
}

int get_range(int l , int r , int type){
    return get(r , type) - get(l - 1 , type);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    freopen("new.inp" , "r" , stdin);
    freopen("new.out" , "w" , stdout);
    cin >> st;
    n = st.size();
    for(int i = 1 ; i <= n ; i ++){
        a[i] = st[i - 1];
        update(i , a[i] - 'a' , 1);
    }
    int q;
    cin >> q;
    char c;
    int pos , l , r , type;
    int num = 0;
    for(int i = 1 ; i <= q ; i ++){
        cin >> type;
        if(type == 1){
            cin >> pos >> c;
            update(pos , a[pos] - 'a' , -1);
            update(pos , c - 'a' , 1);
            a[pos] = c;
        }        
        if(type == 2){
            cin >> l >> r;
            num = 0;
            for(int j = 0 ; j < 26 ; j ++){
                num += get_range(l , r , j) > 0;
            }
            cout << num << '\n';
        }
    }
    return 0;
}
