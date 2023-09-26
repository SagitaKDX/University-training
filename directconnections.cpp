#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;

typedef pair<int, int> pi;
typedef pair<ll, int> pli;
typedef pair<int, ll> pil;
typedef pair<ll, ll> pl;
typedef pair<ld, ld> pd;

typedef vector<int> vi;
typedef vector<bool> vb;
typedef vector<ld> vd;
typedef vector<ll> vl;
typedef vector<pi> vpi;
typedef vector<pl> vpl;
typedef vector<pli> vli;
typedef vector<pil> vil;

#define FORE(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); i++)
#define bit(x, i) (((x) >> (i)) & 1)
#define MASK(i) (1LL << (i))
#define mp make_pair
#define pb push_back
#define f first

// #define s second
#define lb lower_bound
#define ub upper_bound
#define sz(x) (int)x.size()
#define ALL(x) begin(x), end(x)

void minimize(long long &x, long long y)
{
    if (x > y)
    {
        x = y;
    }
}

void maximize(long long &x, long long y)
{
    if (x < y)
    {
        x = y;
    }
}

template <typename T>
inline void read(T &x)
{
    char c;
    bool nega = 0;
    while ((!isdigit(c = getchar())) && c != '-')
        ;
    if (c == '-')
    {
        c = getchar();
        nega = 1;
    }
    x = c - 48;
    while (isdigit(c = getchar()))
    {
        x = x * 10 + c - 48;
    }
    if (nega)
        x = -x;
}
template <typename T>
void Write(T x)
{
    if (x > 9)
        Write(x / 10);
    putchar(x % 10 + 48);
}
template <typename T>
void write(T x)
{
    if (x < 0)
    {
        putchar('-');
        x = -x;
    }
    Write(x);
}

long long pow_mod(long long a, long long b, long long m)
{
    long long res = 1;
    while (b)
    {
        res = res * (b & 1 ? a : 1) % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}

long long GCD(long long a, long long b)
{
    while (b != 0)
    {
        a = a % b;
        long long tmp = a;
        a = b;
        b = tmp;
    }
    return a;
}

long long minn(long long a, long long b, long long c, long long d)
{
    long long res = a;
    if (res > d)
        res = d;
    if (res > b)
        res = b;
    if (res > c)
        res = c;
    return res;
}
const ll INF = 1e18 + 7;
const ll MAXN = 1e5 + 7;
const ll MOD = 1e9 + 7;
int n;
struct item
{
    ll x;
    int p;
};
bool cmp(item u, item v)
{
    return u.x < v.x;
}
bool reverse_cmp(item u, item v)
{
    return u.x > v.x;
}
struct segmentree
{
    ll val;
    ll sum;
    ll laz;

} st[MAXN * 4];
item a[MAXN];
ll b[MAXN], d, pos[MAXN];
int binarysearch(int val)
{
    int l = 1, r = n;
    while (l <= r)
    {
        int mid = l + r;
        mid >>= 1;
        if (b[mid] == val)
            return mid;
        if (b[mid] > val)
        {
            r = mid - 1;
        }
        else
        {
            l = mid + 1;
        }
    }
    return -1;
}
void push_down(int id)
{
    ll t = st[id].laz;
    st[id << 1].laz += t;
    st[id << 1].laz %= MOD;
    st[id << 1].val += st[id << 1].sum * t;
    st[id << 1].val %= MOD;
    st[id << 1 | 1].laz += t;
    st[id << 1 | 1].laz %= MOD;
    st[id << 1 | 1].val += st[id << 1 | 1].sum * t;
    st[id << 1 | 1].val %= MOD;
    st[id].laz = 0;
}
void rebuild(int id, int l, int r)
{
    st[id].val = 0;
    st[id].laz = 0;
    st[id].sum = 0;
    if (l == r)
        return;
    int mid = l + r;
    mid >>= 1;
    rebuild(id << 1, l, mid);
    rebuild(id << 1 | 1, mid + 1, r);
}
void update(int id, int l, int r, int pos, ll val)
{
    if (l == r)
    {
        st[id].sum += val;
        st[id].sum %= MOD;
        return;
    }
    int mid = l + r;
    mid >>= 1;
    if (st[id].laz != 0)
    {
        push_down(id);
    }
    if (pos <= mid)
    {
        update(id << 1, l, mid, pos, val);
    }
    else
    {
        update(id << 1 | 1, mid + 1, r, pos, val);
    }
    st[id].sum = (st[id << 1].sum + st[id << 1 | 1].sum) % MOD;
    st[id].sum %= MOD;
    st[id].val = (st[id << 1].val + st[id << 1 | 1].val) % MOD;
    st[id].val %= MOD;
}
ll get(int id, int l, int r, int u, int v)
{
    if (l > v || r < u)
    {
        return 0;
    }
    if (u <= l && r <= v)
    {
        return st[id].val % MOD;
    }
    int mid = l + r;
    mid >>= 1;
    if (st[id].laz != 0)
    {
        push_down(id);
    }
    return (get(id << 1, l, mid, u, v) % MOD + get(id << 1 | 1, mid + 1, r, u, v) % MOD) % MOD;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    freopen("new.inp", "r", stdin);
    freopen("new.out", "w", stdout);
    int t;
    int z;
    cin >> t;
    ll tmp = 0;
    ll res = 0;
    while (t--)
    {
        cin >> n;
        for (int i = 1; i <= n; i++)
        {
            cin >> a[i].x;
        }
        for (int i = 1; i <= n; i++)
        {
            cin >> a[i].p;
            b[i] = a[i].p;
        }
        sort(b + 1, b + n + 1);
        sort(a + 1, a + n + 1, cmp);
        d = 1;
        for (int i = 1; i <= n; i++)
        {
            if (i >= 2 && b[i] != b[i - 1])
            {
                d++;
            }
            pos[i] = d;
        }
        rebuild(1, 1, d);
        res = 0;
        for (int i = 1; i <= n; i++)
        {   
            cout << a[i].x << " " << a[i].p << '\n';
            if (i > 1)
            {
                st[1].laz += (a[i].x - a[i - 1].x) % MOD;
                st[1].val += (st[1].sum * (a[i].x - a[i - 1].x)) % MOD;
                st[1].val %= MOD;
            }
            z = binarysearch(a[i].p);
            tmp = get(1, 1, d, z, d);
            cout << tmp << '\n';
            res += tmp % MOD;
            res %= MOD;
            update(1, 1, d, z, a[i].p);
        }
        cout << res << '\n';
        rebuild(1, 1, d);
        sort(a + 1, a + n + 1, reverse_cmp);
        for (int i = 1; i <= n; i++)
        {

            z = binarysearch(a[i].p);
            if (i > 1)
            {
                st[1].laz += (a[i - 1].x - a[i].x) % MOD;
                st[1].val += (st[1].sum * (a[i - 1].x - a[i].x)) % MOD;
                st[1].val %= MOD;
            }
            if (z < d)
            {
                tmp = get(1, 1, d, z + 1, d);
            }
            // cout << tmp << '\n';
            res += tmp % MOD;
            res %= MOD;
            update(1, 1, d, z, a[i].p);
        }
        cout << res << '\n';
    }
    return 0;
}