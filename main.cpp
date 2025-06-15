/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace chrono;

// Bubble Sort
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
        }
    }
}

// Merge Sort
void merge(vector<int>& arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; ++i) L[i] = arr[l + i];
    for (int j = 0; j < n2; ++j) R[j] = arr[m + 1 + j];
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(vector<int>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// Quick Sort
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (arr[j] < pivot) {
            ++i;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Generate random array
vector<int> generateArray(int size, string type) {
    vector<int> arr(size);
    srand(time(0));
    for (int i = 0; i < size; ++i)
        arr[i] = rand() % 10000;

    if (type == "sorted") sort(arr.begin(), arr.end());
    else if (type == "reverse") {
        sort(arr.begin(), arr.end(), greater<int>());
    }
    return arr;
}

// Time measurement and execution
void testSort(void (*sortFunc)(vector<int>&), vector<int> arr, const string& name, ofstream& fout, int size) {
    auto start = high_resolution_clock::now();
    sortFunc(arr);
    auto end = high_resolution_clock::now();
    duration<double> duration = end - start;
    fout << name << "," << size << "," << duration.count() << "s\n";
}

void testMergeSort(vector<int> arr, ofstream& fout, int size) {
    auto start = high_resolution_clock::now();
    mergeSort(arr, 0, arr.size() - 1);
    auto end = high_resolution_clock::now();
    duration<double> duration = end - start;
    fout << "MergeSort," << size << "," << duration.count() << "s\n";
}

void testQuickSort(vector<int> arr, ofstream& fout, int size) {
    auto start = high_resolution_clock::now();
    quickSort(arr, 0, arr.size() - 1);
    auto end = high_resolution_clock::now();
    duration<double> duration = end - start;
    fout << "QuickSort," << size << "," << duration.count() << "s\n";
}

int main() {
    ofstream fout("results.csv");
    fout << "Algorithm,InputSize,Time\n";
    vector<int> sizes = {10, 1000, 10000};
    vector<string> types = {"random", "sorted", "reverse"};

    for (int size : sizes) {
        for (string type : types) {
            vector<int> data = generateArray(size, type);
            testSort(bubbleSort, data, "BubbleSort", fout, size);
            data = generateArray(size, type);
            testMergeSort(data, fout, size);
            data = generateArray(size, type);
            testQuickSort(data, fout, size);
        }
    }

    fout.close();
    return 0;
}