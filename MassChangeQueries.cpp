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
const int BLOCK_SIZE = 800;
const int N = 2e5 + 5;
const int LIM = 100;
int n, nblocks;
int a[N];
int lazy[N / BLOCK_SIZE + 1][LIM + 1];
 
void doLazy(int id) { // L R là đầu trái và đầu phải của phần dư bên trái
    int L = id * BLOCK_SIZE;
    int R = min(n - 1, (id + 1) * BLOCK_SIZE - 1);
    for (int i = L; i <= R; i++) {
        a[i] = lazy[id][a[i]]; // thay đổi giá trị các phần tử bằng mảng lazy
    }
    for (int i = 1; i <= 100; i++) {
        lazy[id][i] = i; // đã cập nhật xong, reset lại mảng lazy về ban đầu
    }
}
 
void manualUpdate(int L, int R, int oval, int nval) { // L R là đầu trái và đầu phải của phần dư bên trái
    int id = R / BLOCK_SIZE;
    doLazy(id);
    for (int i = L; i <= R; i++) {
        if (a[i] == oval) {
            a[i] = nval;
        }
    }
}
 
void blockUpdate(int id, int oval, int nval) {
    for (int i = 1; i <= LIM; i++) {
        if (lazy[id][i] == oval) {
            lazy[id][i] = nval;
        }
    }
}
 
void update(int l, int r, int oval, int nval) {
    int blockL = l / BLOCK_SIZE, blockR = r / BLOCK_SIZE;
    if (blockL == blockR) {
        manualUpdate(l, r, oval, nval);
        return;
    }
    for (int i = blockL + 1; i < blockR; ++i) {
        blockUpdate(i, oval, nval);
    }
    manualUpdate(l, (blockL + 1) * BLOCK_SIZE - 1, oval, nval);
    manualUpdate(blockR * BLOCK_SIZE, r, oval, nval);
}
 
void init() {
    nblocks = (n + BLOCK_SIZE - 1) / BLOCK_SIZE;
    for (int i = 0; i < nblocks; i++) {
        for (int j = 1; j <= 100; j++) {
            lazy[i][j] = j;
        }
    }
}
 
signed main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    init();
    int q; cin >> q;
    for (int Q = 0; Q < q; Q++) {
        int l, r, oval, nval;
        cin >> l >> r >> oval >> nval;
        l--; r--;
        update(l, r, oval, nval);
    }
    for (int i = 0; i < nblocks; i++) {
        doLazy(i);
    }
    for (int i = 0; i < n; i++) {
        cout << a[i] << ' ';
    }
    cout << endl;
}