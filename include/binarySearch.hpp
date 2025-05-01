#pragma once
#include "JoinedData.h"
using namespace std;


class binarySearch {
public:
    static void calculatedPurchasesPaymentMethodPercentage(LinkList<transactions> &transactionList, int size, 
        const string selectedCat, const string selectedPaymentMethod);
    static void calculateBadReviewsCommonSentences(LinkList<reviews> &reviewList);
    
    static void calculatedPurchasesPaymentMethodPercentage(transactions *transArray, int size, 
        const string selectedCat, const string selectedPaymentMethod);
    static void calculateBadReviewsCommonSentences(reviews *reviewArray, int size);
  
};