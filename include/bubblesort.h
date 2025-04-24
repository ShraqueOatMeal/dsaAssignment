#pragma once
#include "LinkList.h"
#include "transactions.h"

class bubblesort {
public:
  bubblesort();
  ~bubblesort();
  static void bubbleSortByDate(transactions *arr, int size);
  static void displaySortedByDate(LinkList<transactions> &list);
};
