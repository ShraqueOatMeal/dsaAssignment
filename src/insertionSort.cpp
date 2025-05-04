#include "insertionSort.hpp"
#include "LinkList.h"
#include "reviews.h"
#include "transactions.h"
#include <chrono>
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

bool insertionSort::compareDates(const string &date1, const string &date2) {
  int parseDate1 = parseDate(date1);
  int parseDate2 = parseDate(date2);

  return parseDate1 < parseDate2;
}

// ===========================ARRAY==========================
// Insertion Sort for array
void insertionSort::insertionsort(transactions *transArray, int size) {
  for (int i = 1; i < size; i++) {
    transactions key = transArray[i];
    int j = i - 1;

    while (j >= 0 && compareDates(transArray[j].date, key.date)) {
      transArray[j + 1] = transArray[j];
      j = j - 1;
    }
    transArray[j + 1] = key;
  }
}

// Insertion Sort for reviews array
void insertionSort::insertionsort(reviews *reviewArray, int size) {
  for (int i = 1; i < size; i++) {
    reviews key = reviewArray[i];
    int j = i - 1;

    while (j >= 0 && reviewArray[j].rating > key.rating) {
      reviewArray[j + 1] = reviewArray[j];
      j = j - 1;
    }
    reviewArray[j + 1] = key;
  }
}

// Insertion Sort for JoinedData array
void insertionSort::insertionsort(mergedData *joinedDataArray, int size) {
  for (int i = 1; i < size; i++) {
    mergedData key = joinedDataArray[i];
    int j = i - 1;

    while (j >= 0 && compareDates(joinedDataArray[j].date, key.date)) {
      joinedDataArray[j + 1] = joinedDataArray[j];
      j = j - 1;
    }
    joinedDataArray[j + 1] = key;
  }
}

// Insertion Sort for word frequency array
void insertionSort::insertionsort(WordFrequency *wordArray, int size) {
  for (int i = 1; i < size; i++) {
    WordFrequency key = wordArray[i];
    int j = i - 1;

    // Sort by count (descending), then by rating (ascending)
    while (j >= 0 && (wordArray[j].count < key.count ||
                      wordArray[j].count == key.count)) {
      wordArray[j + 1] = wordArray[j];
      j--;
    }
    wordArray[j + 1] = key;
  }
}

// Insertion Sort for transactions array by category and payment method
void insertionSort::Category_PaymentMethod(transactions *transArray, int size) {
  for (int i = 1; i < size; i++) {
    transactions key = transArray[i];
    int j = i - 1;

    while (j >= 0 && (transArray[j].cat > key.cat ||
                      (transArray[j].cat == key.cat &&
                       transArray[j].paymentMethod > key.paymentMethod))) {
      transArray[j + 1] = transArray[j];
      j = j - 1;
    }
    transArray[j + 1] = key;
  }
}

// ==========================LINKED LIST==========================

// Insertion Sort for linked list
void insertionSort::insertionsort(LinkList<transactions> *transactionList) {
  if (transactionList->getHead() == nullptr ||
      transactionList->getHead()->next == nullptr) {
    // List is empty or has only one element, no sorting needed
    return;
  }

  Node<transactions> *sorted = nullptr; // Start with an empty sorted list
  Node<transactions> *current =
      transactionList->getHead(); // Current node to be inserted

  while (current != nullptr) {
    Node<transactions> *next = current->next; // Save the next node
    sorted = insertIntoSortedList(
        sorted, current); // Insert current into the sorted list
    current = next;       // Move to the next node
  }

  // Update the head of the original list to point to the sorted list
  transactionList->setHead(sorted);
}

// Insertion Sort for reviews linked list
void insertionSort::insertionsort(LinkList<reviews> *reviewsList) {
  if (reviewsList->getHead() == nullptr ||
      reviewsList->getHead()->next == nullptr) {
    // List is empty or has only one element, no sorting needed
    return;
  }

  Node<reviews> *sorted = nullptr; // Start with an empty sorted list
  Node<reviews> *current =
      reviewsList->getHead(); // Current node to be inserted

  while (current != nullptr) {
    Node<reviews> *next = current->next; // Save the next node
    sorted = insertIntoSortedList(
        sorted, current); // Insert current into the sorted list
    current = next;       // Move to the next node
  }

  // Update the head of the original list to point to the sorted list
  reviewsList->setHead(sorted);
}

// Inserting JoinedData into sorted linked list
void insertionSort::insertionsort(LinkList<mergedData> *JoinedDataList) {
  if (JoinedDataList->getHead() == nullptr ||
      JoinedDataList->getHead()->next == nullptr) {
    // List is empty or has only one element, no sorting needed
    return;
  }

  Node<mergedData> *sorted = nullptr; // Start with an empty sorted list
  Node<mergedData> *current =
      JoinedDataList->getHead(); // Current node to be inserted

  while (current != nullptr) {
    Node<mergedData> *next = current->next; // Save the next node
    sorted = insertionSort::insertIntoSortedList(
        sorted, current); // Insert current into the sorted list
    current = next;       // Move to the next node
  }

  // Update the head of the original list to point to the sorted list
  JoinedDataList->setHead(sorted);
}

// Insertion Sort for word frequency linked list
void insertionSort::insertionsort(LinkList<WordFrequency> *wordList) {
  if (!wordList || !wordList->getHead())
    return;

  Node<WordFrequency> *sorted = nullptr;
  Node<WordFrequency> *current = wordList->getHead();

  while (current != nullptr) {
    Node<WordFrequency> *next = current->next;
    if (!sorted || sorted->data.count <= current->data.count) {
      current->next = sorted;
      sorted = current;
    } else {
      Node<WordFrequency> *temp = sorted;
      while (temp->next != nullptr &&
             temp->next->data.count > current->data.count) {
        temp = temp->next;
      }
      current->next = temp->next;
      temp->next = current;
    }
    current = next;
  }

  wordList->setHead(sorted);
}

// Insertion Sort for transactions linked list by category and payment method
void insertionSort::Category_PaymentMethod(
    LinkList<transactions> *transactionList) {
  if (transactionList->getHead() == nullptr ||
      transactionList->getHead()->next == nullptr) {
    // List is empty or has only one element, no sorting needed
    return;
  }

  Node<transactions> *sorted = nullptr; // Start with an empty sorted list
  Node<transactions> *current =
      transactionList->getHead(); // Current node to be inserted

  while (current != nullptr) {
    Node<transactions> *next = current->next; // Save the next node
    sorted = insertIntoSortedListByCategoryPaymentMethod(
        sorted, current); // Insert current into the sorted list
    current = next;       // Move to the next node
  }

  // Update the head of the original list to point to the sorted list
  transactionList->setHead(sorted);
}

// Helper function to insert a node into a sorted linked list by category and
// payment method
Node<transactions> *insertionSort::insertIntoSortedListByCategoryPaymentMethod(
    Node<transactions> *sorted, Node<transactions> *newNode) {
  if (sorted == nullptr ||
      (newNode->data.cat < sorted->data.cat ||
       (newNode->data.cat == sorted->data.cat &&
        newNode->data.paymentMethod < sorted->data.paymentMethod))) {
    // Insert at the beginning of the sorted list
    newNode->next = sorted;
    return newNode;
  }

  Node<transactions> *current = sorted;
  while (current->next != nullptr &&
         (current->next->data.cat < newNode->data.cat ||
          (current->next->data.cat == newNode->data.cat &&
           current->next->data.paymentMethod < newNode->data.paymentMethod))) {
    current = current->next;
  }

  // Insert newNode after current
  newNode->next = current->next;
  current->next = newNode;

  return sorted;
}

// Helper function to insert a node into a sorted singly linked list
Node<transactions> *
insertionSort::insertIntoSortedList(Node<transactions> *sorted,
                                    Node<transactions> *newNode) {
  if (sorted == nullptr ||
      compareDates(newNode->data.date, sorted->data.date)) {
    // Insert at the beginning of the sorted list
    newNode->next = sorted;
    return newNode;
  }

  Node<transactions> *current = sorted;
  while (current->next != nullptr &&
         compareDates(current->next->data.date, newNode->data.date)) {
    current = current->next;
  }

  // Insert newNode after current
  newNode->next = current->next;
  current->next = newNode;

  return sorted;
}

Node<reviews> *insertionSort::insertIntoSortedList(Node<reviews> *sorted,
                                                   Node<reviews> *newNode) {
  if (sorted == nullptr || newNode->data.rating > sorted->data.rating) {
    // Insert at the beginning of the sorted list
    newNode->next = sorted;
    return newNode;
  }

  Node<reviews> *current = sorted;
  while (current->next != nullptr &&
         current->next->data.rating > newNode->data.rating) {
    current = current->next;
  }

  // Insert newNode after current
  newNode->next = current->next;
  current->next = newNode;

  return sorted;
}

Node<mergedData> *
insertionSort::insertIntoSortedList(Node<mergedData> *sorted,
                                    Node<mergedData> *newNode) {
  if (!sorted || compareDates(newNode->data.date, sorted->data.date)) {
    newNode->next = sorted;
    return newNode;
  }

  Node<mergedData> *current = sorted;
  while (current->next &&
         !compareDates(newNode->data.date, current->next->data.date)) {
    current = current->next;
  }

  newNode->next = current->next;
  current->next = newNode;

  return sorted;
}
