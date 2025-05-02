#include "binarySearch.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
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
    
    insertionSortCategory(transArray, size);
    

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
void binarySearch::calculateBadReviewsCommonWords(reviews *reviewArray, int size) {
    insertionSortReview(reviewArray, size); // Sort reviews by rating

    const int MAX_WORDS = 100; // Maximum number of unique words
    string words[MAX_WORDS];   // Array to store unique words
    int frequencies[MAX_WORDS] = {0}; // Array to store word frequencies
    int uniqueWordCount = 0;   // Number of unique words found
    int badReviewsCount = 0;

    // List of stop words to exclude
    const string stopWords[] = {"in", "an", "the", "not", "and", "is", "of", "to", "a", "it"};
    const int stopWordsCount = sizeof(stopWords) / sizeof(stopWords[0]);

    cout << "\n=== Bad Reviews ===\n";

    // Process each review in the array
    for (int i = 0; i < size; i++) {
        if (reviewArray[i].rating == 1) { // Check if the review has a 1-star rating
            badReviewsCount++;
            cout << "Review " << badReviewsCount << ": " << reviewArray[i].review << endl;

            // Split the review into words
            stringstream ss(reviewArray[i].review);
            string word;
            while (ss >> word) {
                // Remove punctuation from the word
                word.erase(remove_if(word.begin(), word.end(), ::ispunct), word.end());
                transform(word.begin(), word.end(), word.begin(), ::tolower); // Convert to lowercase

                // Check if the word is a stop word
                bool isStopWord = false;
                for (int j = 0; j < stopWordsCount; j++) {
                    if (word == stopWords[j]) {
                        isStopWord = true;
                        break;
                    }
                }

                // Skip stop words
                if (isStopWord) {
                    continue;
                }

                // Check if the word is already in the array
                bool found = false;
                for (int j = 0; j < uniqueWordCount; j++) {
                    if (words[j] == word) {
                        frequencies[j]++;
                        found = true;
                        break;
                    }
                }

                // If the word is not found, add it to the array
                if (!found && uniqueWordCount < MAX_WORDS) {
                    words[uniqueWordCount] = word;
                    frequencies[uniqueWordCount] = 1;
                    uniqueWordCount++;
                }
            }
        }
    }

    cout << "\n=== Bad Reviews Summary ===\n";
    if (badReviewsCount == 0) {
        cout << "No bad reviews found.\n";
    } else {
        cout << "Total Bad Reviews: " << badReviewsCount << endl;

        // Sort the words by frequency in descending order
        for (int i = 0; i < uniqueWordCount - 1; i++) {
            for (int j = i + 1; j < uniqueWordCount; j++) {
                if (frequencies[i] < frequencies[j]) {
                    // Swap frequencies
                    int tempFreq = frequencies[i];
                    frequencies[i] = frequencies[j];
                    frequencies[j] = tempFreq;

                    // Swap corresponding words
                    string tempWord = words[i];
                    words[i] = words[j];
                    words[j] = tempWord;
                }
            }
        }

        // Display the top 10 most common words
        cout << "\nMost Common Words in 1-Star Reviews:\n";
        for (int i = 0; i < min(10, uniqueWordCount); i++) {
            cout << "\"" << words[i] << "\": " << frequencies[i] << " occurrences\n";
        }
    }
}

// ===========================LINKED LIST==========================
// Calculate the percentage of selected purchases with payment method chosen
void binarySearch::calculatedPurchasesPaymentMethodPercentage(LinkList<transactions> &transactionList, int size, 
    const string selectedCat, const string selectedPaymentMethod){
        cout << selectedCat << endl;
        cout << selectedPaymentMethod << endl;
        
        insertionSortCategory(&transactionList);

        

        
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
void binarySearch::calculateBadReviewsCommonWords(LinkList<reviews> &reviewList) {
    insertionSortReview(&reviewList);
    Node<reviews> *current = reviewList.getHead();
    const int MAX_WORDS = 100; // Maximum number of unique words
    string words[MAX_WORDS];   // Array to store unique words
    int frequencies[MAX_WORDS] = {0}; // Array to store word frequencies
    int uniqueWordCount = 0;   // Number of unique words found
    int badReviewsCount = 0;

    // List of stop words to exclude
    const string stopWords[] = {"in", "an", "the", "not", "and", "is", "of", "to", "a", "it"};
    const int stopWordsCount = sizeof(stopWords) / sizeof(stopWords[0]);

    cout << "\n=== Bad Reviews ===\n";

    // Traverse the linked list and process bad reviews
    while (current != nullptr) {
        if (current->data.rating == 1) { // Check if the review has a 1-star rating
            badReviewsCount++;
            cout << "Review " << badReviewsCount << ": " << current->data.review << endl;

            // Split the review into words
            stringstream ss(current->data.review);
            string word;
            while (ss >> word) {
                // Remove punctuation from the word
                word.erase(remove_if(word.begin(), word.end(), ::ispunct), word.end());
                transform(word.begin(), word.end(), word.begin(), ::tolower); // Convert to lowercase

                // Check if the word is a stop word
                bool isStopWord = false;
                for (int i = 0; i < stopWordsCount; i++) {
                    if (word == stopWords[i]) {
                        isStopWord = true;
                        break;
                    }
                }

                // Skip stop words
                if (isStopWord) {
                    continue;
                }

                // Check if the word is already in the array
                bool found = false;
                for (int i = 0; i < uniqueWordCount; i++) {
                    if (words[i] == word) {
                        frequencies[i]++;
                        found = true;
                        break;
                    }
                }

                // If the word is not found, add it to the array
                if (!found && uniqueWordCount < MAX_WORDS) {
                    words[uniqueWordCount] = word;
                    frequencies[uniqueWordCount] = 1;
                    uniqueWordCount++;
                }
            }
        }
        current = current->next;
    }

    cout << "\n=== Bad Reviews Summary ===\n";
    if (badReviewsCount == 0) {
        cout << "No bad reviews found.\n";
    } else {
        cout << "Total Bad Reviews: " << badReviewsCount << endl;

        // Sort the words by frequency in descending order
        for (int i = 0; i < uniqueWordCount - 1; i++) {
            for (int j = i + 1; j < uniqueWordCount; j++) {
                if (frequencies[i] < frequencies[j]) {
                    // Swap frequencies
                    int tempFreq = frequencies[i];
                    frequencies[i] = frequencies[j];
                    frequencies[j] = tempFreq;

                    // Swap corresponding words
                    string tempWord = words[i];
                    words[i] = words[j];
                    words[j] = tempWord;
                }
            }
        }

        // Display the top 10 most common words
        cout << "\nMost Common Words in 1-Star Reviews:\n";
        for (int i = 0; i < min(10, uniqueWordCount); i++) {
            cout << "\"" << words[i] << "\": " << frequencies[i] << " occurrences\n";
        }
    }
}