#pragma once

#include "LinkList.h"
#include "reviews.h"
#include "joinedData.h"
#include "transactions.h"
#include <string>
using namespace std;

template <typename T>
struct Node {
    T data;
    Node<T> *next;
};

class insertionSort {
    Node<transactions> *head;
    Node<transactions> *tail;
    int size;
    static Node<transactions>* insertionSort::insertIntoSortedList(Node<transactions> *sorted, Node<transactions> *newNode);
public:
    // Sorting for linked list
    static void insertionsort(LinkList<transactions> *transactionList);
    static void insertionsort(LinkList<reviews> *reviewsList);
    static void insertionsort(LinkList<JoinedData> *JoinedDataList);
    
    // Sorting for array
    static void insertionsort(transactions *transArray, int size);
    static void insertionsort(reviews *reviewArray, int size);
    static void insertionsort(JoinedData *JoinedData, int size);

    // Helper functions
    static bool compareDates(const string &date1, const string &date2);
};