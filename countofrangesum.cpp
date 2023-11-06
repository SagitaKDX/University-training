#include<bits/stdc++.h>
using namespace std;
#define ll long long
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
const ll INF = 1e18 + 7;
int n  = 0 , d =0;
ll prefix[MAXN] , b[MAXN];
int pos[MAXN];
int bit[MAXN];
int binarysearch(ll val){
    int l = 1 , r = n + 1;
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

int lowerbound(ll val){
    int l = 1 , r = n + 1;
    int pos = -1;
    while(l <= r){
        int mid = l + r;
        mid >>= 1;
        if(b[mid] <= val){
            pos = mid;
            l = mid + 1;
        }else{
            r = mid - 1;
        }
    }
    return pos;
}

int upperbound(ll val){
    int l = 1 , r = n + 1;
    int pos = -1;
    while(l <= r){
        int mid = l + r;
        mid >>= 1;
        if(b[mid] >= val){
            pos = mid;
            r = mid - 1;
        }else{
            l = mid + 1;
        }
    }
    return pos;
}

void update(int idx , int val){
    for(; idx <= d ; idx += idx & (-idx)){
        bit[idx] += val;
    }
}

int get(int idx){
    int sum = 0;
    for( ; idx > 0 ; idx -= idx & (-idx)){
        sum += bit[idx];
    }
    return sum;
}

int get_range(int l , int r){
    return get(r) - get(l - 1);
}
int z;
int lowe;
int upp;
int res;
class Solution {
public:
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        n = nums.size();
        prefix[0] = 0;
        for(int i = 1 ;i <= n ; i ++){
            prefix[i] = prefix[i - 1] + nums[i - 1];
            b[i] = prefix[i];
        }
        b[n + 1] = 0;
        sort(b + 1, b + n + 2);
        d = 1;
        pos[1] = 1;;
        for(int i = 2 ; i <= n + 1 ; i ++){
            if(b[i] != b[i - 1]){
                d ++;
            }
            pos[i] = d;
        }
        for(int idx = 1 ; idx <= d ; idx ++){
            bit[idx] = 0;
        }
        update(binarysearch(0) , 1);
        z = 0;
        upp = 0;
        lowe = 0;
        res = 0;

        for(int i = 1 ; i <= n ; i ++){
            z = binarysearch(prefix[i]);
            upp = upperbound(prefix[i] - upper);
            lowe = lowerbound(prefix[i] - lower);
            if(upp == -1 || lowe == -1){
                update(z , 1);
                continue;
            }
            res += get_range(pos[upp] , pos[lowe]);
            update(z , 1);
        }
        return res;
    }
};
/*
#define BIT(x, i) (((x) >> (i)) & 1)
#define MASK(i) (1LL << (i))
#define ONBIT(x, i) ((x) | MASK(i))
#define ll long long
const ll MAXN = 1e5 + 7;
const ll MOD = 1e9 + 7;
const ll INF = 1e18 + 7;
int n  = 0 , d =0;
ll prefix[MAXN] , b[MAXN];
int pos[MAXN];
int st[MAXN * 4];
int binarysearch(ll val){
    int l = 1 , r = n + 1;
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

int lowerbound(ll val){
    int l = 1 , r = n + 1;
    int pos = -1;
    while(l <= r){
        int mid = l + r;
        mid >>= 1;
        if(b[mid] <= val){
            pos = mid;
            l = mid + 1;
        }else{
            r = mid - 1;
        }
    }
    return pos;
}

int upperbound(ll val){
    int l = 1 , r = n + 1;
    int pos = -1;
    while(l <= r){
        int mid = l + r;
        mid >>= 1;
        if(b[mid] >= val){
            pos = mid;
            r = mid - 1;
        }else{
            l = mid + 1;
        }
    }
    return pos;
}

void rebuild(int id , int l , int r){
    st[id] = 0;
    if(l == r){
        return;
    }
    int mid = l + r;
    mid >>= 1;
    rebuild(id << 1 , l , mid);
    rebuild(id << 1 | 1 , mid + 1 , r);
}

void update(int id , int l , int r , int pos , int val){
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

int get(int id , int l , int r , int u , int v){
    if(l > v || u > r){
        return 0;
    }
    if(u <= l && r <= v){
        return st[id];
    }
    int mid = l + r;
    mid >>= 1;
    return get(id << 1 , l , mid , u , v) + get(id << 1 | 1 , mid + 1 , r , u , v);
}
int z;
int lowe;
int upp;
int res;
class Solution {
public:
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        n = nums.size();
        prefix[0] = 0;
        for(int i = 1 ;i <= n ; i ++){
            prefix[i] = prefix[i - 1] + nums[i - 1];
            b[i] = prefix[i];
        }
        b[n + 1] = 0;
        sort(b + 1, b + n + 2);
        d = 1;
        pos[1] = 1;;
        for(int i = 2 ; i <= n + 1 ; i ++){
            if(b[i] != b[i - 1]){
                d ++;
            }
            pos[i] = d;
        }
        rebuild(1 , 1 , d);
        update(1 , 1 , d , binarysearch(0) , 1);
        z = 0;
        upp = 0;
        lowe = 0;
        res = 0;

        for(int i = 1 ; i <= n ; i ++){
            z = binarysearch(prefix[i]);
            upp = upperbound(prefix[i] - upper);
            lowe = lowerbound(prefix[i] - lower);
            if(upp == -1 || lowe == -1){
                update(1 , 1 , d , z , 1);
                continue;
            }
            res += get(1 , 1, d , pos[upp] , pos[lowe]);
            update(1 , 1 , d , z , 1);
        }
        return res;
    }
};
*/
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    freopen("new.inp" , "r" , stdin);
    freopen("new.out" , "w" , stdout);
    vector<int > a;
    for(int i = 0 ; i < 4 ; i ++){
        int x;
        cin >> x;
        a.push_back(x);
    }
    int upper , low;
    cin >> low >> upper;
    Solution s;
    cout << s.countRangeSum(a , low , upper);
    return 0;
}