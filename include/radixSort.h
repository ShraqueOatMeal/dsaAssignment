#pragma once

#include "LinkList.h"
#include "reviews.h"
#include "transactions.h"

class radixSort {
public:
  radixSort();
  ~radixSort();
  static void radixsort(transactions *transArray, int n);
  static void radixsort(reviews *reviewArray, int n);
  static void radixsort(LinkList<transactions> *transactionList, int n);
  static void countSort(reviews *reviewArray, int n);
  static void countSort(LinkList<reviews> *reviewList, int n);
};
