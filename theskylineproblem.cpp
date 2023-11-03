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
const ll MAXN = 1e4 + 7;
const ll MOD = 1e9 + 7;
const ll INF = 1e18 + 7;
struct item{
    ll le , ri ,he;
};

struct sweepline{
    ll h , point;
    int type;
};

struct segment_tree{
    int cnt;
    ll val;
};

bool cmp(sweepline u , sweepline v){
    if(u.point == v.point){
        return u.type < v.type;
    }else{
        return u.point < v.point;
    }
}

segment_tree st[MAXN * 4];
sweepline q[2 * MAXN];
ll b[MAXN];
int n , d;
int posi[MAXN];
item bd[MAXN];

int binarysearch(ll val){
    int l = 1 , r = n;
    while(l <= r){
        int mid = l + r;
        mid >>= 1;
        if(b[mid] == val){
            // cout << posi[mid] << '\n';
            return posi[mid];
        }
        if(b[mid] < val){
            l = mid + 1;
        }else{
            r = mid - 1;
        }
    }
    return 0;
}


void rebuild(int id , int l , int r){
    st[id].val = 0;
    st[id].cnt = 0;
    if(l == r){
        return;
    }
    int mid = l + r;
    mid >>= 1;
    rebuild(id << 1 , l , mid);
    rebuild(id << 1 | 1 , mid + 1 , r);
}


void update(int id , int l , int r , int pos , ll val , int upd){
    if(l == r){
        st[id].cnt += upd;
        if(st[id].cnt == 0){
            st[id].val = 0;
        }else{
            st[id].val = val;
        }
        return;
    }
    int mid = l + r;
    mid >>= 1;
    if(pos <= mid){
        update(id << 1 , l , mid , pos , val , upd);
    }else{
        update(id << 1 | 1 , mid + 1 , r , pos , val , upd);
    }
    st[id].val = max(st[id << 1].val , st[id << 1 | 1].val);
}


class Solution {
public:
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        n = buildings.size() ;
        for(int i = 0 ; i < n ; i ++){
            bd[i + 1].le = buildings[i][0];
            bd[i + 1].ri = buildings[i][1];
            bd[i + 1].he = buildings[i][2];
            b[i + 1] = buildings[i][2];
            q[i + 1].h = bd[i + 1].he;
            q[i + 1].point = bd[i + 1].le;
            q[i + 1].type = 0;
            q[i + 1 + n].h = bd[i + 1].he;
            q[i + 1 + n].point = bd[i + 1].ri;
            q[i + 1 + n].type = 1;

        }
        sort(b + 1 , b + n + 1);
        d = 1;
        posi[1] = 1;
        for(int i =  2 ; i <= n ; i ++){
            if(b[i] != b[i - 1]){
                d ++;
            }
            posi[i] = d;
        }
        rebuild(1  , 1 , d);
        sort(q + 1 , q + 2 * n + 1 , cmp);
        vector<vector<int>> ans;
        for(int i = 1 ; i <=2 * n ; i ++){
            // cout << q[i].point << " " << q[i].h << " " << q[i].type << '\n';
            if(q[i].type == 0){
                int idx = i;
                update(1 , 1 , d , binarysearch(q[i].h) , q[i].h , 1);
                while(idx + 1 <=2 * n && q[idx + 1].point == q[i].point && q[idx + 1].type == 0){
                    idx ++;
                    update(1 , 1 , d , binarysearch(q[idx].h) , q[idx].h , 1);
                }
                i = idx;
            }else{
                int idx = i;
                update(1 , 1 , d , binarysearch(q[i].h) , q[i].h , -1);
                while(idx + 1 <=  2 * n && q[idx + 1].point == q[i].point && q[idx + 1].type == 1){
                    idx ++;
                    update(1 , 1 , d , binarysearch(q[idx].h) , q[idx].h , -1);
                }
                i = idx;
            }
            if(ans.size()){
                if(ans[ans.size() - 1][1] != st[1].val){
                    vector<int> cur;
                    cur.push_back(q[i].point);
                    cur.push_back(st[1].val);
                    ans.push_back(cur);
                }
            }else{
                vector<int> cur;
                cur.push_back(q[i].point);
                cur.push_back(st[1].val);
                ans.push_back(cur);
            }
        }
        return ans;
    }
};
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    freopen("new.inp" , "r" , stdin);
    freopen("new.out" , "w" , stdout);
    vector<vector<int>>v;
    for(int i = 0 ; i <= 2; i ++){
        vector<int> cur;
        for(int j = 0 ; j <= 2 ; j ++){
            int x;
            cin >> x;
            cur.push_back(x);           
        }
        v.push_back(cur);
    }
    Solution S;
    S.getSkyline(v);   
    return 0;
}