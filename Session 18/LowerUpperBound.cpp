#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> arr = {1, 2, 4, 4, 4, 6, 8};
    int x = 4;
    int n = arr.size();

    int low = 0, high = n - 1;
    int lower = n;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] >= x) {
            lower = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    low = 0;
    high = n - 1;
    int upper = n;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] > x) {
            upper = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    cout << "Lower Bound Index: " << lower << endl;
    cout << "Upper Bound Index: " << upper << endl;

    return 0;
}
