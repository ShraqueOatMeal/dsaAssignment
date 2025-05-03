#include "binarySearch.hpp"
#include <iostream>
#include <iomanip>
using namespace std;

// Helper function to calculate the percentage of selected purchases with payment method chosen
double binarySearch::calculatePercentage(int count, int total) {
    if (total == 0) {
        return 0.0; 
    }
    return (static_cast<double>(count) / total) * 100;
}

// // ===========================ARRAY==========================

// Calculate the percentage of selected purchases with payment method chosen
int binarySearch::calculatedPurchasesPaymentMethodPercentage(transactions *transArray, int size, const string &selectedCat, const string &selectedPaymentMethod) {
    int left = 0;
    int right = size - 1;
    int count = 0;
    int total = 0;

    // Calculate total transactions under the selected category
    for (int i = 0; i < size; i++) {
        if (transArray[i].cat == selectedCat) {
            total++;
        }
    }

    // Find the first occurrence
    int first = -1;
    left = 0;
    right = size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (transArray[mid].cat == selectedCat && transArray[mid].paymentMethod == selectedPaymentMethod) {
            first = mid;
            right = mid - 1; // Continue searching in the left half
        } else if (transArray[mid].cat < selectedCat || 
                  (transArray[mid].cat == selectedCat && transArray[mid].paymentMethod < selectedPaymentMethod)) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    // Find the last occurrence
    int last = -1;
    left = 0;
    right = size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (transArray[mid].cat == selectedCat && transArray[mid].paymentMethod == selectedPaymentMethod) {
            last = mid;
            left = mid + 1; // Continue searching in the right half
        } else if (transArray[mid].cat < selectedCat || 
                  (transArray[mid].cat == selectedCat && transArray[mid].paymentMethod < selectedPaymentMethod)) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    // Calculate count
    if (first != -1 && last != -1) {
        count = last - first + 1;
    }

    // Handle case where no matches are found
    if (count == 0) {
        cout << "No matching transactions found for Category: " << selectedCat
             << " and Payment Method: " << selectedPaymentMethod << endl;
        return 0;
    }

    // Print results
    double percentage = calculatePercentage(count, total);
    cout << "Category: " << selectedCat << endl;
    cout << "Payment Method: " << selectedPaymentMethod << endl;
    cout << "Transactions in category: " << count << endl;
    cout << "Total Transactions under " << selectedCat << ": " << total << endl;
    cout << "Percentage: " << fixed << setprecision(2) << percentage << "%" << endl;

    return count;
}

// Calculate the rating of bad reviews
int binarySearch::calculateBadReviewsCommonWords(reviews *reviewArray, int size) {
    int left = 0;
    int right = size - 1;
    int count = 0;
    
    // Find the first occurrence
    int first = -1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (reviewArray[mid].rating == 1) {
            first = mid;
            right = mid - 1; // Continue searching in the left half
        } else if (reviewArray[mid].rating < 1) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    // Find the last occurrence
    int last = -1;
    left = 0;
    right = size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (reviewArray[mid].rating == 1) {
            last = mid;
            left = mid + 1; // Continue searching in the right half
        } else if (reviewArray[mid].rating < 1) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    // Calculate count
    if (first != -1 && last != -1) {
        count = last - first + 1;
    }

    // Handle case where no matches are found
    if (count == 0) {
        cout << "No matching reviews found with rating 1." << endl;
        return 0;
    }
    return count; // Return the count of bad reviews
}

// // ===========================LINKED LIST==========================
// // Calculate the percentage of selected purchases with payment method chosen
Node<transactions> *binarySearch::findMiddle(Node<transactions>* start, Node<transactions>* end) {
    if (start == nullptr) {
        return nullptr;
    }
    if (start == end) {
        return start; // Base case: only one node
    }
    Node<transactions>* slow = start;
    Node<transactions>* fast = start;

    while (fast != end && fast->next != end) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

void binarySearch::calculatePurchasesPaymentMethodPercentage(LinkList<transactions> &transactionList, const string &selectedCat, const string &selectedPaymentMethod) {
    int count = 0;
    int total = 0;

    // Perform binary search to find the first matching transaction
    Node<transactions>* start = transactionList.getHead();
    Node<transactions>* end = nullptr;
    Node<transactions>* match = nullptr;

    while (start != end) {
        Node<transactions>* mid = findMiddle(start, end);

        if (mid->data.cat == selectedCat && mid->data.paymentMethod == selectedPaymentMethod) {
            match = mid; // Match found
            end = mid; // Continue searching in the left half
        } else if (mid->data.cat < selectedCat || (mid->data.cat == selectedCat && mid->data.paymentMethod < selectedPaymentMethod)) {
            start = mid->next; // Search in the right half
        } else {
            end = mid; // Search in the left half
        }
    }

    // If no match is found, print results and return
    if (match == nullptr) {
        cout << "No matching transactions found for Category: " << selectedCat
             << " and Payment Method: " << selectedPaymentMethod << endl;
        return;
    }

    // Count all matching transactions
    Node<transactions>* current = match;
    while (current != nullptr && current->data.cat == selectedCat && current->data.paymentMethod == selectedPaymentMethod) {
        count++;
        current = current->next;
    }

    // Count total transactions in the selected category
    current = transactionList.getHead();
    while (current != nullptr) {
        if (current->data.cat == selectedCat) {
            total++;
        }
        current = current->next;
    }

    // Calculate percentage
    double percentage = calculatePercentage(count, total);

    // Print results
    cout << "Category: " << selectedCat << endl;
    cout << "Payment Method: " << selectedPaymentMethod << endl;
    cout << "Transactions in category: " << count << endl;
    cout << "Total Transactions under " << selectedCat << ": " << total << endl;
    cout << "Percentage: " << fixed << setprecision(2) << percentage << "%" << endl;
}

// Calculate the rating of bad reviews
template <typename T>
Node<T>* findMiddle(Node<T>* start, Node<T>* end) {
    if (start == nullptr || start == end) {
        return nullptr;
    }
    Node<T>* slow = start;
    Node<T>* fast = start;
    while (fast != end && fast->next != end) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

Node<reviews>* binarySearchLinkedList(Node<reviews>* start, Node<reviews>* end, int rating) {
    if (start == nullptr || start == end) {
        return nullptr; // Base case: empty list or no match
    }

    // Find the middle node
    Node<reviews>* mid = findMiddle(start, end);

    // Compare the middle node's data with the target
    if (mid->data.rating == rating) {
        return mid; // Match found
    } else if (mid->data.rating < rating) {
        // Search in the right half
        return binarySearchLinkedList(mid->next, end, rating);
    } else {
        // Search in the left half
        return binarySearchLinkedList(start, mid, rating);
    }
}

int binarySearch::calculateBadReviewsCommonWords(LinkList<reviews>& reviewList, int rating) {
    int count = 0;

    Node<reviews>* current = reviewList.getHead();

    // Traverse the linked list
    while (current != nullptr) {
        if (current->data.rating == rating) {
            count++;
        }
        current = current->next;
    }

    return count;
}
