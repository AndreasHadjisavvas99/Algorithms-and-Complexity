#include <iostream>
using namespace std;
#include <bits/stdc++.h>
bool isOk(int arr[],int& N,int& K,int& median)
{
    int pre[N];
    
    for (int i = 0; i < N; i++) {
        if (arr[i] >= median)
            pre[i] = 1;
        else
            pre[i] = -1;
 
        if (i > 0)
            pre[i] += pre[i - 1];
    }
    // mx denotes the maximum
    // sum of a sub array having
    // length at least k.
    int mx_median = pre[K - 1];
 
    // mn denotes the minimum
    // prefix sum seen so far.
    int mn_median = 0;
 
    for (int i = K; i < N; i++) {
        mn_median = min(mn_median, pre[i - K]);
        mx_median = max(mx_median, pre[i] - mn_median);
    }
    if (mx_median > 0)
        return true;
    return false;
}
int findMaxMedian(int arr[], int N, int K)
{
    //l and r meaning left and right boundary of binary search
    int l = 1, r = N + 1;
    
    //curent max median
    int mx_median = -1;
    
    while (l <= r){
        int mid = (l + r) / 2;
        if (isOk(arr,N,K , mid)) {
            mx_median = mid;
            l = mid + 1;
        }
        else
            r = mid - 1;
    }
    return mx_median;
}
int main()
{
    int n,k;
    //cout << "Give Number of Markets N and minimum number of consecutive markets K\n";
    cin >> n ;
    cin >> k ;
    //cout << "Insert available products per market i\n";
    
    int c[n]; //cerials per market
    
    //data insertion
    for (int i = 0; i < n; i++) {
        cin >> c[i];
    }
    //cout << "Maximum median: ";
    cout << findMaxMedian(c,n,k) << endl;
    
    return 0;
}
