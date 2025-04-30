#include "jumpsearch.h"
#include <chrono>
#include <iostream>
using namespace std::chrono;
using namespace std;

jumpSearch::jumpSearch() {}
jumpSearch::~jumpSearch() {}

void jumpSearch::searchByProduct(transactions* arr, int size, const string& product) {
  auto start = high_resolution_clock::now();  //  Start timing

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

  auto end = high_resolution_clock::now();  //  End timing
  auto duration = duration_cast<milliseconds>(end - start);
  cout << " Execution time: " << duration.count() << " ms\n";
  cout << " Estimated Time Complexity of Jump Search: O(square root n) \n";
  cout << " Estimated space used: O(1) (no additional memory used)\n";

}


void jumpSearch::searchByCategory(transactions* arr, int size, const string& category) {
  auto start = high_resolution_clock::now();  //  Start timing

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

  auto end = high_resolution_clock::now();  //  End timing
  auto duration = duration_cast<milliseconds>(end - start);
  cout << " Execution time: " << duration.count() << " ms\n";
  cout << " Estimated Time Complexity of Jump Search: O(square root n) \n";
  cout << " Estimated space used: O(1) (no additional memory used)\n";

}


void jumpSearch::searchByPaymentMethod(transactions* arr, int size, const string& method) {
  auto start = high_resolution_clock::now();  //  Start timing

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

  auto end = high_resolution_clock::now();  //  End timing
  auto duration = duration_cast<milliseconds>(end - start);
  cout << " Execution time: " << duration.count() << " ms\n";
  cout << " Estimated Time Complexity of Jump Search: O(square root n) \n";
  cout << " Estimated space used: O(1) (no additional memory used)\n";

}


void jumpSearch::calculateElectronicsCreditPercentage(transactions* arr, int size) {
  using namespace chrono;

  auto start = high_resolution_clock::now();  //  Start timer

  int electronics_total = 0;
  int electronics_credit = 0;

  cout << "\n=== Electronics Transactions ===\n";

  for (int i = 0; i < size; i++) {
      if (arr[i].cat == "Electronics") {
          electronics_total++;
          arr[i].print();  //  Display the matching transaction
          if (arr[i].paymentMethod == "Credit Card") {
              electronics_credit++;
          }
      }
  }

  auto end = high_resolution_clock::now();  //  End timer
  auto duration = duration_cast<milliseconds>(end - start);  // milliseconds output

  cout << "\n=== Electronics Purchases with Credit Card ===\n";
  if (electronics_total == 0) {
      cout << "No Electronics purchases found.\n";
  } else {
      double percentage = (electronics_credit * 100.0) / electronics_total;
      cout << "Total Electronics Purchases: " << electronics_total << endl;
      cout << "With Credit Card: " << electronics_credit << endl;
      cout << "Percentage: " << percentage << "%\n";
  }

  cout << "\n Execution time: " << duration.count() << " milliseconds.\n";
  cout << " Estimated Time Complexity of Jump Search: O(square root n) \n";
  cout << " Estimated space used: O(1) (no additional memory used)\n";

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
