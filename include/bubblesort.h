#pragma once
#include "LinkList.h"
#include "transactions.h"

class bubblesort {
public:
    static void bubbleSortByDate(transactions* arr, int size);
    static void displaySortedByDate(LinkList<transactions>& list);
    static transactions* getSortedArrayByDate(LinkList<transactions>& list, int& size); // 🔥 NEW
};
