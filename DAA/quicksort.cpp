// Analyze Quick Sort using deterministic and randomized variants.

#include <bits/stdc++.h>
using namespace std;

int find_pivot(int l, int r, vector<int> &arr)
{
    int i = l;
    int j = r;
    int p = l;
    while (i <= j && j < arr.size())
    {
        while (i <= j && arr[i] <= arr[p])
            i++;
        while (i <= j && arr[j] > arr[p])
            j--;
        if (i < j)
            swap(arr[i], arr[j]);
    }
    swap(arr[p], arr[j]);
    return j;
}

void quick_merge(vector<int> &arr, int l, int r)
{
    if (l < r)
    {
        int p = find_pivot(l, r, arr);
        quick_merge(arr, l, p - 1);
        quick_merge(arr, p + 1, r);
    }
}

int main()
{
    vector<int> arr(1e5);
    vector<int> sorted_arr (1e5);
    for(int i=0;i<1e5;i++){
        arr[i] = rand() % 1000000;
        sorted_arr[i] = i;
    }
    cout << "Hi\n";
    // check time
    auto start = chrono::high_resolution_clock::now();
    quick_merge(arr, 0, arr.size() - 1);
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << "Time taken by Quick Sort: " << duration.count() << " microseconds" << endl;

    start = chrono::high_resolution_clock::now();
    quick_merge(sorted_arr, 0, sorted_arr.size() - 1);
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << "Time taken by Quick Sort (sorted array): " << duration.count() << " microseconds" << endl;
    cout << endl;
    return 0;
}