#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm> // for std::sort
#include <fstream>   // for unit test output

using std::cout;
using std::endl;
using std::sort;

const int NUMBERS_SIZE = 50000;
const int CLOCKS_PER_MS = CLOCKS_PER_SEC / 1000;

int genRandInt(int low, int high) {
    return low + rand() % (high - low + 1);
}

void fillArrays(int arr1[], int arr2[], int arr3[]) {
    for (int i = 0; i < NUMBERS_SIZE; ++i) {
        arr1[i] = genRandInt(0, NUMBERS_SIZE);
        arr2[i] = arr1[i];
        arr3[i] = arr1[i];
    }
}

void InsertionSort(int numbers[], int numbersSize) {
    for (int i = 1; i < numbersSize; ++i) {
        int key = numbers[i];
        int j = i - 1;
        while (j >= 0 && numbers[j] > key) {
            numbers[j + 1] = numbers[j];
            --j;
        }
        numbers[j + 1] = key;
    }
}

int Partition_midpoint(int numbers[], int i, int k) {
    int midpoint = i + (k - i) / 2;
    int pivot = numbers[midpoint];
    int low = i;
    int high = k;

    while (true) {
        while (numbers[low] < pivot) {
            ++low;
        }
        while (numbers[high] > pivot) {
            --high;
        }
        if (low >= high) {
            return high;
        }
        std::swap(numbers[low], numbers[high]);
        ++low;
        --high;
    }
}

void Quicksort_midpoint(int numbers[], int i, int k) {
    if (i >= k) return;
    int pivotIndex = Partition_midpoint(numbers, i, k);
    Quicksort_midpoint(numbers, i, pivotIndex);
    Quicksort_midpoint(numbers, pivotIndex + 1, k);
}

int medianOfThree(int numbers[], int i, int k) {
    int mid = i + (k - i) / 2;
    if (numbers[i] > numbers[mid]) std::swap(numbers[i], numbers[mid]);
    if (numbers[i] > numbers[k]) std::swap(numbers[i], numbers[k]);
    if (numbers[mid] > numbers[k]) std::swap(numbers[mid], numbers[k]);
    return mid;
}

int Partition_medianOfThree(int numbers[], int i, int k) {
    int pivotIndex = medianOfThree(numbers, i, k);
    int pivot = numbers[pivotIndex];
    int low = i;
    int high = k;

    while (true) {
        while (numbers[low] < pivot) {
            ++low;
        }
        while (numbers[high] > pivot) {
            --high;
        }
        if (low >= high) {
            return high;
        }
        std::swap(numbers[low], numbers[high]);
        ++low;
        --high;
    }
}

void Quicksort_medianOfThree(int numbers[], int i, int k) {
    if (i >= k) return;
    int pivotIndex = Partition_medianOfThree(numbers, i, k);
    Quicksort_medianOfThree(numbers, i, pivotIndex);
    Quicksort_medianOfThree(numbers, pivotIndex + 1, k);
}

int main() {
    srand(time(0));

    int arr1[NUMBERS_SIZE];
    int arr2[NUMBERS_SIZE];
    int arr3[NUMBERS_SIZE];

    fillArrays(arr1, arr2, arr3);

    clock_t Start, End;
    int elapsedTime;

    // Quicksort_midpoint
    Start = clock();
    Quicksort_midpoint(arr1, 0, NUMBERS_SIZE - 1);
    End = clock();
    elapsedTime = (End - Start) / CLOCKS_PER_MS;
    cout << "Quicksort_midpoint runtime: " << elapsedTime << " ms" << endl;

    // Quicksort_medianOfThree
    Start = clock();
    Quicksort_medianOfThree(arr2, 0, NUMBERS_SIZE - 1);
    End = clock();
    elapsedTime = (End - Start) / CLOCKS_PER_MS;
    cout << "Quicksort_medianOfThree runtime: " << elapsedTime << " ms" << endl;

    // InsertionSort
    Start = clock();
    InsertionSort(arr3, NUMBERS_SIZE);
    End = clock();
    elapsedTime = (End - Start) / CLOCKS_PER_MS;
    cout << "InsertionSort runtime: " << elapsedTime << " ms" << endl;

    return 0;
}
