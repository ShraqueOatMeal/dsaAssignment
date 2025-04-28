#include "radixSort.h"
#include "JoinedData.h"
#include "LinkList.h"
#include "reviews.h"
#include "transactions.h"
#include <string>

radixSort::radixSort() {
  // Constructor implementation
}

radixSort::~radixSort() {
  // Destructor implementation
}

int dateToInt(const std::string &dateStr) {
  int day = std::stoi(dateStr.substr(0, 2));
  int month = std::stoi(dateStr.substr(3, 2));
  int year = std::stoi(dateStr.substr(6, 4));

  return year * 10000 + month * 100 + day;
}

int maxDate(LinkList<transactions> *transactionList, int n) {

  Node<transactions> *current = transactionList->getHead();
  int max = dateToInt(current->data.date);

  while (current != nullptr) {
    int dateVal = dateToInt(current->data.date);
    if (dateVal > max) {
      max = dateVal;
    }
    current = current->next;
  }
  return max;
}

int maxDate(transactions *transArray, int n) {

  int max = dateToInt(transArray[0].date);

  for (int i = 0; i < n; i++) {
    int dateVal = dateToInt(transArray[i].date);
    if (dateVal > max) {
      max = dateVal;
    }
  }

  return max;
}

void countSort(LinkList<transactions> *transactionList, int n, int exp) {
  LinkList<transactions> count[10];

  Node<transactions> *current = transactionList->getHead();

  while (current != nullptr) {
    int dateVal = dateToInt(current->data.date);
    int digit = (dateVal / exp) % 10;
    count[digit].addData(current->data);
    current = current->next;
  }

  transactionList->clear();

  for (int i = 0; i < 10; i++) {
    Node<transactions> *countNode = count[i].getHead();
    while (countNode != nullptr) {
      transactionList->addData(countNode->data);
      countNode = countNode->next;
    }
  }
}

void countSort(transactions *transArray, int n, int exp) {
  transactions *output = new transactions[n];
  int count[10] = {0};

  for (int i = 0; i < n; i++) {
    int dateVal = dateToInt(transArray[i].date);
    count[(dateVal / exp) % 10]++;
  }

  for (int i = 1; i < 10; i++)
    count[i] += count[i - 1];

  for (int i = n - 1; i >= 0; i--) {
    int dateVal = dateToInt(transArray[i].date);
    output[count[(dateVal / exp) % 10] - 1] = transArray[i];
    count[(dateVal / exp) % 10]--;
  }

  for (int i = 0; i < n; i++)
    transArray[i] = output[i];
}

void radixSort::countSort(reviews *reviewArray, int n) {
  reviews *output = new reviews[n];
  int count[10] = {0};

  for (int i = 0; i < n; i++)
    count[reviewArray[i].rating % 10]++;

  for (int i = 1; i < 10; i++)
    count[i] += count[i - 1];

  for (int i = n - 1; i >= 0; i--) {
    output[count[reviewArray[i].rating % 10] - 1] = reviewArray[i];
    count[reviewArray[i].rating % 10]--;
  }

  for (int i = 0; i < n; i++)
    reviewArray[i] = output[i];
}

void radixSort::countSort(LinkList<reviews> *reviewList, int n) {
  LinkList<reviews> count[10];

  Node<reviews> *current = reviewList->getHead();

  while (current != nullptr) {
    count[current->data.rating % 10].addData(current->data);
    current = current->next;
  }

  reviewList->clear();

  for (int i = 0; i < 10; i++) {
    Node<reviews> *countNode = count[i].getHead();
    while (countNode != nullptr) {
      reviewList->addData(countNode->data);
      countNode = countNode->next;
    }
  }
}

void radixSort::radixsort(transactions *transArray, int n) {

  int m = maxDate(transArray, n);

  for (int exp = 1; m / exp > 0; exp *= 10)
    ::countSort(transArray, n, exp);
}

void radixSort::radixsort(LinkList<transactions> *transactionList, int n) {

  int m = maxDate(transactionList, n);

  for (int exp = 1; m / exp > 0; exp *= 10)
    ::countSort(transactionList, n, exp);
}

int maxDate(LinkList<mergedData> *mergedList, int n) {
  Node<mergedData> *current = mergedList->getHead();
  int max = dateToInt(current->data.date);

  while (current != nullptr) {
    int dateVal = dateToInt(current->data.date);
    if (dateVal > max) {
      max = dateVal;
    }
    current = current->next;
  }
  return max;
}

int maxDate(mergedData *mergedArray, int n) {
  int max = dateToInt(mergedArray[0].date);

  for (int i = 0; i < n; i++) {
    int dateVal = dateToInt(mergedArray[i].date);
    if (dateVal > max) {
      max = dateVal;
    }
  }

  return max;
}

void countSort(LinkList<mergedData> *mergedList, int n, int exp) {
  LinkList<mergedData> count[10];

  Node<mergedData> *current = mergedList->getHead();

  while (current != nullptr) {
    int dateVal = dateToInt(current->data.date);
    int digit = (dateVal / exp) % 10;
    count[digit].addData(current->data);
    current = current->next;
  }

  mergedList->clear();

  for (int i = 0; i < 10; i++) {
    Node<mergedData> *countNode = count[i].getHead();
    while (countNode != nullptr) {
      mergedList->addData(countNode->data);
      countNode = countNode->next;
    }
  }
}

void countSort(mergedData *mergedArray, int n, int exp) {
  mergedData *output = new mergedData[n];
  int count[10] = {0};

  for (int i = 0; i < n; i++) {
    int dateVal = dateToInt(mergedArray[i].date);
    count[(dateVal / exp) % 10]++;
  }

  for (int i = 1; i < 10; i++)
    count[i] += count[i - 1];

  for (int i = n - 1; i >= 0; i--) { // reverse order
    int dateVal = dateToInt(mergedArray[i].date);
    output[count[(dateVal / exp) % 10] - 1] = mergedArray[i];
    count[(dateVal / exp) % 10]--;
  }

  for (int i = 0; i < n; i++)
    mergedArray[i] = output[i];

  delete[] output;
}

void radixSort::radixsort(LinkList<mergedData> *mergedList, int n) {

  int m = maxDate(mergedList, n);

  for (int exp = 1; m / exp > 0; exp *= 10)
    ::countSort(mergedList, n, exp);
}

void radixSort::radixsort(mergedData *mergedArray, int n) {

  int m = maxDate(mergedArray, n);

  for (int exp = 1; m / exp > 0; exp *= 10)
    ::countSort(mergedArray, n, exp);
}
