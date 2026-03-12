class Solution {
public:
    int maxSum(vector<int>& nums, int k) {
        vector<int> count(32);
        int mod = 1e9 + 7;
        for (int x : nums){
            for (int b = 0; b < 32; b++){
                if (x & (1 << b))
                    count[b]++;
            }
        }
        long long ans=0;
        for (int j = 0; j < k; j++) {
            long long res = 0;
            for (int i = 0; i < 32; i++) {
                if (count[i] > 0) {
                    count[i]--;
                    res += 1 << i;
                }
            }
            ans = (ans + (res * res) % mod) % mod;
        }
        return ans;
    }
};
