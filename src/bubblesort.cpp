#include "bubblesort.h"
#include "JoinedData.h"
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

// Bubble sort on linked list of mergedData
void bubblesort::bubbleSortByDate(LinkList<mergedData> &list) {
  bool swapped;
  Node<mergedData> *ptr1;
  Node<mergedData> *lptr = nullptr;

  if (list.getHead() == nullptr)
    return;

  do {
    swapped = false;
    ptr1 = list.getHead();

    while (ptr1->next != lptr) {
      int date1 = convertDateToInt(ptr1->data.date);
      int date2 = convertDateToInt(ptr1->next->data.date);

      if (date1 > date2) {
        swap(ptr1->data, ptr1->next->data);
        swapped = true;
      }
      ptr1 = ptr1->next;
    }
    lptr = ptr1;
  } while (swapped);
}

// Bubble sort on of Arrays of mergedData
void bubblesort::displaySortedByDate(mergedData *arr, int size) {

  // Sort using Bubble Sort
  for (int i = 0; i < size - 1; i++) {
    for (int j = 0; j < size - i - 1; j++) {
      int date1 = convertDateToInt(arr[j].date);
      int date2 = convertDateToInt(arr[j + 1].date);
      if (date1 > date2) {
        swap(arr[j], arr[j + 1]);
      }
    }
  }
}

// Display and sort mergedData linked list
void bubblesort::displaySortedByDate(LinkList<mergedData> &list) {

  bubbleSortByDate(list); // Sort in-place using linked list logic
}

// Bubble sort on linked list of transactions
void bubblesort::bubbleSortByDate(LinkList<transactions> &list) {
  bool swapped;
  Node<transactions> *ptr1;
  Node<transactions> *lptr = nullptr;

  if (list.getHead() == nullptr)
    return;

  do {
    swapped = false;
    ptr1 = list.getHead();

    while (ptr1->next != lptr) {
      int date1 = convertDateToInt(ptr1->data.date);
      int date2 = convertDateToInt(ptr1->next->data.date);

      if (date1 > date2) {
        swap(ptr1->data, ptr1->next->data);
        swapped = true;
      }
      ptr1 = ptr1->next;
    }
    lptr = ptr1;
  } while (swapped);
}

// Display and sort transactions from linked list
void bubblesort::displaySortedByDate(LinkList<transactions> &list) {

  bubbleSortByDate(list); // In-place sort
}

void bubblesort::bubbleSortByDate(transactions *arr, int size) {
  for (int i = 0; i < size - 1; ++i) {
    for (int j = 0; j < size - i - 1; ++j) {
      int date1 = convertDateToInt(arr[j].date);
      int date2 = convertDateToInt(arr[j + 1].date);
      if (date1 > date2) {
        swap(arr[j], arr[j + 1]);
      }
    }
  }
}

void bubblesort::displaySortedByDate(transactions *arr, int size) {

  bubblesort::bubbleSortByDate(arr, size); // sort the original array
}

void bubblesort::bubbleSortByCategory(transactions *arr, int size) {
  for (int i = 0; i < size - 1; i++) {
    for (int j = 0; j < size - i - 1; j++) {
      if (arr[j].cat > arr[j + 1].cat) {
        swap(arr[j], arr[j + 1]);
      }
    }
  }
}

void bubblesort::bubbleSortByCategory(LinkList<transactions> &list) {
  bool swapped;
  Node<transactions> *ptr1;
  Node<transactions> *lptr = nullptr;

  if (list.getHead() == nullptr)
    return;

  do {
    swapped = false;
    ptr1 = list.getHead();

    while (ptr1->next != lptr) {
      if (ptr1->data.cat > ptr1->next->data.cat) {
        swap(ptr1->data, ptr1->next->data);
        swapped = true;
      }
      ptr1 = ptr1->next;
    }
    lptr = ptr1;
  } while (swapped);
}
