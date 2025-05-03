#pragma once
#include "JoinedData.h"
#include "WordFrequency.h" 
using namespace std;


class binarySearch {
public:
    // Helper function to calculate the percentage of selected purchases with payment method chosen
    static double calculatePercentage(int count, int total);

    // Helper function to find the middle node in a linked list
    template <typename T>
    Node<T> *findMiddle(Node<T> *start, Node<T> *end);
    
    // Linked List
    static Node<transactions> *binarySearchLinkedList(Node<transactions> *start, Node<transactions> *end, const string &selectedCat, const string &selectedPaymentMethod);
    static void calculatePurchasesPaymentMethodPercentage(LinkList<transactions> &transactionList, const string &selectedCat, const string &selectedPaymentMethod);
    
    static Node<reviews> *findMiddle(Node<WordFrequency> *head, Node<WordFrequency>* end);
    static Node<WordFrequency>* binarySearchLinkedList(Node<WordFrequency>* start, Node<WordFrequency>* end, const string& word);
    static void calculateBadReviewsCommonWords(LinkList<WordFrequency> &wordList, const string &word);
    
    // Array
    static int calculatedPurchasesPaymentMethodPercentage(transactions *transArray, int size, const string &selectedCat, const string &selectedPaymentMethod);
};