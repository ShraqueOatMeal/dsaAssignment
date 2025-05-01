#pragma once

#include "JoinedData.h"
#include "LinkList.h"
#include "reviews.h"
#include "transactions.h"
#include <string>
using namespace std;

template <typename T> struct insertNode {
  T data;
  Node<T> *next;
};

class insertionSort {
  Node<transactions> *head;
  Node<transactions> *tail;
  int size;
  static Node<transactions> *insertIntoSortedList(Node<transactions> *sorted,
                                                  Node<transactions> *newNode);
  static Node<reviews> *insertIntoSortedList(Node<reviews> *sorted,
                                             Node<reviews> *newNode);
  static Node<mergedData> *insertIntoSortedList(Node<mergedData> *sorted,
                                                Node<mergedData> *newNode);

public:
  // Sorting for linked list
  static void insertionsort(LinkList<transactions> *transactionList);
  static void insertionsort(LinkList<reviews> *reviewsList);
  static void insertionsort(LinkList<mergedData> *JoinedDataList);
  static void insertionSortCategory(LinkList<transactions> *transactionList);
  static void insertionSortReview(LinkList<reviews> *transactionList);

  // Sorting for array
  static void insertionsort(transactions *transArray, int size);
  static void insertionsort(reviews *reviewArray, int size);
  static void insertionsort(mergedData *JoinedData, int size);
  static void insertionSortCategory(transactions *transArray, int size);
  static void insertionSortReview(reviews *reviewArray, int size);

  // Helper functions
  static bool compareDates(const string &date1, const string &date2);
};
