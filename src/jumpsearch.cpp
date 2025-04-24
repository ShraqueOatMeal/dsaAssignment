#include "jumpsearch.h"
#include "LinkList.h"
#include "transactions.h"
#include <iostream>
using namespace std;

// Filter by Product Name
jumpSearch::jumpSearch() {
  // Constructor implementation
}

jumpSearch::~jumpSearch() {
  // Destructor implementation
}

void jumpSearch::searchByProduct(LinkList<transactions> &list,
                                 const string &product) {
  Node<transactions> *current = list.getHead();
  bool found = false;

  cout << "Search results for Product: " << product << "\n";
  while (current) {
    if (current->data.prod == product) {
      current->data.print();
      found = true;
    }
    current = current->next;
  }
  if (!found) {
    cout << "No transactions found for product: " << product << endl;
  }
}

// Filter by Category
void jumpSearch::searchByCategory(LinkList<transactions> &list,
                                  const string &category) {
  Node<transactions> *current = list.getHead();
  bool found = false;

  cout << "Search results for Category: " << category << "\n";
  while (current) {
    if (current->data.cat == category) {
      current->data.print();
      found = true;
    }
    current = current->next;
  }
  if (!found) {
    cout << "No transactions found for category: " << category << endl;
  }
}

// Filter by Payment Method
void jumpSearch::searchByPaymentMethod(LinkList<transactions> &list,
                                       const string &paymentMethod) {
  Node<transactions> *current = list.getHead();
  bool found = false;

  cout << "Search results for Payment Method: " << paymentMethod << "\n";
  while (current) {
    if (current->data.paymentMethod == paymentMethod) {
      current->data.print();
      found = true;
    }
    current = current->next;
  }
  if (!found) {
    cout << "No transactions found for payment method: " << paymentMethod
         << endl;
  }
}

// Sample interactive menu to test the search
void jumpSearch::searchMenu(LinkList<transactions> &list) {
  int choice;
  string input;

  cout << "Search Transactions By:\n"
       << "1. Product Name\n"
       << "2. Category\n"
       << "3. Payment Method\n"
       << "Enter your choice: ";
  cin >> choice;
  cin.ignore(); // To handle leftover newline

  cout << "Enter search term: ";
  getline(cin, input);

  switch (choice) {
  case 1:
    searchByProduct(list, input);
    break;
  case 2:
    searchByCategory(list, input);
    break;
  case 3:
    searchByPaymentMethod(list, input);
    break;
  default:
    cout << "Invalid choice.\n";
    break;
  }
}
