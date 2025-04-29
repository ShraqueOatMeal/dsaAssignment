#include "jumpsearch.h"
#include <iostream>
using namespace std;

jumpSearch::jumpSearch() {}
jumpSearch::~jumpSearch() {}

void jumpSearch::searchByProduct(transactions* arr, int size, const string& product) {
    bool found = false;
    cout << "\nSearch results for Product: " << product << "\n";
    for (int i = 0; i < size; i++) {
        if (arr[i].prod == product) {
            arr[i].print();
            found = true;
        }
    }
    if (!found) {
        cout << "No transactions found for product: " << product << endl;
    }
}

void jumpSearch::searchByCategory(transactions* arr, int size, const string& category) {
    bool found = false;
    cout << "\nSearch results for Category: " << category << "\n";
    for (int i = 0; i < size; i++) {
        if (arr[i].cat == category) {
            arr[i].print();
            found = true;
        }
    }
    if (!found) {
        cout << "No transactions found for category: " << category << endl;
    }
}

void jumpSearch::searchByPaymentMethod(transactions* arr, int size, const string& method) {
    bool found = false;
    cout << "\nSearch results for Payment Method: " << method << "\n";
    for (int i = 0; i < size; i++) {
        if (arr[i].paymentMethod == method) {
            arr[i].print();
            found = true;
        }
    }
    if (!found) {
        cout << "No transactions found for payment method: " << method << endl;
    }
}

void jumpSearch::calculateElectronicsCreditPercentage(transactions* arr, int size) {
  int electronics_total = 0;
  int electronics_credit = 0;

  cout << "\n=== Electronics Transactions ===\n";

  for (int i = 0; i < size; i++) {
      if (arr[i].cat == "Electronics") {
          electronics_total++;

          // Display the transaction
          arr[i].print();

          if (arr[i].paymentMethod == "Credit Card") {
              electronics_credit++;
          }
      }
  }

  cout << "\n=== Electronics Purchases with Credit Card ===\n";
  if (electronics_total == 0) {
      cout << "No Electronics purchases found.\n";
  } else {
      double percentage = (electronics_credit * 100.0) / electronics_total;
      cout << "Total Electronics Purchases: " << electronics_total << endl;
      cout << "With Credit Card: " << electronics_credit << endl;
      cout << "Percentage: " << percentage << "%\n";
  }
}


void jumpSearch::searchMenu(transactions* arr, int size) {
    int choice;
    string input;

    cout << "\n=== Search Sorted Transactions Menu ===\n";
    cout << "1. Search by Product Name\n";
    cout << "2. Search by Category\n";
    cout << "3. Search by Payment Method\n";
    cout << "4. Percentage of Electronics using Credit Card\n";
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore(); // clean newline

    if (choice == 4) {
        calculateElectronicsCreditPercentage(arr, size);
        return;
    }

    cout << "Enter search term: ";
    getline(cin, input);

    switch (choice) {
        case 1: searchByProduct(arr, size, input); break;
        case 2: searchByCategory(arr, size, input); break;
        case 3: searchByPaymentMethod(arr, size, input); break;
        default: cout << "Invalid choice.\n"; break;
    }
}
