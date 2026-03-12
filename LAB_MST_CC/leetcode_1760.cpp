class Solution {
public:
    int minimumSize(vector<int>& nums, int maxOperations) {
        int n=nums.size();
        int low=1;
        int high=INT_MIN;
        for(int i=0;i<n;i++)high=max(high,nums[i]);

        while(low<high){
            int mid=low+(high-low)/2;
            int ops=0;
            for(int i=0;i<n;i++){
                ops+=(nums[i]-1)/mid;
                if(ops>maxOperations)break;
            }
            if(ops<=maxOperations)high=mid;
            else low=mid+1;
        }
        return high;
    }
};
