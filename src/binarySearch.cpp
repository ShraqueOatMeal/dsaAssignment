#include "binarySearch.hpp"
#include "insertionSort.cpp"
#include <iostream>
using namespace std;

// ============================ARRAY==========================

// Calculate the percentage of Electronics purchases made with a Credit Card
void binarySearch::calculateElectronicsCreditPercentage(transactions *arr, int size) {
    insertionSort::insertionSortCategory(arr, size); // Sort the array by category
    int electronics_total = 0;
    int electronics_credit = 0;

    cout << "\n=== Electronics Transactions ===\n";

    for (int i = 0; i < size; i++) {
        if (arr[i].cat == "Electronics") {
            electronics_total++;
            arr[i].print();
            if (arr[i].paymentMethod == "Credit Card") {
                electronics_credit++;
            }
        }
    }

    cout << "\n=== Electronics Purchases with Credit Card ===\n";
    if (electronics_total == 0) {
        cout << "No Electronics purchases found. (0%)\n";
    } else {
        double percentage = (electronics_credit * 100.0) / electronics_total;
        cout << "Total Electronics Purchases: " << electronics_total << endl;
        cout << "With Credit Card: " << electronics_credit << endl;
        cout << "Percentage: " << percentage << "%\n";
    }
}

// Calculate the most common 1-star reviews
void binarySearch::calculateBadReviewsCommonSentences(reviews *arr, int size) {
    const int MAX_REVIEWS = 100; 
    string reviews[MAX_REVIEWS]; // Array to store unique review sentences
    int frequencies[MAX_REVIEWS] = {0}; // Array to store frequencies of each review
    int uniqueCount = 0; // Number of unique reviews found
    int badReviewsCount = 0;

    cout << "\n=== Bad Reviews ===\n";

    for (int i = 0; i < size; i++) {
        if (arr[i].rating == 1) { // Check if the review has a 1-star rating
            badReviewsCount++;
            arr[i].print(); // Display the matching review

            bool found = false;
            for (int j = 0; j < uniqueCount; j++) {
                if (reviews[j] == arr[i].reviewText) {
                    frequencies[j]++;
                    found = true;
                    break;
                }
            }

            if (!found && uniqueCount < MAX_REVIEWS) {
                reviews[uniqueCount] = arr[i].reviewText;
                frequencies[uniqueCount] = 1;
                uniqueCount++;
            }
        }
    }

    cout << "\n=== Bad Reviews Summary ===\n";
    if (badReviewsCount == 0) {
        cout << "No bad reviews found.\n";
    } else {
        cout << "Total Bad Reviews: " << badReviewsCount << endl;

        // Display the most common review sentences
        cout << "\nMost Common 1-Star Review Sentences:\n";
        for (int i = 0; i < uniqueCount; i++) {
            cout << "\"" << reviews[i] << "\": " << frequencies[i] << " occurrences\n";
        }
    }
}

// ============================LINKED LIST==========================

// Calculate the percentage of Electronics purchases made with a Credit Card
void binarySearch::calculateElectronicsCreditPercentage(LinkList<transactions> &arr) {
    insertionSort::insertionSortCategory(arr); // Sort the linked list by category
    Node<transactions> *current = arr.getHead();
    int electronics_total = 0;
    int electronics_credit = 0;

    cout << "\n=== Electronics Transactions ===\n";

    while (current != nullptr) {
        if (current->data.cat == "Electronics") {
            electronics_total++;
            current->data.print(); // Display the matching transaction
            if (current->data.paymentMethod == "Credit Card") {
                electronics_credit++;
            }
        }
        current = current->next;
    }

    cout << "\n=== Electronics Purchases with Credit Card ===\n";
    if (electronics_total == 0) {
        cout << "No Electronics purchases found. (0%)\n";
    } else {
        double percentage = (electronics_credit * 100.0) / electronics_total;
        cout << "Total Electronics Purchases: " << electronics_total << endl;
        cout << "With Credit Card: " << electronics_credit << endl;
        cout << "Percentage: " << percentage << "%\n";
    }
}

// Calculate the most common 1-star reviews in a linked list
void binarySearch::calculateBadReviewsCommonSentences(LinkList<reviews> &arr) {
    Node<transactions> *current = arr.getHead();
    ReviewNode *reviewHead = nullptr;

    cout << "\n=== Bad Reviews ===\n";

    while (current != nullptr) {
        if (current->data.rating == 1) {
            current->data.print();

            // Check if the review is already in the linked list
            ReviewNode *reviewCurrent = reviewHead;
            bool found = false;
            while (reviewCurrent != nullptr) {
                if (reviewCurrent->reviewText == current->data.reviewText) {
                    reviewCurrent->frequency++;
                    found = true;
                    break;
                }
                reviewCurrent = reviewCurrent->next;
            }

            // If the review is not found, add it to the linked list
            if (!found) {
                ReviewNode *newNode = new ReviewNode(current->data.reviewText);
                newNode->next = reviewHead;
                reviewHead = newNode;
            }
        }
        current = current->next;
    }

    cout << "\n=== Bad Reviews Summary ===\n";
    if (!reviewHead) {
        cout << "No bad reviews found.\n";
    } else {
        int totalBadReviews = 0;
        ReviewNode *temp = reviewHead;
        while (temp != nullptr) {
            totalBadReviews += temp->frequency;
            cout << "\"" << temp->reviewText << "\": " << temp->frequency << " occurrences\n";
            temp = temp->next;
        }
        cout << "Total Bad Reviews: " << totalBadReviews << endl;
    }

    // Free the linked list memory
    while (reviewHead != nullptr) {
        ReviewNode *temp = reviewHead;
        reviewHead = reviewHead->next;
        delete temp;
    }
}

