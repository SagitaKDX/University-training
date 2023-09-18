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
const ll INF = 1e20 + 7;
const ll MAXN = 1e5 + 7;
const ll MOD = 1e9 + 7;
int n ;
struct item{
    int num ;
    int l , r;
    int laz;
};
struct query{
    bool type ;
    ll val;
};
query a[MAXN];
item st[MAXN * 4];
int d = 1;
ll b[MAXN] , pos[MAXN] , v[MAXN];
int num[MAXN];
void push_down(int id){
    int t;
    t = st[id].laz;
    st[id << 1].laz += t;
    st[id << 1].l += t;
    st[id << 1].r += t;
    st[id << 1 | 1].laz += t;
    st[id << 1 | 1].l += t;
    st[id << 1 | 1].r += t;
    st[id].laz = 0;
    return;
}
void rebuild(int id , int l , int r){
    st[id].l = 0;
    st[id].r = 0;
    st[id].num = 0;
    st[id].laz = 0;
    if(r == l){
        return;
    }
    int mid = l + r;
    mid >>= 1;
    rebuild(id << 1 , l , mid);
    rebuild(id << 1 | 1 , mid + 1 , r);
}
void update(int id , int l , int r , int u , int v , int type , int val){
    if(l > v || r < u){
        return;
    }
    if(u <= l && r <= v){
        // type 0 new value
        // type 1 resize the tree 
        // type 2 delete value
        if(type == 0){
            st[id].num += 1;
            if(st[id].num == 1){
                st[id].l += 1;
            }
            st[id].r = st[id].l + st[id].num - 1;

        }
        if(type == 2){
            st[id].num -= 1;
            if(st[id].num == 0){
                st[id].l -= 1;
                st[id].r = st[id].l ;
            }else{
                st[id].r -= 1;
            }
            
        }
        if(type == 1){
            st[id].laz += val;
            st[id].l += val;
            st[id].r += val;   
        }
        return;
    }
    push_down(id);
    int mid = l + r;
    mid >>= 1;
    update(id << 1 , l , mid , u , v, type , val);
    update(id << 1 | 1 , mid + 1 , r , u , v , type , val);
    st[id].num = st[id << 1].num + st[id << 1 | 1].num;
    st[id].l = st[id << 1].l;
    st[id].r = st[id << 1 | 1].r;
}
int find(int id ,int l , int r, int pos){
    if(l == r){
        return l;
    }
    push_down(id);
    int mid = l + r;
    mid >>= 1;
    if(st[id << 1].l <= pos && pos <= st[id << 1].r){
        return find(id << 1 , l , mid , pos);
    }
    return find(id << 1 | 1 , mid + 1 , r , pos);
}
int binarysearch(ll val){
    int l = 1 , r = n;
    while(l <= r){
        int mid = l + r;
        mid >>= 1;
        if(b[mid] == val){
            return pos[mid];
        }
        if(b[mid] > val){
            r = mid - 1;
        }else{
            l = mid + 1;
        }
    }
    return 0;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    freopen("new.inp" , "r" , stdin);
    freopen("new.out" , "w" , stdout);
    cin >> n;
    for(int i = 1 ; i <= n ; i ++){
        char x;
        cin >> x;
        a[i].type = (x == 'r')? 0 : 1;
        cin >> a[i].val;
        b[i] = a[i].val;
    }
    d = 1;
    sort(b + 1 , b + n + 1);
    for(int i = 1 ; i <= n ; i ++){
        if( i >= 2 && b[i] != b[i - 1]){
            d++;
        }
        pos[i] = d;
        v[d] = b[i]; 
    }
    int cur = 0;
    for(int i = 1 ; i <= n ; i ++){
        int z = binarysearch(a[i].val);
        
        if(a[i].type == false){
            if(num[z] - 1 < 0 ){
                cout <<"Wrong!" << '\n';
                continue;
            }else{
                cur --;
                num[z] --;
                update(1 , 1 , d , z , z , 2 , -1);
                if(z < d){
                    update(1 , 1 , d , z + 1 , d , 1 , -1);
                }
                if(cur == 0){
                    cout << "Wrong!" << '\n';
                    continue;
                }
                ll val = 0;
                if(cur % 2 == 1){
                    val = v[find(1 , 1 , d ,(int) cur / 2 + 1 )];
                    cout << val << '\n';
                }else{
                    val = v[find(1 , 1 , d , (int) cur / 2 )];
                    val += v[find(1 , 1 , d , (int) cur / 2 + 1)];
                    if(val % 2 == 0){
                         cout << fixed << setprecision(0) << (double) val / 2.0<< '\n';
                    }else{

                        cout << fixed << setprecision(1) << (double) val / 2.0<< '\n';
                    }
                    
                }

            }
        }
        if(a[i].type){
            cur ++;
            num[z] ++;
            update(1 , 1 , d , z , z , 0 , 1);
            if(z < d){
                update(1 , 1 , d , z + 1 , d , 1 , 1);
            }
            ll val = 0;
            if(cur % 2 == 1){
                val = v[find(1 , 1 , d ,(int) cur / 2 + 1 )];
                cout << val << '\n';
                //  cout << v[find(1 , 1 , d , cur / 2 + 1)] << '\n';
            }else{
                val = v[find(1 , 1 , d , (int) cur / 2 )];
                val += v[find(1 , 1 , d , (int) cur / 2 + 1)];
                if(val % 2 == 0){
                     cout << fixed << setprecision(0) << (double) val / 2.0<< '\n';
                }else{
                    cout << fixed << setprecision(1) << val / 2.0<< '\n';
                }
               
            }
        }
    }
    return 0;
}