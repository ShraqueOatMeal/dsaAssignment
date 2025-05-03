#include "jumpsearch.h"
#include <chrono>
#include <cmath>
#include <iomanip>
#include <iostream>

void jumpSearch::searchMenu(transactions *arr, int size, int catChoice,
                            int paymentChoice) {
  string selectedCat;
  string selectedPaymentMethod;

  // Category selection
  switch (catChoice) {
  case 1:
    selectedCat = "Automotive";
    break;
  case 2:
    selectedCat = "Books";
    break;
  case 3:
    selectedCat = "Groceries";
    break;
  case 4:
    selectedCat = "Sports";
    break;
  case 5:
    selectedCat = "Toys";
    break;
  case 6:
    selectedCat = "Beauty";
    break;
  case 7:
    selectedCat = "Furniture";
    break;
  case 8:
    selectedCat = "Electronics";
    break;
  case 9:
    selectedCat = "Fashion";
    break;
  case 10:
    selectedCat = "Home Appliances";
    break;
  default:
    cout << "Invalid category.\n";
    return;
  }

  // Payment method selection
  switch (paymentChoice) {
  case 1:
    selectedPaymentMethod = "Bank Transfer";
    break;
  case 2:
    selectedPaymentMethod = "PayPal";
    break;
  case 3:
    selectedPaymentMethod = "Debit Card";
    break;
  case 4:
    selectedPaymentMethod = "Cash on Delivery";
    break;
  case 5:
    selectedPaymentMethod = "Credit Card";
    break;
  default:
    cout << "Invalid payment method.\n";
    return;
  }

  cout << "\nJump Search (Array) for Category: " << selectedCat
       << ", Payment Method: " << selectedPaymentMethod << "\n";

  auto start = chrono::high_resolution_clock::now();
  // Jump Search for the first appearance of selectedCat
  int step = sqrt(size);
  int prev = 0;
  while (prev < size && arr[min(step, size) - 1].cat < selectedCat) {
    prev = step;
    step += sqrt(size);
    if (prev >= size)
      break;
  }

  // Find exact starting index within block
  int startIdx = -1;
  for (int i = prev; i < min(step, size); i++) {
    if (arr[i].cat == selectedCat) {
      startIdx = i;
      break;
    }
  }

  // If not found, category doesn't exist
  if (startIdx == -1) {
    cout << "No transactions found for category \"" << selectedCat << "\".\n";
    return;
  }

  // Expand backward
  int first = startIdx;
  while (first > 0 && arr[first - 1].cat == selectedCat) {
    first--;
  }

  // Expand forward
  int last = startIdx;
  while (last + 1 < size && arr[last + 1].cat == selectedCat) {
    last++;
  }

  // Count and print matches in full category range
  int categoryCount = last - first + 1;
  int matchCount = 0;
  for (int i = first; i <= last; i++) {
    if (arr[i].paymentMethod == selectedPaymentMethod) {
      arr[i].print();
      matchCount++;
    }
  }

  auto end = chrono::high_resolution_clock::now();
  chrono::duration<double, milli> duration = end - start;

  if (categoryCount == 0) {
    cout << "No transactions found for category \"" << selectedCat << "\".\n";
  } else {
    double percentage = (matchCount * 100.0) / categoryCount;
    cout << "\nTotal in category \"" << selectedCat << "\": " << categoryCount
         << endl;
    cout << "Matching with \"" << selectedPaymentMethod << "\": " << matchCount
         << endl;
    cout << "Percentage: " << fixed << setprecision(2) << percentage << "%\n";
  }

  cout << "Jump Search (Array) completed.\n";
  cout << "Execution time: " << duration.count() << " ms\n";
  cout << "Estimated Time Complexity: O(square root n)\n";
  cout << "Estimated Space Complexity: O(1)\n";
}

void jumpSearch::searchMenu(LinkList<transactions> &list, int catChoice,
                            int paymentChoice) {
  string selectedCat;
  string selectedPaymentMethod;

  switch (catChoice) {
  case 1:
    selectedCat = "Automotive";
    break;
  case 2:
    selectedCat = "Books";
    break;
  case 3:
    selectedCat = "Groceries";
    break;
  case 4:
    selectedCat = "Sports";
    break;
  case 5:
    selectedCat = "Toys";
    break;
  case 6:
    selectedCat = "Beauty";
    break;
  case 7:
    selectedCat = "Furniture";
    break;
  case 8:
    selectedCat = "Electronics";
    break;
  case 9:
    selectedCat = "Fashion";
    break;
  case 10:
    selectedCat = "Home Appliances";
    break;
  default:
    cout << "Invalid category.\n";
    return;
  }

  switch (paymentChoice) {
  case 1:
    selectedPaymentMethod = "Bank Transfer";
    break;
  case 2:
    selectedPaymentMethod = "PayPal";
    break;
  case 3:
    selectedPaymentMethod = "Debit Card";
    break;
  case 4:
    selectedPaymentMethod = "Cash on Delivery";
    break;
  case 5:
    selectedPaymentMethod = "Credit Card";
    break;
  default:
    cout << "Invalid payment method.\n";
    return;
  }

  cout << "\nJump Search (Linked List) Category: " << selectedCat
       << ", Payment Method: " << selectedPaymentMethod << "\n";

  auto start = chrono::high_resolution_clock::now();

  // Count total size
  int size = 0;
  Node<transactions> *node = list.getHead();
  while (node != nullptr) {
    size++;
    node = node->next;
  }

  int stepSize = sqrt(size);
  int index = 0;
  Node<transactions> *prev = nullptr;
  Node<transactions> *current = list.getHead();

  // Jump steps to find category block
  while (current != nullptr && current->next != nullptr &&
         current->data.cat < selectedCat) {
    prev = current;
    for (int i = 0; i < stepSize && current->next != nullptr; i++) {
      current = current->next;
      index++;
    }
  }

  // Linear scan from prev to current to find category matches
  Node<transactions> *startScan = (prev != nullptr) ? prev : list.getHead();
  int categoryCount = 0;
  int matchCount = 0;

  while (startScan != nullptr && startScan->data.cat <= selectedCat) {
    if (startScan->data.cat == selectedCat) {
      categoryCount++;
      if (startScan->data.paymentMethod == selectedPaymentMethod) {
        startScan->data.print();
        matchCount++;
      }
    }
    startScan = startScan->next;
  }

  auto end = chrono::high_resolution_clock::now();
  chrono::duration<double, milli> duration = end - start;

  if (matchCount == 0) {
    cout << "No matching transactions found.\n";
  } else {
    double percentage =
        (categoryCount > 0) ? (matchCount * 100.0 / categoryCount) : 0;
    cout << "\nTotal in category \"" << selectedCat << "\": " << categoryCount
         << endl;
    cout << "Matching with \"" << selectedPaymentMethod << "\": " << matchCount
         << endl;
    cout << "Percentage: " << fixed << setprecision(2) << percentage << "%\n";
  }

  cout << "Jump Search (Linked List) completed.\n";
  cout << "Execution time: " << duration.count() << " ms\n";
  cout << "Estimated Time Complexity: O(square root n)\n";
  cout << "Estimated Space Complexity: O(1)\n";
}
