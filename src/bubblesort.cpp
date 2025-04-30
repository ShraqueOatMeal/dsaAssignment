#include "bubblesort.h"
#include "LinkList.h"
#include "transactions.h"
#include <chrono>
#include <iostream>
#include <string>
using namespace std;

// Convert DD/MM/YYYY string to integer format YYYYMMDD
int convertDateToInt(const string &date) {
  int day = stoi(date.substr(0, 2));
  int month = stoi(date.substr(3, 2));
  int year = stoi(date.substr(6, 4));
  return year * 10000 + month * 100 + day;
}

// Helper: Convert linked list to array
transactions *toArray(LinkList<transactions> &list, int &size) {
  Node<transactions> *current = list.getHead();
  size = 0;

  while (current) {
    size++;
    current = current->next;
  }

  transactions *arr = new transactions[size];

  current = list.getHead();
  int index = 0;
  while (current) {
    arr[index++] = current->data;
    current = current->next;
  }

  return arr;
}

void bubblesort::bubbleSortByDate(transactions *arr, int size) {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size - i - 1; j++) {
      int date1 = convertDateToInt(arr[j].date);
      int date2 = convertDateToInt(arr[j + 1].date);

      if (date1 > date2) {
        swap(arr[j], arr[j + 1]);
      }
    }
  }
}

transactions *bubblesort::getSortedArrayByDate(LinkList<transactions> &list,
                                               int &size) {
  Node<transactions> *current = list.getHead();
  size = 0;

  while (current) {
    size++;
    current = current->next;
  }

  transactions *arr = new transactions[size];
  current = list.getHead();
  int index = 0;
  while (current) {
    arr[index++] = current->data;
    current = current->next;
  }

  bubbleSortByDate(arr, size); // Sort in place
  return arr;
}

// Display sorted transactions by date
void bubblesort::displaySortedByDate(LinkList<transactions> &list) {
  int size = 0;
  transactions *arr = toArray(list, size);

  // Start timing
  auto start = chrono::high_resolution_clock::now();

  bubbleSortByDate(arr, size); // Sorting

  // End timing
  auto end = chrono::high_resolution_clock::now();
  chrono::duration<double, milli> duration = end - start;

  cout << "Transactions sorted by date (Bubble Sort):\n";
  for (int i = 0; i < size; i++) {
    arr[i].print();
  }

  cout << "\n Sorting completed in " << duration.count() << " milliseconds.\n";
  cout << "Estimated Time Complexity of Bubble Sort: O(n^2) \n";
  cout << "Estimated space used of Bubble Sort: O(1) (in-place sorting)"
       << endl;

  delete[] arr;
}
