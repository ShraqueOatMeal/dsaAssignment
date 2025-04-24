#include "radixSort.h"
#include "LinkList.h"
#include "reviews.h"
#include "transactions.h"
#include <iostream>
#include <string>
using namespace std;

// Convert LinkedList to raw array
transactions* toArray(LinkList<transactions>& list, int& size) {
    Node<transactions>* current = list.getHead();
    size = 0;

    // First count the number of nodes
    while (current) {
        size++;
        current = current->next;
    }

    // Allocate raw array
    transactions* arr = new transactions[size];

    // Fill array
    current = list.getHead();
    int index = 0;
    while (current) {
        arr[index++] = current->data;
        current = current->next;
    }

    return arr;
}

// Bubble sort by date (YYYY-MM-DD format)
void bubbleSortByDate(transactions* arr, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j].date > arr[j + 1].date) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Display function for sorted results
void displaySortedByDate(LinkList<transactions>& list) {
    int size = 0;
    transactions* arr = toArray(list, size);

    bubbleSortByDate(arr, size);

    cout << "Transactions sorted by date:\n";
    for (int i = 0; i < size; i++) {
        arr[i].print();
    }

    delete[] arr; // Cleanup
}
