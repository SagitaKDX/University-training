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
#define MOD 1000000007
#define s(a) scanf("%d",&a);

vector<int> edges[100009];
long long int visited[100009];
long long int  count1[100009];
long long int B[100009],C[100009],D[100009];

void dfs(int x, int temp)
{
    if(visited[x] == 0)
        visited[x] = temp;
    for(int i = 0 ; i< edges[x].size() ; i++)
    {
        if(visited[edges[x][i]] == 0)
            dfs(edges[x][i],temp);
    }
    return;
}

int main()
{
    int n,i,a,b;
    char c;
    s(n);
    for(i=0 ; i< n -1 ; i++)
    {
        s(a);
        s(b);
        cin>>c;
        if( c != 'r')
        {
            edges[a].push_back(b);
            edges[b].push_back(a);
        }
    }
    int temp = 1;
    for(i=1 ; i<=n ; i++)
    {
        if(visited[i] == 0)
        {
            dfs(i,temp);
            temp++;
        }
    }
    for(i=1 ; i<= n ; i++)
        count1[visited[i]]++;   
    long long int sum = 0;
    B[n-1] = count1[n];
    for(i=n-2;i>=0;i--) B[i] = (B[i+1] + count1[i+1])%MOD;
    for(i=1;i<n-1;i++) C[i] = (count1[i+1]*B[i+1])%MOD;

    D[n-2] = C[n-2];
    for(i=n-3;i>=1;i--) D[i] = (D[i+1] + C[i])%MOD;

    for(i=0;i<n-2;i++) sum = (sum + count1[i+1]*D[i+1])%MOD;
    cout<< ( MOD + sum )%MOD<<endl; 
    return 0;
}