#pragma once

#include "LinkList.h"
#include "reviews.h"
#include "transactions.h"
#include <string>

class quickSort {
public:
    quickSort();
    ~quickSort();

    // Sorting for linked list
    static void quickSortTransactions(LinkList<transactions> *transactionList);

    // Sorting for array
    static void quickSortTransactions(transactions *transArray, int low, int high);

    // Helper functions
    static bool compareDates(const std::string &date1, const std::string &date2);

private:
    // Partition for array
    static int partition(transactions *transArray, int low, int high);

    // Partition for linked list
    static Node<transactions>* partition(Node<transactions>* low, Node<transactions>* high, Node<transactions>** newLow, Node<transactions>** newHigh);

    // QuickSort for linked list
    static void quickSortLinkedList(Node<transactions>* low, Node<transactions>* high);
};
