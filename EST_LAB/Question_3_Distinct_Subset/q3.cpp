
class Solution {
  public:
    vector<vector<int>> findSubsets(vector<int>& arr) {
        int n = arr.size();
        sort(arr.begin(), arr.end());

        set<vector<int>> uniqueSubsets;

        int total = 1 << n;  

        for(int mask = 0; mask < total; mask++) {
            vector<int> subset;

            for(int i = 0; i < n; i++) {
                if(mask & (1 << i)) {
                    subset.push_back(arr[i]);
                }
            }

            uniqueSubsets.insert(subset);
        }

        vector<vector<int>> result(uniqueSubsets.begin(), uniqueSubsets.end());
        return result;
    }
};