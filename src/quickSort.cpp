#include "quickSort.hpp"
#include "LinkList.h"
#include "transactions.h"
#include <sstream>
#include <string>
using namespace std;

// Helper function: Convert dd/mm/yyyy to yyyymmdd
int parseDate(const string &date) {
  int day, month, year;
  char delimiter;
  stringstream ss(date);
  ss >> day >> delimiter >> month >> delimiter >> year;
  return year * 10000 + month * 100 + day;
}

// Helper function: Compare two dates
bool quickSort::compareDates(const string &date1, const string &date2) {
  return parseDate(date1) < parseDate(date2);
}

// Partition function for array
int quickSort::partition(transactions *transArray, int low, int high) {
  string pivotDate =
      transArray[high].date; // Assuming 'date' is a string in DD/MM/YYYY
  int i = low - 1;

  for (int j = low; j < high; j++) {
    if (compareDates(transArray[j].date, pivotDate)) {
      i++;
      swap(transArray[i], transArray[j]);
    }
  }
  swap(transArray[i + 1], transArray[high]);
  return i + 1;
}

// QuickSort for array
void quickSort::quickSortTransactions(transactions *transArray, int low,
                                      int high) {
  if (low < high) {
    int pivotIndex = partition(transArray, low, high);
    quickSortTransactions(transArray, low, pivotIndex - 1);
    quickSortTransactions(transArray, pivotIndex + 1, high);
  }
}

// Partition function for linked list
Node<transactions> *quickSort::partition(Node<transactions> *low,
                                         Node<transactions> *high,
                                         Node<transactions> **newLow,
                                         Node<transactions> **newHigh) {
  string pivotDate = high->data.date; // Pivot is the last node's date
  Node<transactions> *i = nullptr;    // Tracks the smaller element

  Node<transactions> *current = low;
  while (current != high) {
    if (compareDates(current->data.date, pivotDate)) {
      if (i == nullptr) {
        i = low;
      } else {
        i = i->next;
      }
      swap(i->data, current->data);
    }
    current = current->next;
  }

  // Swap the pivot node with the node after the last smaller element
  if (i == nullptr) {
    i = low;
  } else {
    i = i->next;
  }
  swap(i->data, high->data);

  *newLow = low;
  *newHigh = high;

  return i; // Return the pivot node
}

// QuickSort for linked list
void quickSort::quickSortLinkedList(Node<transactions> *low,
                                    Node<transactions> *high) {
  if (low == nullptr || low == high || low == high->next) {
    return;
  }

  Node<transactions> *newLow = nullptr;
  Node<transactions> *newHigh = nullptr;

  Node<transactions> *pivot = partition(low, high, &newLow, &newHigh);

  if (newLow != pivot) {
    Node<transactions> *temp = newLow;
    while (temp->next != pivot) {
      temp = temp->next;
    }
    temp->next = nullptr;
    quickSortLinkedList(newLow, temp);
    temp->next = pivot;
  }

  if (newHigh != pivot) {
    quickSortLinkedList(pivot->next, newHigh);
  }
}

// Helper function to start sorting a linked list
void quickSort::quickSortTransactions(LinkList<transactions> *transactionList) {
  if (transactionList->getHead() == nullptr) {
    return;
  }

  Node<transactions> *tail = transactionList->getHead();
  while (tail->next != nullptr) {
    tail = tail->next;
  }

  quickSortLinkedList(transactionList->getHead(), tail);
}
