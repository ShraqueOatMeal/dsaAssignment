#include "binarySearch.hpp"
#include <iostream>
using namespace std;

// // ===========================ARRAY==========================

// Calculate the percentage of selected purchases with payment method chosen
int binarySearch::calculatedPurchasesPaymentMethodPercentage(transactions *transArray, const string &selectedCat, const string &selectedPaymentMethod) {
    int left = 0;
    int right = sizeof(transArray) / sizeof(transArray[0]) - 1;
    int count = 0;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (transArray[mid].cat == selectedCat && transArray[mid].paymentMethod == selectedPaymentMethod) {
            count++;
            // Check for duplicates on the left side
            int temp = mid - 1;
            while (temp >= left && transArray[temp].cat == selectedCat && transArray[temp].paymentMethod == selectedPaymentMethod) {
                count++;
                temp--;
            }
            // Check for duplicates on the right side
            temp = mid + 1;
            while (temp <= right && transArray[temp].cat == selectedCat && transArray[temp].paymentMethod == selectedPaymentMethod) {
                count++;
                temp++;
            }
            break; // Exit the loop once we find the first occurrence
        } else if (transArray[mid].cat < selectedCat || (transArray[mid].cat == selectedCat && transArray[mid].paymentMethod < selectedPaymentMethod)) {
            left = mid + 1;
        } else {
            right = mid - 1;
        } 
        
    }
    return count;
}

// Calculate the rating of bad reviews

// // ===========================LINKED LIST==========================
// // Calculate the percentage of selected purchases with payment method chosen
// void binarySearch::calculatedPurchasesPaymentMethodPercentage(LinkList<transactions> &transactionList, int size, 
//     const string selectedCat, const string selectedPaymentMethod){
        
// }

// // Calculate the percentage of selected purchases with payment method chosen
// void binarySearch::calculateBadReviewsCommonWords(LinkList<reviews> &reviewList) {
    
// }

