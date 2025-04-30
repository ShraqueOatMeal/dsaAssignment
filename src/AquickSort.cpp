#include "AquickSort.hpp"

AquickSort::AquickSort() {}
AquickSort::~AquickSort() {}

void AquickSort::quickSort(transactions *transArray, int low, int high) {
    if (low < high) {
        int pivotIndex = partition(transArray, low, high);
        quickSort(transArray, low, pivotIndex - 1);
        quickSort(transArray, pivotIndex + 1, high);
    }
}

void AquickSort::quickSort(reviews *reviewArray, int low, int high) {
    if (low < high) {
        int pivotIndex = partition(reviewArray, low, high);
        quickSort(reviewArray, low, pivotIndex - 1);
        quickSort(reviewArray, pivotIndex + 1, high);
    }
}

void AquickSort::swap(transactions &a, transactions &b) {
    transactions temp = a;
    a = b;
    b = temp;
}

void AquickSort::swap(reviews &a, reviews &b) {
    reviews temp = a;
    a = b;
    b = temp;
}

int AquickSort::partition(transactions *array, int low, int high) {
    transactions pivot = array[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (array[j] < pivot) {
            i++;
            swap(array[i], array[j]);
        }
    }
    swap(array[i + 1], array[high]);
    return i + 1;
}