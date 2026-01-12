#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;


void complexRec(int n) {


   if (n <= 2) {
       return;
   }


   int p = n;
   while (p > 0) {
       vector<int> temp(n);
       for (int i = 0; i < n; i++) {
           temp[i] = i ^ p;
       }
       p >>= 1;
   }


   vector<int> small(n);
   for (int i = 0; i < n; i++) {
       small[i] = i * i;
   }


   if (n % 3 == 0) {
       reverse(small.begin(), small.end());
   } else {
       reverse(small.begin(), small.end());
   }
   
   // Recurrence Relation : T(n)=2 + n+ nlogn+ 3T(n/2)
   
   // Time complexity : O((n^log(3) base 2))
   auto start = high_resolution_clock::now();

   complexRec(n / 2);
   complexRec(n / 2);
   complexRec(n / 2);

   auto end = high_resolution_clock::now();
   auto duration = duration_cast<milliseconds>(end - start);
   cout << duration.count() << endl;
}
int main()
{
    complexRec(20);
    return 0;
}



