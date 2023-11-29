#include <bits/stdc++.h>
 
using namespace std;
typedef long long ll;
 
const ll INF = 1e18;
const ll MAXN =2e5 + 7;
ll a[MAXN] , n , q;
struct item{
    ll val ,lazy , setup;
};
item st[MAXN * 4];
void push_down(int id , int l , int r , int mid ){
        if(st[id].setup != 0 ){
           st[id << 1].setup  = st[id << 1 | 1].setup = st[id].setup ;
           st[id << 1].val = st[id].setup * (mid - l + 1);
           st[id << 1 | 1].val = st[id].setup * (r - mid);
           st[id << 1].lazy = 0;
           st[id << 1 | 1].lazy = 0;
           st[id].setup = 0;
        }else{
           if(st[id].lazy != 0){
                if(st[id << 1].setup == 0){
                    st[id << 1].lazy += st[id].lazy;
                }else{
                    st[id << 1].setup += st[id].lazy;
                    st[id << 1].lazy = 0;
                }
                if(st[id << 1 | 1 ].setup == 0){
                    st[id << 1 | 1].lazy += st[id].lazy;
                }else{
                    st[id << 1 | 1].setup += st[id].lazy;
                    st[id << 1 | 1].lazy = 0;
                }
                st[id << 1].val += st[id].lazy * (mid - l + 1);
                st[id << 1 | 1].val += st[id].lazy * (r - mid);
                st[id].lazy = 0;
           }
        }
}
void build(int id , int l , int r){
    st[id].setup = 0;
    st[id].lazy = 0 ;
    if(l == r){
        st[id].val = a[l];
        return ;
    }
    int mid = l + r;
    mid >>= 1 ;
    build(id << 1 , l , mid );
    build(id << 1 | 1 , mid + 1 , r);
    st[id].val = st[id << 1].val + st[id << 1 | 1].val;
 
}
void update(int id , int l , int r , int u , int v , ll val){
    if(l > v || r < u){
     return ;
    }
    if(u <= l && r <= v){
        st[id].val += val * ( r - l + 1 );
        if(st[id].setup == 0 ){
               st[id].lazy += val;
        }else{
            st[id].setup += val;
        }
        return ;
    }
    int mid = l + r ;
    mid >>= 1;
    push_down(id , l , r , mid);
    update(id << 1 ,l , mid , u , v , val);
    update(id << 1 | 1 , mid + 1 ,r , u , v , val);
    st[id].val = st[id << 1].val + st[id << 1 | 1].val;
}
void reset(int id , int l , int r , int u , int v , ll val){
    if(l > v || r < u ){
        return ;
    }
    if(u <= l && r <= v){
        st[id].val = val *(r - l + 1);
        st[id].lazy = 0 ;
        st[id].setup = val;
        return ;
    }
    int mid = l + r ;
    mid >>= 1;
    push_down(id , l , r , mid);
    reset(id << 1 ,l , mid , u , v , val);
    reset(id << 1 | 1 , mid + 1 ,r , u , v , val);
    st[id].val = st[id << 1].val + st[id << 1 | 1].val;
}
ll getsum(int id , int l ,int r , int u , int v){
    if(l > v || r < u ){
        return 0;
    }
    if(u <= l && r <= v){
        return st[id].val;
    }
    int mid = ( l + r) >> 1;
    push_down(id , l , r ,mid);
    return getsum(id << 1 , l , mid  , u , v) + getsum(id << 1 | 1 , mid + 1 , r , u , v);
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
//    freopen("new.inp" , "r" , stdin);
//    freopen("new.out" , "w" , stdout);
    cin >> n >> q ;
    for(int i = 1 ; i <= n ; i ++){
        cin >> a[i];
    }
    build(1 , 1 , n);
    for(int i = 1 ; i <= q ; i ++){
        int type ;
        cin >> type ;
        int a1 , b , x;
        if(type == 1){
            cin >> a1 >> b >> x;
            update(1 , 1 , n , a1 , b , x);
        }
        if(type == 2){
            cin >> a1 >> b >> x;
            reset(1 ,1 ,n , a1 , b , x);
        }
        if(type == 3){
             cin >> a1 >> b;
             cout << getsum(1 , 1 , n , a1 , b) << '\n';
        }
 
    }
    return 0;
}