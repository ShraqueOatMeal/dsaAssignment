#include "binarySearch.hpp"
#include <iostream>
using namespace std;

// Insertion Sort for category in transactions array (question 2)
void insertionSortCategory(transactions *transArray, int size){
    for (int i = 1; i < size; i++) {
        transactions key = transArray[i];
        int j = i - 1;
  
      // Move elements of transArray[0..i-1], that are greater than key,
      // to one position ahead of their current position
        while (j >= 0 && transArray[j].cat > key.cat) {
            transArray[j + 1] = transArray[j];
            j = j - 1;
        }
        transArray[j + 1] = key; // Place the key in its correct position
    }
}
  
// Insertion Sort for reviews in reviews array (question 3)
void insertionSortReview(reviews *reviewArray, int size) {
    for (int i = 1; i < size; i++) {
        reviews key = reviewArray[i];
        int j = i - 1;
  
      // Move elements of reviewArray[0..i-1], that are greater than key,
      // to one position ahead of their current position
      while (j >= 0 && reviewArray[j].rating > key.rating) {
            reviewArray[j + 1] = reviewArray[j];
            j = j - 1;
        }
        reviewArray[j + 1] = key; // Place the key in its correct position
    }
}

Node<transactions> *insertIntoSortedList(Node<transactions> *sorted, Node<transactions> *newNode) {
    if (sorted == nullptr || newNode->data.cat > sorted->data.cat) {
      // Insert at the beginning of the sorted list
      newNode->next = sorted;
      return newNode;
    }
  
    Node<transactions> *current = sorted;
    while (current->next != nullptr &&
           current->next->data.cat > newNode->data.cat) {
      current = current->next;
    }
  
    // Insert newNode after current
    newNode->next = current->next;
    current->next = newNode;
  
    return sorted;
  }

Node<reviews> *insertIntoSortedList(Node<reviews> *sorted, Node<reviews> *newNode) {
    if (sorted == nullptr || newNode->data.rating > sorted->data.rating) {
        // Insert at the beginning of the sorted list
        newNode->next = sorted;
        return newNode;
    }
  
    Node<reviews> *current = sorted;
    while (current->next != nullptr && current->next->data.rating > newNode->data.rating) {
        current = current->next;
    }
  
    // Insert newNode after current
    newNode->next = current->next;
    current->next = newNode;
  
    return sorted;
}
  
// Insertion Sort for category in transactions linked list (question 2)
void insertionSortCategory(LinkList<transactions> *transactionList) {
    if (transactionList->getHead() == nullptr || transactionList->getHead()->next == nullptr) {// List is empty or has only one element, no sorting needed
      return;
    }
  
    Node<transactions> *sorted = nullptr; // Start with an empty sorted list
    Node<transactions> *current =
        transactionList->getHead(); // Current node to be inserted
  
    while (current != nullptr) {
        Node<transactions> *next = current->next; // Save the next node
        sorted = insertIntoSortedList(sorted, current); // Insert current into the sorted list
        current = next;       // Move to the next node
    }
  
    // Update the head of the original list to point to the sorted list
    transactionList->setHead(sorted);
}
  
// Insertion Sort for reviews in reviews linked list (question 3)
void insertionSortReview(LinkList<reviews> *reviewsList) {
    if (reviewsList->getHead() == nullptr ||
        reviewsList->getHead()->next == nullptr) {
        // List is empty or has only one element, no sorting needed
        return;
    }
  
    Node<reviews> *sorted = nullptr; // Start with an empty sorted list
    Node<reviews> *current =
        reviewsList->getHead(); // Current node to be inserted
  
    while (current != nullptr) {
        Node<reviews> *next = current->next; // Save the next node
        sorted = insertIntoSortedList(
            sorted, current); // Insert current into the sorted list
        current = next;       // Move to the next node
    }
  
    // Update the head of the original list to point to the sorted list
    reviewsList->setHead(sorted);
}
  

// ===========================ARRAY==========================
// Calculate the percentage of selected purchases with payment method chosen
void binarySearch::calculatedPurchasesPaymentMethodPercentage(transactions *transArray, int size, 
    const string selectedCat, const string selectedPaymentMethod){
    cout << "Hello" << endl;
    insertionSortCategory(transArray, size);
    cout << "Hello" << endl;

    int categoryCount = 0;
    int categoryPaymentCount = 0;

    for (int i = 0; i < size; i++) {
        if (transArray[i].cat == selectedCat) {
            categoryCount++;
            if (transArray[i].paymentMethod == selectedPaymentMethod) {
                categoryPaymentCount++;
            }
        }
    }

    if (categoryCount == 0) {
        cout << "No purchases found for the selected category." << endl;
        return;
    }
        
    double percentage = (static_cast<double>(categoryPaymentCount) / categoryCount) * 100.0;

    cout << "Total purchases in " << selectedCat << ": " << categoryCount << endl;
    cout << "Total purchases in " << selectedCat << " with payment method " << selectedPaymentMethod << ": " << categoryPaymentCount << endl;
    cout << "Percentage of purchases in " << selectedCat << " with payment method " << selectedPaymentMethod << ": " << percentage << "%" << endl;
}

// Calculate the rating of bad reviews
void binarySearch::calculateBadReviewsCommonSentences(reviews *reviewArray, int size) {
    cout << "Hello" << endl;
    insertionSortReview(reviewArray, size);
    cout << "Hello" << endl;

    const int MAX_REVIEWS = 100; 
    string ReviewNode[MAX_REVIEWS]; // Array to store unique review sentences
    int frequencies[MAX_REVIEWS] = {0}; // Array to store frequencies of each review
    int uniqueCount = 0; // Number of unique ReviewNode found
    int badReviewsCount = 0;

    cout << "\n=== Bad Reviews ===\n";

    for (int i = 0; i < size; i++) {
        if (reviewArray[i].rating == 1) { // Check if the review has a 1-star rating
            badReviewsCount++;
            reviewArray[i].print(); // Display the matching review

            bool found = false;
            for (int j = 0; j < uniqueCount; j++) {
                if (ReviewNode[j] == reviewArray[i].review) {
                    frequencies[j]++;
                    found = true;
                    break;
                }
            }

            if (!found && uniqueCount < MAX_REVIEWS) {
                ReviewNode[uniqueCount] = reviewArray[i].review;
                frequencies[uniqueCount] = 1;
                uniqueCount++;
            }
        }
    }

    cout << "\n=== Bad Reviews Summary ===\n";
    if (badReviewsCount == 0) {
        cout << "No bad ReviewNode found.\n";
    } else {
        cout << "Total Bad Reviews: " << badReviewsCount << endl;

        // Display the most common review sentences
        cout << "\nMost Common 1-Star Review Sentences:\n";
        for (int i = 0; i < uniqueCount; i++) {
            cout << "\"" << ReviewNode[i] << "\": " << frequencies[i] << " occurrences\n";
        }
    }
}

// ===========================LINKED LIST==========================
// Calculate the percentage of selected purchases with payment method chosen
void binarySearch::calculatedPurchasesPaymentMethodPercentage(LinkList<transactions> &transactionList, int size, 
    const string selectedCat, const string selectedPaymentMethod){
        cout << selectedCat << endl;
        cout << selectedPaymentMethod << endl;
        cout << "Hello" << endl;
        insertionSortCategory(&transactionList);

        cout << "Hello" << endl;

        
        Node<transactions> *current = transactionList.getHead();
        int categoryCount = 0;
        int categoryPaymentCount = 0;

        while (current != nullptr) {
            cout << current->data.cat << endl;
            cout << current->data.paymentMethod << endl;
            if (current->data.cat == selectedCat) {
                categoryCount++;
                if (current->data.paymentMethod == selectedPaymentMethod) {
                    categoryPaymentCount++;
                }
            }
            current = current->next;
        }

        if (categoryCount == 0) {
            cout << "No purchases found for the selected category." << endl;
            return;
        }
        double percentage = (static_cast<double>(categoryPaymentCount) / categoryCount) * 100.0;

        cout<< "hey" << endl;
        cout << "Total purchases in " << selectedCat << ": " << categoryCount << endl;
        cout << "Total purchases in " << selectedCat << " with payment method " << selectedPaymentMethod << ": " << categoryPaymentCount << endl;
        cout << "Percentage of purchases in " << selectedCat << " with payment method " << selectedPaymentMethod << ": " << percentage << "%" << endl;
        
    }

// Calculate the percentage of selected purchases with payment method chosen
void binarySearch::calculateBadReviewsCommonSentences(LinkList<reviews> &reviewList) {
    // Sort the reviews list using insertion sort based on the rating
    cout << "Hello" << endl;
    insertionSortReview(&reviewList);
    cout << "Hello" << endl;

    Node<reviews> *current = reviewList.getHead();
    int badReviewCount = 0;

    cout << "\n=== Bad Reviews ===\n";

    // Traverse the linked list and process bad reviews
    while (current != nullptr) {
        if (current->data.rating == 1) {
            cout << "Review " << (badReviewCount + 1) << ": " << current->data.review << endl;
            badReviewCount++;
        }
        current = current->next;
    }

    if (badReviewCount == 0) {
        cout << "No bad reviews found." << endl;
        return;
    }

    cout << "\nTotal bad reviews: " << badReviewCount << endl;

    cout << "Bad Reviews:" << endl;
    for (int i = 0; i < badReviewCount; i++) {
        cout << "Review " << (i + 1) << ": " << current->data.review << endl;
    }
    cout << "Total bad reviews: " << badReviewCount << endl;
    cout << "Common sentences in bad reviews:" << endl;
    for (int i = 0; i < badReviewCount; i++) {
        cout << current->data.review << endl;
    }
    cout << "Total common sentences: " << badReviewCount << endl;
}