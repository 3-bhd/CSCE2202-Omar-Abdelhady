#include <iostream>
#include <vector>

using namespace std;

pair<int, pair<int, int>> maxCrossingSubArray(vector<int>& nums, int start, int end, int mid) {
    int leftSum = -9999;
    int sum = 0;
    int maxLeft = mid;
    for (int i = mid; i >= start; i--) {
        sum += nums[i];
        if (sum > leftSum) {
            leftSum = sum;
            maxLeft = i;
        }
    }
    int rightSum = -9999;
    sum = 0;
    int maxRight = mid + 1;
    for (int i = mid + 1; i <= end; i++) {
        sum += nums[i];
        if (sum > rightSum) {
            rightSum = sum;
            maxRight = i;
        }
    }
    
    return {leftSum + rightSum, {maxLeft, maxRight}};
}

pair<int, pair<int, int>> maxSubArray(vector<int>& nums, int start, int end) {
    if (start == end) {
        return {nums[start], {start, end}};
    }
    int mid = (start + end) / 2;
    auto left = maxSubArray(nums, start, mid);
    auto right = maxSubArray(nums, mid + 1, end);
    auto cross = maxCrossingSubArray(nums, start, end, mid);

    if (left.first >= right.first && left.first >= cross.first) {
        return left;
    } else if (right.first >= left.first && right.first >= cross.first) {
        return right;
    } else {
        return cross;
    }
}

int main() {
    vector<int> nums = {-3, -2, 5, 4, 3, 0, 1, -5};
    auto result = maxSubArray(nums, 0, nums.size() - 1);
    cout << "Maximum subarray starts at index " << result.first << " and ends at index " << result.second.first << " with sum " << result.second.second << endl;
    for (int i = result.second.first; i <= result.second.second; i++) {
        cout << nums[i] << " ";
    }
    return 0;
}

