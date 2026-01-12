#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

long long operations = 0;
int maxDepth = 0;


void complexRec(int n, int depth) {

    operations++; // function call
    maxDepth = max(maxDepth, depth);

    if (n <= 2) {
        return;
    }

    int p = n;
    while (p > 0) {
        operations++;
        vector<int> temp(n);
        for (int i = 0; i < n; i++) {
            operations++;
            temp[i] = i ^ p;
        }
        p >>= 1;
    }

    vector<int> small(n);
    for (int i = 0; i < n; i++) {
        operations++;
        small[i] = i * i;
    }

    operations++;
    reverse(small.begin(), small.end());

    // Recursive calls
    complexRec(n / 2, depth + 1);
    complexRec(n / 3, depth + 1);

    //recurrence relation = 2+n+nlogn+2T(n/2)
    //time complexity = O(n^log(3) base 2)
}

int main() {

    vector<int> testSizes = {10, 20, 40, 80};

    cout << "n\tOperations\tMax Depth\tTime (ms)\n";
    cout << "---------------------------------------------\n";

    for (int n : testSizes) {

        operations = 0;
        maxDepth = 0;

        auto start = high_resolution_clock::now();
        complexRec(n, 1);
        auto end = high_resolution_clock::now();

        auto duration = duration_cast<milliseconds>(end - start);

        cout << n << "\t"
             << operations << "\t\t"
             << maxDepth << "\t\t"
             << duration.count() << endl;
    }

    return 0;
}
