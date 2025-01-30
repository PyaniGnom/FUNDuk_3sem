#include "Sorts.h"

void Sorts::ShakerSort(Record* arr, int size) {
    int left = 0;
    int right = size - 1;
    int lastSwap;
    bool swapped;

    while (left < right) {
        // Проход слева направо
        swapped = false;
        lastSwap = left;
        for (int i = left; i < right; ++i) {
            if (arr[i] > arr[i + 1]) {
                Record temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;

                swapped = true;
                lastSwap = i;
            }
        }
        if (!swapped) break;
        right = lastSwap;

        // Проход справа налево
        swapped = false;
        lastSwap = right;
        for (int i = right; i > left; --i) {
            if (arr[i - 1] > arr[i]) {
                Record temp = arr[i];
                arr[i] = arr[i - 1];
                arr[i - 1] = temp;

                swapped = true;
                lastSwap = i;
            }
        }
        if (!swapped) break;
        left = lastSwap;
    }
}

void Sorts::HeapSort(Record* arr, int size) {
    for (int i = size / 2 - 1; i >= 0; --i) {
        heapify(arr, size, i);
    }

    for (int i = size - 1; i > 0; --i) {
        Record temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        heapify(arr, i, 0);
    }
}

bool Sorts::isStable(Record* arr, int size) {
    for (int i = 1; i < size; ++i) {
        if (arr[i].FirstKey == arr[i - 1].FirstKey && arr[i].SecondKey == arr[i - 1].SecondKey) {
            if (arr[i].LineNumber < arr[i - 1].LineNumber) {
                return false;
            }
        }
    }
    return true;
}

void Sorts::heapify(Record* arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[largest] < arr[left]) {
        largest = left;
    }

    if (right < n && arr[largest] < arr[right]) {
        largest = right;
    }

    if (largest != i) {
        Record temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        heapify(arr, n, largest);
    }
}
