#pragma once
#include "JoinedData.h"
#include "LinkList.h"
#include "transactions.h"

class bubblesort {
public:
  static void bubbleSortByDate(transactions* arr, int size);
  static void bubbleSortByDate(LinkList<transactions>& list);
  static void bubbleSortByDate(LinkList<mergedData> &list);
  static void displaySortedByDate(mergedData* arr, int size);

  static void displaySortedByDate(LinkList<mergedData>& list);
  static void displaySortedByDate(LinkList<transactions>& list);
  static void displaySortedByDate(transactions* arr, int size);
  static transactions* getSortedArrayByDate(LinkList<transactions>& list, int& size);
};
