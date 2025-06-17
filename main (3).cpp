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
#include <functional>

using namespace std;
using namespace chrono;

// Sorting Algorithms 

void bubbleSort(vector<int>& arr) {
    int n = arr.size(); 
    for (int i = 0; i < n - 1; ++i)
    for (int j = 0; j < n - i - 1; ++j)
    if (arr[j] > arr[j + 1]) 
    swap(arr[j], arr[j + 1]);
    }
    
void merge(vector<int>& arr, int l, int m, int r) { 
    int n1 = m - l + 1; int n2 = r - m;
    vector<int> L(n1), R(n2); 
    for (int i = 0; i < n1; ++i) L[i] = arr[l + i]; 
    for (int j = 0; j < n2; ++j) R[j] = arr[m + 1 + j]; 
    int i = 0, j = 0, k = l; 
    while (i < n1 && j < n2) arr[k++] = (L[i] <= R[j])? L[i++] : R[j++]; 
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

int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; ++j)
        if (arr[j] < pivot)
            swap(arr[++i], arr[j]);
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

// Data Generation

vector<int> generateArray(int size, const string& type) {
    vector<int> arr(size);
    for (int i = 0; i < size; ++i)
        arr[i] = rand() % 10000;

    if (type == "sorted") sort(arr.begin(), arr.end());
    else if (type == "reverse") sort(arr.begin(), arr.end(), greater<int>());

    return arr;
}

// Testing
void testSortAverage(
    function<void(vector<int>&)> sortFunc,
    const string& name,
    const vector<int>& baseArray,
    const string& type,
    int size,
    int repeats,
    ofstream& fout
) {
    double totalTime = 0.0;

    for (int i = 0; i < repeats; ++i) {
        vector<int> arr = baseArray; // use a fresh copy for each run
        auto start = high_resolution_clock::now();
        sortFunc(arr);
        auto end = high_resolution_clock::now();
        duration<double> dur = end - start;
        totalTime += dur.count();
    }

    double avgTime = totalTime / repeats;
    fout << name << "," << size << "," << type << "," << avgTime << "s\n";
}

// Main 

int main() {
    srand(time(0));

    ofstream fout("results.csv");
    fout << "Algorithm,InputSize,Type,AverageTime\n";

    vector<int> sizes = {10, 1000, 10000};
    vector<string> types = {"random", "sorted", "reverse"};
    int repeats = 3;

    for (int size : sizes) {
        for (const string& type : types) {
            vector<int> baseArray = generateArray(size, type);

            testSortAverage(bubbleSort, "BubbleSort", baseArray, type, size, repeats, fout);
            testSortAverage(
                [](vector<int>& arr) { mergeSort(arr, 0, arr.size() - 1); },
                "MergeSort", baseArray, type, size, repeats, fout
            );
            testSortAverage(
                [](vector<int>& arr) { quickSort(arr, 0, arr.size() - 1); },
                "QuickSort", baseArray, type, size, repeats, fout
            );
        }
    }

    fout.close();
    cout << "Experiment finished! Results saved to results.csv" << endl;
    return 0;
}


// kinda massad
// 202210677