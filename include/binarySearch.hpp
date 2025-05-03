#pragma once
#include "JoinedData.h"
#include "WordFrequency.h" 
using namespace std;


class binarySearch {
public:
    // Helper function to calculate the percentage of selected purchases with payment method chosen
    static double calculatePercentage(int count, int total);
    
    // Linked List
    static Node<transactions> *findMiddle(Node<transactions> *head, Node<transactions>* end);
    static Node<transactions> *binarySearchLinkedList(Node<transactions> *start, Node<transactions> *end, const string &selectedCat, const string &selectedPaymentMethod);
    static void calculatePurchasesPaymentMethodPercentage(LinkList<transactions>& transactionList, const string &selectedCat, const string &selectedPaymentMethod);
    
    static Node<reviews> *findMiddle(Node<reviews> *head, Node<reviews>* end);
    static Node<reviews>* binarySearchLinkedList(Node<reviews>* start, Node<reviews>* end, int rating);
    static int calculateBadReviewsCommonWords(LinkList<reviews>& reviewList, int rating);
    
    // Array
    static int calculatedPurchasesPaymentMethodPercentage(transactions *transArray, int size, const string &selectedCat, const string &selectedPaymentMethod);
    static int calculateBadReviewsCommonWords(reviews *reviewArray, int size);
    
};