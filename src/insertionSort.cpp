#include "../include/insertionSort.hpp"
#include "../include/LinkList.h"
#include "../include/transactions.h"
#include "../include/reviews.h"
#include <string>
#include <sstream>
using namespace std;

// Helper function: Convert dd/mm/yyyy to yyyymmdd
int parseDate(const string &date) {
    int day, month, year;
    char delimiter;
    stringstream ss(date);
    ss >> day >> delimiter >> month >> delimiter >> year;
    return year * 10000 + month * 100 + day;
}

bool compareDates(const string &date1, const string &date2){
    int parseDate1 = parseDate(date1);
    int parseDate2 = parseDate(date2);

    return parseDate1 < parseDate2;
}

// Insertion Sort for array
void insertionSort::insertionsort(transactions *transArray, int size){
    for (int i = 1; i < size; i++){
        transactions key = transArray[i];
        int j = i - 1;

        // Move elements of transArray[0..i-1], that are greater than key,
        // to one position ahead of their current position
        while (j >= 0 && compareDates(transArray[j].date, key.date)){
            transArray[j + 1] = transArray[j];
            j = j - 1;
        }
        transArray[j + 1] = key; // Place the key in its correct position
    }
}

// Insertion Sort for linked list
void insertionSort::insertionsort(LinkList<transactions> *transactionList) {
    if (transactionList->getHead() == nullptr || transactionList->getHead()->next == nullptr) {
        // List is empty or has only one element, no sorting needed
        return;
    }

    Node<transactions> *sorted = nullptr; // Start with an empty sorted list
    Node<transactions> *current = transactionList->getHead(); // Current node to be inserted

    while (current != nullptr) {
        Node<transactions> *next = current->next; // Save the next node
        sorted = insertIntoSortedList(sorted, current); // Insert current into the sorted list
        current = next; // Move to the next node
    }

    // Update the head of the original list to point to the sorted list
    transactionList->setHead(sorted);
}

// Helper function to insert a node into a sorted singly linked list
Node<transactions>* insertionSort::insertIntoSortedList(Node<transactions> *sorted, Node<transactions> *newNode) {
    if (sorted == nullptr || compareDates(newNode->data.date, sorted->data.date)) {
        // Insert at the beginning of the sorted list
        newNode->next = sorted;
        return newNode;
    }

    Node<transactions> *current = sorted;
    while (current->next != nullptr && compareDates(current->next->data.date, newNode->data.date)) {
        current = current->next;
    }

    // Insert newNode after current
    newNode->next = current->next;
    current->next = newNode;

    return sorted;
}