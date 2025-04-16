#pragma once

#include "reviews.h"
#include "transactions.h"

class radixSort {
public:
  radixSort();
  ~radixSort();
  static void radixsort(transactions *transArray, int n);
  static void radixsort(reviews *reviewArray, int n);
};
