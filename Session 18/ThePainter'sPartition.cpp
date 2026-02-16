#include <bits/stdc++.h>
using namespace std;

bool canPaint(vector<int>& arr, int k, long long maxTime) {
    int painters = 1;
    long long total = 0;

    for (int i = 0; i < arr.size(); i++) {
        total += arr[i];

        if (total > maxTime) {
            painters++;
            total = arr[i];
        }

        if (painters > k) return false;
    }
    return true;
}

long long minTime(vector<int>& arr, int k) {
    long long low = *max_element(arr.begin(), arr.end());
    long long high = accumulate(arr.begin(), arr.end(), 0LL);
    long long ans = high;

    while (low <= high) {
        long long mid = (low + high) / 2;

        if (canPaint(arr, k, mid)) {
            ans = mid;
            high = mid - 1;   
        } else {
            low = mid + 1;    
        }
    }
    return ans;
}

int main() {
    vector<int> arr = {5, 10, 30, 20, 15};
    int k = 3;

    cout << minTime(arr, k);
}
