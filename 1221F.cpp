// #pragma GCC optimize("Ofast")
// #pragma optimize("unroll-loops")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>

using namespace std;
#define ll long long
#define ld long double

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

const ll MAXN = 1e6 + 7;
const ll MAXQ = 5e5 + 7;
const ll INF = 1e18 + 7;
const ll MAXVAL = 1e18 + 7;

int n;
struct item{
    ll x , y , c;
};

struct seg_tree{
    ll val , laz;
    int pos;
};

ll save[MAXN] , pos[MAXN] , value[MAXN] , d = 0;

bool cmp(item u , item v){
    if(max(u.x , u.y) == max(v.x , v.y)){
        return min(u.x , u.y) < min(v.x , v.y);
    }
    return max(u.x , u.y) < max(v.x , v.y);
}

int binarysearch(ll val){
    int l = 1 , r = 2 * n;
    while(l <= r){
        int mid = l + r;
        mid >>= 1;
        if(save[mid] == val){
            return pos[mid];
        }
        if(save[mid] > val){
            r = mid - 1;
        }else{
            l = mid + 1;
        }
    }
    return -1;
}



seg_tree st[MAXN * 4];
item qu[MAXN];

seg_tree max_val(seg_tree k , seg_tree h){
    if(k.val > h.val){
        return k;
    }else{
        return h;
    }
}

void push_down(int id){
    ll tmp = st[id].laz;
    st[id].laz = 0;
    st[id << 1].val += tmp;
    st[id << 1].laz += tmp;
    st[id << 1 | 1].val += tmp;
    st[id << 1 | 1].laz += tmp;
}

void build(int id , int l , int r){
    st[id].laz = 0;
    if(l == r){
        st[id].pos = l;
        st[id].val = 0;
        return;
    }
    int mid = l + r;
    mid >>= 1;
    build(id << 1 , l , mid);
    build(id << 1 | 1, mid + 1 , r);
    st[id] = max_val(st[id << 1 | 1] , st[id << 1]);
}

void update(int id , int l , int r , int u , int v , ll val){
    if(l > v || r < u ||l > r){
        return;
    }
    if(u <= l && r <= v){
        st[id].val += val;
        st[id].laz += val;
        return;
    }
    int mid = l + r;
    mid >>= 1;
    if(st[id].laz != 0){
        push_down(id);
    }
    update(id << 1 , l , mid , u , v , val);
    update(id << 1 | 1 , mid + 1 , r , u , v , val);
    if(st[id << 1].val < st[id << 1 | 1].val){
        st[id].val = st[id << 1 | 1].val;
        st[id].pos = st[id << 1 | 1].pos;
    }else{
        st[id].val = st[id << 1].val;
        st[id].pos = st[id << 1].pos;
    }
}


seg_tree get_max(int id , int l , int r , int u , int v){
    if(l > v || r < u || l > r){
        seg_tree tmp;
        tmp.laz = 0;
        tmp.val = -INF; 
        tmp.pos = 0;
        return tmp;
    }
    if(u <= l && r <= v){
        return st[id];
    }
    int mid = l + r;
    mid >>= 1;
    if(st[id].laz != 0){
        push_down(id);
    }
    return max_val(get_max(id << 1 , l , mid , u , v) , get_max(id << 1 | 1, mid + 1 , r , u , v));
}

signed main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    // freopen("new.inp" , "r" , stdin);
    // freopen("new.out" , "w" , stdout);
    cin >> n ;
    for(int i = 1 ; i <= n ; i ++){
        cin >> qu[i].x >> qu[i].y >> qu[i].c;
        save[i] = qu[i].x;
        save[n + i] = qu[i].y;
    }

    sort(save + 1 , save + 2 * n + 1);
    pos[1] = 1;
    d = 1;
    bool ok = false;
    value[1] = save[1];
    if(save[1] == 381){
            ok = true;
    }
    for(int i = 2  ; i <= 2 * n ; i ++){
        d += save[i] != save[i - 1];
        pos[i] = d;
        value[d] = save[i];
        if(save[i] == 381){
            ok = true;
        }
    }
    sort(qu + 1 , qu + n + 1 , cmp);
    build(1 , 1 , d);
    ll max_res = 0;
    item top_right;
    top_right.x = save[2 * n] + 1;
    top_right.y = save[2 * n] + 1;
    item down_left;
    down_left.x = save[2 * n] + 1;
    down_left.y = save[2 * n] + 1;
    int pos_max , new_pos;
    int i = 1;

    for( ; i <= n ; i ++){
        pos_max = binarysearch(max(qu[i].x , qu[i].y));
        if(i == 1){
            for(int j = 1 ; j < pos_max ; j ++){
                update(1 , 1 , d , j , j ,- (value[pos_max] - value[j]));
            }
        }
        if(i > 1 ){
            int pos_max2 = binarysearch(max(qu[i - 1].x , qu[i - 1].y));
            update(1 , 1 , d , 1 , pos_max2 , -(value[pos_max] - value[pos_max2]));
            for(int j = pos_max2 + 1 ; j < pos_max ; j ++){
                update(1 , 1 , d , j , j ,- (value[pos_max] - value[j]));
            }
        }
        new_pos = binarysearch(min(qu[i].x , qu[i].y));
        update(1 , 1 , d , 1 , new_pos , qu[i].c);
        while(i + 1 <= n && max(qu[i].x, qu[i].y) == max(qu[i + 1].x , qu[i + 1].y) ){
            i += 1;
            new_pos = binarysearch(min(qu[i].x , qu[i].y));
            update(1 , 1 , d ,1 , new_pos , qu[i].c);
        }

        seg_tree tmp = get_max(1 , 1 , d , 1 , pos_max);
        if(tmp.val > max_res){
            max_res = tmp.val;
            top_right.x = max(qu[i].x , qu[i].y);
            top_right.y = max(qu[i].x , qu[i].y);
            down_left.x = value[tmp.pos];
            down_left.y = value[tmp.pos];
        }
    }
    cout << max_res << '\n';
    cout << down_left.x << " " << down_left.y << ' ';
    cout << top_right.x << " " << top_right.y << '\n';
    return 0;    
}
