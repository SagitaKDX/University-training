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
struct FT {
    int size;
    vector<int>tree;
    FT(int size) : size(size) {
        tree.resize(size + 1);
    }
    int lsb(int n) {
        return n & -n;
    }
    void add(int i, int val) {
        i = max(i + 1, 1);
        while (i <= size) {
            tree[i] += val;
            i += lsb(i);
        }
    }
    int getSum(int i) {
        i = min(i + 1, size);
        int res = 0;
        while (i) {
            res += tree[i];
            i -= lsb(i);
        }
        return res;
    }
};
class Solution {
public:
    long long countQuadruplets(vector<int>& nums) {
        FT left(nums.size() + 1), right(nums.size() + 1);
        long long res = 0;
        for (int i = 0; i < nums.size(); i++) right.add(nums[i], 1);
        for (int k = 0; k < nums.size(); k++) {
            right.add(nums[k], -1);
            for (int j = 0; j < k; j++) {
                left.add(nums[j], 1);
                if (nums[j] < nums[k]) continue;
                res += (long long) (right.getSum(nums.size()) - right.getSum(nums[j])) * left.getSum(nums[k] - 1);
            }
            for (int j = 0; j < k; j++) left.add(nums[j], -1);
        }
        return res;
    }
};
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    freopen("new.inp" , "r" , stdin);
    freopen("new.out" , "w" , stdout);
    vector<int > a;
    int x;
    while(cin >> x){
        a.push_back(x);
    }
    Solution s;
    cout << s.countQuadruplets(a);
    return 0;
}
