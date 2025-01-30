#ifndef LABA_3_SORTS_H
#define LABA_3_SORTS_H


#include "Record.h"

class Sorts {
public:
    static void ShakerSort(Record arr[], int size);

    static void HeapSort(Record arr[], int size);

    static bool isStable(Record arr[], int size);

private:
    static void heapify(Record arr[], int n, int i);
};


#endif //LABA_3_SORTS_H
