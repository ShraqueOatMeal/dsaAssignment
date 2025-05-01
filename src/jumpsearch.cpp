#include "jumpsearch.h"
#include <iostream>     
#include <iomanip>      
#include <chrono>  

void jumpSearch::searchMenu(transactions* arr, int size, int catChoice, int paymentChoice) {
    string selectedCat;
    string selectedPaymentMethod;

    switch (catChoice) {
        case 1: selectedCat = "Automotive"; break;
        case 2: selectedCat = "Books"; break;
        case 3: selectedCat = "Groceries"; break;
        case 4: selectedCat = "Sports"; break;
        case 5: selectedCat = "Toys"; break;
        case 6: selectedCat = "Beauty"; break;
        case 7: selectedCat = "Furniture"; break;
        case 8: selectedCat = "Electronics"; break;
        case 9: selectedCat = "Fashion"; break;
        case 10: selectedCat = "Home Appliances"; break;
        default: cout << "Invalid category.\n"; return;
    }

    switch (paymentChoice) {
        case 1: selectedPaymentMethod = "Bank Transfer"; break;
        case 2: selectedPaymentMethod = "PayPal"; break;
        case 3: selectedPaymentMethod = "Debit Card"; break;
        case 4: selectedPaymentMethod = "Cash on Delivery"; break;
        case 5: selectedPaymentMethod = "Credit Card"; break;
        default: cout << "Invalid payment method.\n"; return;
    }

    cout << "\nJump Search (Array) Category: " << selectedCat << ", Payment Method: " << selectedPaymentMethod << "\n";

    auto start = chrono::high_resolution_clock::now();

    int categoryCount = 0;
    int matchCount = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i].cat == selectedCat) {
            categoryCount++;
            if (arr[i].paymentMethod == selectedPaymentMethod) {
                arr[i].print();
                matchCount++;
            }
        }
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = end - start;

    if (matchCount == 0) {
        cout << "No matching transactions found.\n";
    } else {
        double percentage = (categoryCount > 0) ? (matchCount * 100.0 / categoryCount) : 0;
        cout << "\nTotal in category \"" << selectedCat << "\": " << categoryCount << endl;
        cout << "Matching with \"" << selectedPaymentMethod << "\": " << matchCount << endl;
        cout << "Percentage: " << fixed << setprecision(2) << percentage << "%\n";
    }

    cout << "Jump Search (Array) completed.\n";
    cout << "Execution time: " << duration.count() << " ms\n ";
    cout << "Estimated Time Complexity: O(n)\n";
    cout << "Estimated Space Complexity: O(1)\n";
}

void jumpSearch::searchMenu(LinkList<transactions>& list, int catChoice, int paymentChoice) {
    string selectedCat;
    string selectedPaymentMethod;

    switch (catChoice) {
        case 1: selectedCat = "Automotive"; break;
        case 2: selectedCat = "Books"; break;
        case 3: selectedCat = "Groceries"; break;
        case 4: selectedCat = "Sports"; break;
        case 5: selectedCat = "Toys"; break;
        case 6: selectedCat = "Beauty"; break;
        case 7: selectedCat = "Furniture"; break;
        case 8: selectedCat = "Electronics"; break;
        case 9: selectedCat = "Fashion"; break;
        case 10: selectedCat = "Home Appliances"; break;
        default: cout << "Invalid category.\n"; return;
    }

    switch (paymentChoice) {
        case 1: selectedPaymentMethod = "Bank Transfer"; break;
        case 2: selectedPaymentMethod = "PayPal"; break;
        case 3: selectedPaymentMethod = "Debit Card"; break;
        case 4: selectedPaymentMethod = "Cash on Delivery"; break;
        case 5: selectedPaymentMethod = "Credit Card"; break;
        default: cout << "Invalid payment method.\n"; return;
    }

    cout << "\nJump Search (Linked List) Category: " << selectedCat
         << ", Payment Method: " << selectedPaymentMethod << "\n";

    auto start = chrono::high_resolution_clock::now();

    int categoryCount = 0;
    int matchCount = 0;

    Node<transactions>* current = list.getHead();
    while (current != nullptr) {
        if (current->data.cat == selectedCat) {
            categoryCount++;
            if (current->data.paymentMethod == selectedPaymentMethod) {
                current->data.print();
                matchCount++;
            }
        }
        current = current->next;
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = end - start;

    if (matchCount == 0) {
        cout << "No matching transactions found.\n";
    } else {
        double percentage = (categoryCount > 0) ? (matchCount * 100.0 / categoryCount) : 0;
        cout << "\nTotal in category \"" << selectedCat << "\": " << categoryCount << endl;
        cout << "Matching with \"" << selectedPaymentMethod << "\": " << matchCount << endl;
        cout << "Percentage: " << fixed << setprecision(2) << percentage << "%\n";
    }

    cout << "Jump Search (Linked List) completed.\n";
    cout << "Execution time: " << duration.count() << " ms\n";
    cout << "Estimated Time Complexity: O(n)\n";
    cout << "Estimated Space Complexity: O(1)\n";
}

