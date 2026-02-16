#include <bits/stdc++.h>
using namespace std;

bool canEat(vector<int>& piles, int h, int speed) {
    long long hours = 0;

    for (int i = 0; i < piles.size(); i++) {
        hours += (piles[i] + speed - 1) / speed;   
        if (hours > h) return false;
    }

    return true;
}

int minEatingSpeed(vector<int>& piles, int h) {
    int left = 1;
    int right = *max_element(piles.begin(), piles.end());
    int ans = right;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (canEat(piles, h, mid)) {
            ans = mid;
            right = mid - 1;   
        } else {
            left = mid + 1;    
        }
    }

    return ans;
}

int main() {
    vector<int> piles = {3, 6, 7, 11};
    int h = 8;

    cout << minEatingSpeed(piles, h);
}
