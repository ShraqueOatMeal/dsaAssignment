#include "bubblesort.h"
#include "LinkList.h"
#include "transactions.h"
#include <iostream>
#include <string>
using namespace std;

// Helper: Convert linked list to array
transactions* toArray(LinkList<transactions>& list, int& size) {
    Node<transactions>* current = list.getHead();
    size = 0;

    while (current) {
        size++;
        current = current->next;
    }

    transactions* arr = new transactions[size];

    current = list.getHead();
    int index = 0;
    while (current) {
        arr[index++] = current->data;
        current = current->next;
    }

    return arr;
    
}


// Bubble Sort by Date (DD/MM/YYYY)
void bubblesort::bubbleSortByDate(transactions* arr, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j].date > arr[j + 1].date) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}


// Main function: Display sorted transactions by date
void bubblesort::displaySortedByDate(LinkList<transactions>& list) {
    int size = 0;
    transactions* arr = toArray(list, size);

    bubbleSortByDate(arr, size);

    cout << "Transactions sorted by date (Bubble Sort):\n";
    for (int i = 0; i < size; i++) {
        arr[i].print();
    }

    delete[] arr; // Clean up
}
