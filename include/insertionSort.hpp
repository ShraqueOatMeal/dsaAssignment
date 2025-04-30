#pragma once

#include "LinkList.h"
#include "reviews.h"
#include "transactions.h"
#include <string>
using namespace std;

class insertionSort {
public:
    insertionSort();
    ~insertionSort();

    // Sorting for linked list
    static void insertionSortTransactions(LinkList<transactions> *transactionList);
    static void insertionSortReviews(LinkList<reviews> *reviewsList);
    
    // Sorting for array
    static void insertionSortTransactions(transactions *transArray, int size);
    static void insertionSortReviews(transactions *reviewArray, int size);

    // Helper functions
    static bool compareDates(const string &date1, const string &date2);
};