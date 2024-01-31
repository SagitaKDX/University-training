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
    const ll INF = 1e18 + 7;
    const ll MAXN= 1e6 + 7;
    int n;
    int a[MAXN];
    struct item{
        int type ;
        ll val;
        int pos ;
        int l ;
    };

    vector<item > query;
    bool cmp(item u , item v){
        if(u.pos == v.pos){
            return u.type < v.type;
        }
        return u.pos  < v.pos;
    }
    int last[MAXN]; 
    int st[MAXN];
    void update(int id , int l , int r , int pos , ll val){
        if(l == r){
            st[id] += val;
            return ;
        }
        int mid = l + r;
        mid >>= 1; 
        if(pos <= mid){
            update(id << 1 , l , mid , pos , val);
        }else{
            update(id << 1 | 1 , mid + 1 , r , pos , val);
        }
        st[id] = st[id << 1] + st[id << 1 | 1];
    }
    ll get(int id , int l , int r , int u , int v ){
        if(u > r || l > v){
            return 0;
        }
        if(u <= l && r <= v){
            return st[id];
        }
        int mid =l + r;
        mid >>= 1;
        return get(id << 1 , l , mid , u , v) + get(id << 1 | 1 , mid + 1 , r , u , v);
    }
    ll ans[MAXN];
    int main(){
        // ios_base::sync_with_stdio(false);
        // cin.tie(0);
        freopen("new.inp" , "r" , stdin);
        freopen("new.out" , "w" , stdout);
        read(n);
        int q;
        read(q);
        for(int i = 1 ; i <= n ; i ++){
            read(a[i]);
            query.push_back({1 , a[i] , i , 0});
        }
        int u , v;
        for(int i = 1 ; i <= q ; i ++){
            read(u); read(v);
            query.push_back({3 , i , v , u});
        }
        sort(ALL(query) , cmp);
        for(item k : query){
            if(k.type == 1){
                if(last[k.val] == 0){
                    update(1 , 1 , n , k.pos , 1);
                    last[k.val] = k.pos;
                }else{
                    update(1 , 1 , n , last[k.val] , -1);
                    last[k.val] = k.pos;
                    update(1 , 1 , n , k.pos , 1);
                }
            }
            if(k.type  == 3){
                ans[k.val] = get(1 , 1 , n , k.l , k.pos);
            }
        }
        for(int i = 1 ; i <= q ; i ++){
            write(ans[i]);
            putchar('\n');
        }
        return 0;
    }