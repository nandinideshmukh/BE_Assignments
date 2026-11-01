
#include <iostream>
#include <vector>
#include <windows.h>
#include <chrono>
#include <cstdlib>
using namespace std;
using namespace chrono;

void merge(vector<int>& A, int l, int m, int r) {
    vector<int> L(A.begin() + l, A.begin() + m + 1);
    vector<int> R(A.begin() + m + 1, A.begin() + r + 1);

    int i = 0, j = 0, k = l;

    while (i < L.size() && j < R.size()) {
        if (L[i] <= R[j])
            A[k++] = L[i++];
        else
            A[k++] = R[j++];
    }

    while (i < L.size()) A[k++] = L[i++];
    while (j < R.size()) A[k++] = R[j++];
}

void mergeSort(vector<int>& A, int l, int r) {
    if (l >= r) return;

    int m = l + (r - l) / 2;
    mergeSort(A, l, m);
    mergeSort(A, m + 1, r);
    merge(A, l, m, r);
}

void parallelMergeSort(vector<int>& A, int l, int r, int depth);

struct ThreadArgs {
    vector<int>* array;
    int left;
    int right;
    int depth;
};

DWORD WINAPI parallelMergeSortWorker(LPVOID parameter) {
    ThreadArgs* args = static_cast<ThreadArgs*>(parameter);
    parallelMergeSort(*args->array, args->left, args->right, args->depth);
    return 0;
}

void parallelMergeSort(vector<int>& A, int l, int r, int depth) {
    if (l >= r) return;

    if (depth <= 0) {
        mergeSort(A, l, r);
        return;
    }

    int m = l + (r - l) / 2;

    ThreadArgs leftArgs = {&A, l, m, depth - 1};
    ThreadArgs rightArgs = {&A, m + 1, r, depth - 1};

    HANDLE leftThread = CreateThread(
        NULL, 0, parallelMergeSortWorker, &leftArgs, 0, NULL);

    if (leftThread == NULL) {
        cerr << "Could not create a worker thread (error "
             << GetLastError() << "); sorting this section sequentially.\n";
        parallelMergeSort(A, l, m, depth - 1);
        parallelMergeSort(A, m + 1, r, depth - 1);
    } else {
        HANDLE rightThread = CreateThread(
            NULL, 0, parallelMergeSortWorker, &rightArgs, 0, NULL);

        if (rightThread == NULL) {
            cerr << "Could not create a worker thread (error "
                 << GetLastError() << "); sorting this section sequentially.\n";
            WaitForSingleObject(leftThread, INFINITE);
            CloseHandle(leftThread);
            parallelMergeSort(A, m + 1, r, depth - 1);
        } else {
            HANDLE threads[2] = {leftThread, rightThread};
            DWORD waitResult = WaitForMultipleObjects(
                2, threads, TRUE, INFINITE);
            if (waitResult == WAIT_FAILED) {
                cerr << "Could not wait for worker threads (error "
                     << GetLastError() << ").\n";
                WaitForSingleObject(leftThread, INFINITE);
                WaitForSingleObject(rightThread, INFINITE);
            }
            CloseHandle(leftThread);
            CloseHandle(rightThread);
        }
    }

    merge(A, l, m, r);
}

int main() {
    int n;
    cout << "Enter array size: ";
    cin >> n;

    if (n <= 0) {
        cout << "Invalid array size\n";
        return 1;
    }

    vector<int> original(n);

    srand(42);
    for (int i = 0; i < n; i++)
        original[i] = rand();

    // Normal Merge Sort timing
    vector<int> A = original;

    auto start1 = high_resolution_clock::now();
    mergeSort(A, 0, n - 1);
    auto end1 = high_resolution_clock::now();

    double normalTime =
        duration<double, milli>(end1 - start1).count();

    // Parallel Merge Sort timing
    vector<int> B = original;

    int depth = 2; // Limits thread creation

    auto start2 = high_resolution_clock::now();
    parallelMergeSort(B, 0, n - 1, depth);
    auto end2 = high_resolution_clock::now();

    double parallelTime =
        duration<double, milli>(end2 - start2).count();

    cout << "\nNormal Merge Sort time: "
         << normalTime << " ms\n";

    cout << "Parallel Merge Sort time: "
         << parallelTime << " ms\n";

    if (parallelTime > 0)
        cout << "Speedup: "
             << normalTime / parallelTime << "x\n";

    return 0;
}
