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

    // Perform binary search to find the first occurrence
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (reviewArray[mid].rating == 1) {
            // Count all occurrences of the matching element
            int temp = mid;
            while (temp >= 0 && reviewArray[temp].rating == 1) {
                count++;
                temp--;
            }
            temp = mid + 1;
            while (temp < size && reviewArray[temp].rating == 1) {
                count++;
                temp++;
            }
            break;
        } else if (reviewArray[mid].rating < 1) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return count; // Return the count of bad reviews
}

// // ===========================LINKED LIST==========================
// // Calculate the percentage of selected purchases with payment method chosen
Node<transactions> *findMiddle(Node<transactions> *start, Node<transactions> *end) {
    if (start == nullptr || start == end) {
        return nullptr;
    }
    Node<transactions> *slow = start;
    Node<transactions> *fast = start;
    while (fast != end && fast->next != end) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

Node<transactions>* binarySearchLinkedList(Node<transactions>* start, Node<transactions>* end, const string& selectedCat, const string& selectedPaymentMethod) {
    if (start == nullptr || start == end) {
        return nullptr; // Base case: empty list or no match
    }

    // Find the middle node
    Node<transactions>* mid = findMiddle(start, end);

    // Compare the middle node's data with the target
    if (mid->data.cat == selectedCat && mid->data.paymentMethod == selectedPaymentMethod) {
        return mid; // Match found
    } else if (mid->data.cat < selectedCat || (mid->data.cat == selectedCat && mid->data.paymentMethod < selectedPaymentMethod)) {
        // Search in the right half
        return binarySearchLinkedList(mid->next, end, selectedCat, selectedPaymentMethod);
    } else {
        // Search in the left half
        return binarySearchLinkedList(start, mid, selectedCat, selectedPaymentMethod);
    }
}

void binarySearch::calculatedPurchasesPaymentMethodPercentage(LinkList<transactions>& transactionList, const string& selectedCat, const string& selectedPaymentMethod) {
    int count = 0;
    int total = 0;

    Node<transactions>* current = transactionList.getHead();

    // Traverse the linked list
    while (current != nullptr) {
        if (current->data.cat == selectedCat) {
            total++; // Increment total count of transactions in the category
            if (current->data.paymentMethod == selectedPaymentMethod) {
                count++; // Increment count of matching transactions
            }
        }
        current = current->next; // Move to the next node
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
Node<reviews>* findMiddle(Node<reviews>* start, Node<reviews>* end) {
    if (start == nullptr || start == end) {
        return nullptr;
    }
    Node<reviews>* slow = start;
    Node<reviews>* fast = start;
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