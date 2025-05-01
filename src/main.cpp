#include "JoinedData.h"
#include "LinkList.h"
#include "WordFrequency.h"
#include "bubblesort.h"
#include "insertionSort.hpp"
// #include "jumpsearch.h"
// #include "oneStarReview.h"
#include "radixSort.h"
#include "reviews.h"
#include "transactions.h"
#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

// Declaration

void loadTransaction(ifstream &transactionFile,
                     LinkList<transactions> &transactionList);
void loadTransaction(ifstream &transactionFile, transactions *transArray,
                     int size);
void displayTransactionArr(transactions *transArray, int size);

void loadReview(ifstream &reviewFile, LinkList<reviews> &reviewList);
void loadReview(ifstream &reviewFile, reviews *reviewArray, int size);
void displayReviewsArray(reviews *reviewArray, int size);

void linearSearch(int catChoice, int paymentChoice, int size,
                  transactions *transArray);

void linearSearch(int catChoice, int paymentChoice, int size,
                  LinkList<transactions> &transactionList);

int rowsNum(ifstream &file);

void calculatePercentage(LinkList<transactions> &transactionList, int size,
                         const string &category, const string &paymentMethod);

void calculatePercentage(transactions *transArray, int size,
                         const string &category, const string &paymentMethod);

void cleanData(ifstream &inputFile, const string &outputFilename);

// Use to trim the white spaces, tabs, and new lines from the string
string trim(const string &str) {
  size_t first = str.find_first_not_of(" \n\r\t");
  if (string::npos == first) {
    return str;
  }
  size_t last = str.find_last_not_of(" \n\r\t");
  return str.substr(first, (last - first + 1));
}

// Use to define the payment method
enum paymentMeth { BankTransfer = 1, PayPal, DebitCard, COD, CreditCard };

// Use to define the category
enum category {
  Automotive = 1,
  Books,
  Groceries,
  Sports,
  Toys,
  Beauty,
  Furniture,
  Electronics,
  Fashion,
  HomeAppliances
};

// Menu
void displayMainMenu();
void sortByDateMenu(int choice, LinkList<transactions> &transactionList,
                    LinkList<reviews> &reviewList, transactions *transArray,
                    reviews *reviewArray, int transCount, int reviewCount);
void filterByCategoryAndPayment(int choice,
                                LinkList<transactions> &transactionList,
                                transactions *transArray, int transCount);
void checkNegativeReviews(int choice, LinkList<reviews> &reviewList,
                          reviews *reviewArray, int reviewCount);
// System will run in here
int main(int argc, char *argv[]) {
  // Data cleaning (unchanged)
  ifstream uncleanedTransactionFile("../data/transactions.csv");
  ifstream uncleanedReviewFile("../data/reviews.csv");
  cleanData(uncleanedTransactionFile, "../data/transactions_cleaned.csv");
  cleanData(uncleanedReviewFile, "../data/reviews_cleaned.csv");
  uncleanedTransactionFile.close();
  uncleanedReviewFile.close();

  // Open cleaned files
  ifstream transactionFile("../data/transactions_cleaned.csv");
  ifstream reviewFile("../data/reviews_cleaned.csv");

  // Count rows
  int transCount = rowsNum(transactionFile);
  int reviewCount = rowsNum(reviewFile);

  // Reset file pointers
  transactionFile.clear();
  transactionFile.seekg(0);
  string dummyLine;
  getline(transactionFile, dummyLine); // Skip header
  reviewFile.clear();
  reviewFile.seekg(0);
  getline(reviewFile, dummyLine); // Skip header

  // Declare and initialize reviewList and reviewArray
  LinkList<reviews> reviewList;
  reviews* reviewArray = nullptr;

  // Initialize reviewCount (previously referred to as count)
  int reviewCount = rowsNum(reviewFile);

  // Allocate memory for reviewArray
  reviewArray = new reviews[reviewCount];

  // Analyze top words
  oneStarReview::analyzeTopWords(reviewList);       // for linked list
  oneStarReview::analyzeTopWords(reviewArray, reviewCount); // for array


  // Choose data structure
  cout << "Choose a mode to run:" << endl;
  cout << "\t1. Linked List" << endl;
  cout << "\t2. Array" << endl;
  cout << "Mode: ";
  int choice;
  cin >> choice;

  // Data structures
  LinkList<transactions> transactionList;
  LinkList<reviews> reviewList;
  transactions *transArray = nullptr;
  reviews *reviewArray = nullptr;

  // Load data based on choice
  if (choice == 1) {
    loadTransaction(transactionFile, transactionList);
    loadReview(reviewFile, reviewList);
  } else if (choice == 2) {
    transArray = new transactions[transCount];
    reviewArray = new reviews[reviewCount];
    loadTransaction(transactionFile, transArray, transCount);
    loadReview(reviewFile, reviewArray, reviewCount);
  } else {
    cout << "Invalid mode choice" << endl;
    return 1;
  }

  // Main menu loop
  bool exit = false;
  while (!exit) {
    displayMainMenu();
    int funcChoice;
    cin >> funcChoice;

    switch (funcChoice) {
    case 1:
      sortByDateMenu(choice, transactionList, reviewList, transArray,
                     reviewArray, transCount, reviewCount);
      break;
    case 2:
      filterByCategoryAndPayment(choice, transactionList, transArray,
                                 transCount);
      break;
    case 3:
      checkNegativeReviews(choice, reviewList, reviewArray, reviewCount);
      break;
    case 4:
      exit = true;
      break;
    default:
      cout << "Invalid choice, please try again." << endl;
      break;
    }
  }

  // Clean up
  if (choice == 2) {
    delete[] transArray;
    delete[] reviewArray;
  }

  return 0;
}

// Methods

// load link list
void loadTransaction(ifstream &transactionFile,
                     LinkList<transactions> &transactionList) {

  string line;

  while (getline(transactionFile, line)) {
    stringstream ss(line);
    string custID, prod, cat, priceStr, date, paymentMethod;
    getline(ss, custID, ',');
    getline(ss, prod, ',');
    getline(ss, cat, ',');
    getline(ss, priceStr, ',');
    getline(ss, date, ',');
    getline(ss, paymentMethod);

    transactions t;

    t.custID = custID;
    t.prod = prod;
    t.cat = cat;
    t.price = stod(priceStr);
    t.date = date;
    t.paymentMethod = trim(paymentMethod);

    transactionList.addData(t);
  }
}

// load array
void loadTransaction(ifstream &transactionFile, transactions *transArray,
                     int size) {
  string line;

  int index = 0;

  while (getline(transactionFile, line) && index < size) {
    stringstream ss(line);
    string custID, prod, cat, priceStr, date, paymentMethod;
    getline(ss, custID, ',');
    getline(ss, prod, ',');
    getline(ss, cat, ',');
    getline(ss, priceStr, ',');
    getline(ss, date, ',');
    getline(ss, paymentMethod);

    transactions t;

    t.custID = custID;
    t.prod = prod;
    t.cat = cat;
    t.price = stod(priceStr);
    t.date = date;
    t.paymentMethod = trim(paymentMethod);

    transArray[index] = t;
    index++;
  }
}

// Use to display the transactions array
void displayTransactionArr(transactions *transArr, int size) {
  cout << "Transactions (Array):" << endl;
  for (int i = 0; i < size; i++) {
    transArr[i].print();
  }
}

// load link list
void loadReview(ifstream &reviewFile, LinkList<reviews> &reviewList) {
  string line;

  // Read Reviews
  while (getline(reviewFile, line)) {
    stringstream ss(line);
    string prodID, custID, ratingStr, reviewText;

    getline(ss, prodID, ',');
    getline(ss, custID, ',');
    getline(ss, ratingStr, ',');
    getline(ss, reviewText);

    reviews r;

    r.prodID = prodID;
    r.custID = custID;
    r.rating = stoi(ratingStr);
    r.review = reviewText;

    reviewList.addData(r);
  }
}

void calculatePercentage(LinkList<transactions> &transactionList,
                         const string &category, const string &paymentMethod) {
  int categoryCount = 0;
  int matchCount = 0;

  Node<transactions> *current = transactionList.getHead();

  while (current != nullptr) {
    if (current->data.cat == category) {
      categoryCount++;
      if (current->data.paymentMethod == paymentMethod) {
        matchCount++;
      }
    }
    current = current->next;
  }

  double percentage =
      (categoryCount > 0) ? (double)matchCount / categoryCount * 100 : 0;
  cout << "Category: " << category << endl;
  cout << "Payment Method: " << paymentMethod << endl;
  cout << "Transactions in category: " << categoryCount << endl;
  cout << "Transactions with payment method: " << matchCount << endl;
  cout << "Percentage: " << fixed << setprecision(2) << percentage << "%"
       << endl;
}

// Use to filter the transactions based on the category and payment method
// using link list
void linearSearch(int catChoice, int paymentChoice, int size,
                  LinkList<transactions> &transactionList) {
  string selectedCat;
  string selectedPaymentMethod;

  switch (catChoice) {
  case Automotive:
    selectedCat = "Automotive";
    break;
  case Books:
    selectedCat = "Books";
    break;
  case Groceries:
    selectedCat = "Groceries";
    break;
  case Sports:
    selectedCat = "Sports";
    break;
  case Toys:
    selectedCat = "Toys";
    break;
  case Beauty:
    selectedCat = "Beauty";
    break;
  case Furniture:
    selectedCat = "Furniture";
    break;
  case Electronics:
    selectedCat = "Electronics";
    break;
  case Fashion:
    selectedCat = "Fashion";
    break;
  case HomeAppliances:
    selectedCat = "Home Appliances";
    break;
  default:
    cout << "Unknown Category Choice" << endl;
    break;
  }

  switch (paymentChoice) {
  case BankTransfer:
    selectedPaymentMethod = "Bank Transfer";
    break;
  case PayPal:
    selectedPaymentMethod = "PayPal";
    break;
  case DebitCard:
    selectedPaymentMethod = "Debit Card";
    break;
  case COD:
    selectedPaymentMethod = "Cash on Delivery";
    break;
  case CreditCard:
    selectedPaymentMethod = "Credit Card";
    break;
  default:
    cout << "Unknown Payment Method Choice" << endl;
    break;
  }

  cout << "Filtered List: " << endl;

  Node<transactions> *current = transactionList.getHead();

  while (current != nullptr) {

    if (current->data.cat == selectedCat &&
        current->data.paymentMethod == selectedPaymentMethod) {
      current->data.print();
    }
    current = current->next;
  }

  calculatePercentage(transactionList, selectedCat, selectedPaymentMethod);
}

// load array
void loadReview(ifstream &reviewFile, reviews *reviewArray, int size) {
  string line;

  int index = 0;

  // Read Reviews
  while (getline(reviewFile, line) && index < size) {
    stringstream ss(line);
    string prodID, custID, ratingStr, reviewText;

    getline(ss, prodID, ',');
    getline(ss, custID, ',');
    getline(ss, ratingStr, ',');
    getline(ss, reviewText);

    reviews r;

    r.prodID = prodID;
    r.custID = custID;
    r.rating = stoi(ratingStr);
    r.review = reviewText;

    reviewArray[index] = r;
    index++;
  }
}

// Use to display the reviews array
void displayReviewsArray(reviews *reviewArray, int size) {
  cout << "Reviews (Array):" << endl;
  for (int i = 0; i < size; i++) {
    reviewArray[i].print();
  }
}

void calculatePercentage(transactions *transArray, int size,
                         const string &category, const string &paymentMethod) {
  int categoryCount = 0;
  int matchCount = 0;

  for (int i = 0; i < size; i++) {
    if (transArray[i].cat == category) {
      categoryCount++;
      if (transArray[i].paymentMethod == paymentMethod) {
        matchCount++;
      }
    }
  }

  double percentage =
      (categoryCount > 0) ? (double)matchCount / categoryCount * 100 : 0;
  cout << "Category: " << category << endl;
  cout << "Payment Method: " << paymentMethod << endl;
  cout << "Transactions in category: " << categoryCount << endl;
  cout << "Transactions with payment method: " << matchCount << endl;
  cout << "Percentage: " << fixed << setprecision(2) << percentage << "%"
       << endl;
}

// Use to filter the transactions based on the category and payment method
// using array
void linearSearch(int catChoice, int paymentChoice, int size,
                  transactions *transArray) {
  string selectedCat;
  string selectedPaymentMethod;

  switch (catChoice) {
  case Automotive:
    selectedCat = "Automotive";
    break;
  case Books:
    selectedCat = "Books";
    break;
  case Groceries:
    selectedCat = "Groceries";
    break;
  case Sports:
    selectedCat = "Sports";
    break;
  case Toys:
    selectedCat = "Toys";
    break;
  case Beauty:
    selectedCat = "Beauty";
    break;
  case Furniture:
    selectedCat = "Furniture";
    break;
  case Electronics:
    selectedCat = "Electronics";
    break;
  case Fashion:
    selectedCat = "Fashion";
    break;
  case HomeAppliances:
    selectedCat = "Home Appliances";
    break;
  default:
    cout << "Unknown Category Choice" << endl;
    break;
  }

  switch (paymentChoice) {
  case BankTransfer:
    selectedPaymentMethod = "Bank Transfer";
    break;
  case PayPal:
    selectedPaymentMethod = "PayPal";
    break;
  case DebitCard:
    selectedPaymentMethod = "Debit Card";
    break;
  case COD:
    selectedPaymentMethod = "Cash on Delivery";
    break;
  case CreditCard:
    selectedPaymentMethod = "Credit Card";
    break;
  default:
    cout << "Unknown Payment Method Choice" << endl;
    break;
  }

  cout << "Filtered List: " << endl;
  for (int i = 0; i < size; i++) {
    if (transArray[i].cat == selectedCat &&
        transArray[i].paymentMethod == selectedPaymentMethod) {
      transArray[i].print();
    }
  }

  calculatePercentage(transArray, size, selectedCat, selectedPaymentMethod);
}

// Use to count the number of rows in the file
int rowsNum(ifstream &file) {
  int count = 0;
  string line;

  getline(file, line);

  while (getline(file, line)) {
    if (!line.empty()) {
      count++;
    }
  }

  file.clear();
  file.seekg(0);
  return count;
}

void cleanData(ifstream &inputFile, const string &outputFilename) {
  ofstream outputFile(outputFilename);

  if (!inputFile.is_open() || !outputFile.is_open()) {
    cout << "Error opening files!" << endl;
    return;
  }

  string line;

  // Copy the header to the output file
  getline(inputFile, line);
  outputFile << line << endl;

  // Process each data row
  while (getline(inputFile, line)) {
    // Skip empty lines
    if (line.empty()) {
      continue;
    }

    // Count the maximum possible number of fields (commas + 1)
    int maxFields = 1;
    for (char c : line) {
      if (c == ',')
        maxFields++;
    }

    // Create an array to hold the fields
    string *fields = new string[maxFields];
    int fieldCount = 0;

    // Parse CSV line accounting for quoted fields
    bool inQuotes = false;
    string currentField = "";

    for (char c : line) {
      if (c == '"') {
        inQuotes = !inQuotes;
      } else if (c == ',' && !inQuotes) {
        // Add the completed field
        fields[fieldCount++] = trim(currentField);
        currentField = "";
      } else {
        currentField += c;
      }
    }
    // Add the last field
    fields[fieldCount++] = trim(currentField);

    // Now check the fields for problems
    bool hasEmptyField = false;
    bool hasInvalidValue = false;

    for (int i = 0; i < fieldCount; i++) {
      // Check for empty fields
      if (fields[i].empty()) {
        hasEmptyField = true;
        break;
      }

      // Check for "Invalid" or "NaN"
      string lowerField = fields[i];
      // Convert to lowercase for case-insensitive comparison
      for (char &c : lowerField) {
        c = tolower(c);
      }

      if (lowerField == "invalid" || lowerField == "nan" ||
          lowerField == "invalid date" || lowerField == "invalid rating") {
        hasInvalidValue = true;
        break;
      }
    }

    // Write the valid line to the output file
    if (!hasEmptyField && !hasInvalidValue) {
      outputFile << line << endl;
    }

    // Clean up the dynamically allocated array
    delete[] fields;
  }

  inputFile.close();
  outputFile.close();
}

void displayMainMenu() {
  cout << "\n==========Main Menu==========" << endl;
  cout << "1. Sort by date" << endl;
  cout << "2. Filter by category and payment method" << endl;
  cout << "3. Check negative reviews" << endl;
  cout << "4. Exit" << endl;
  cout << "Choice: ";
}

void sortByDateMenu(int choice, LinkList<transactions> &transactionList,
                    LinkList<reviews> &reviewList, transactions *transArray,
                    reviews *reviewArray, int transCount, int reviewCount) {
  cout << "\nChoose a process:" << endl;
  cout << "1. Regular sort of transaction data" << endl;
  cout << "2. Inner join on Customer ID and sort by date" << endl;
  cout << "3. Left join on Customer ID and sort by date" << endl;
  cout << "Choice: ";
  int processChoice;
  cin >> processChoice;

  cout << "\nChoose a sorting algorithm:" << endl;
  cout << "1. Bubble Sort" << endl;
  cout << "2. Insertion Sort" << endl;
  cout << "3. Radix Sort" << endl;
  cout << "Sorting Algorithm: ";
  int sortChoice;
  cin >> sortChoice;

  if (choice == 1) { // Linked List
    if (processChoice == 1) {
      cout << "\nSorting transaction data..." << endl;
      switch (sortChoice) {
      case 1:
        bubblesort::displaySortedByDate(transactionList);
        break;
      case 2:
        insertionSort::insertionsort(&transactionList);
        break;
      case 3: {
        auto start = chrono::high_resolution_clock::now();
        radixSort::radixsort(&transactionList, transCount);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> duration = end - start;
        cout << "\nSorting completed in " << duration.count()
             << " milliseconds." << endl;
        break;
      }
      default:
        cout << "\nUnknown sorting algorithm" << endl;
        break;
      }
    } else if (processChoice == 2) {
      LinkList<mergedData> mergedList;
      JoinedData::innerJoinLists(transactionList, reviewList, mergedList);
      cout << "\nInner join completed. Total records: " << mergedList.getCount()
           << endl;
      cout << "\nSample of joined data (before sorting):" << endl;
      int displayCount = 0;
      Node<mergedData> *current = mergedList.getHead();
      while (current != nullptr && displayCount < 5) {
        current->data.print();
        current = current->next;
        displayCount++;
      }
      cout << "\nSorting joined data by date..." << endl;
      switch (sortChoice) {
      case 1:
        bubblesort::displaySortedByDate(mergedList);
        break;
      case 2:
        insertionSort::insertionsort(&mergedList);
        break;
      case 3: {
        auto start = chrono::high_resolution_clock::now();
        radixSort::radixsort(&mergedList, mergedList.getCount());
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> duration = end - start;
        cout << "\nSorting completed in " << duration.count()
             << " milliseconds." << endl;
        break;
      }
      default:
        cout << "\nUnknown sorting algorithm" << endl;
        break;
      }
      cout << "\nSample of joined data (after sorting):" << endl;
      displayCount = 0;
      current = mergedList.getHead();
      while (current != nullptr && displayCount < 5) {
        current->data.print();
        current = current->next;
        displayCount++;
      }
    } else if (processChoice == 3) {
      LinkList<mergedData> mergedList;
      JoinedData::leftJoinLists(transactionList, reviewList, mergedList);
      cout << "\nLeft join completed. Total records: " << mergedList.getCount()
           << endl;
      cout << "\nSample of joined data (before sorting):" << endl;
      int displayCount = 0;
      Node<mergedData> *current = mergedList.getHead();
      while (current != nullptr && displayCount < 5) {
        current->data.print();
        current = current->next;
        displayCount++;
      }
      cout << "\nSorting joined data by date..." << endl;
      switch (sortChoice) {
      case 1:
        bubblesort::displaySortedByDate(mergedList);
        break;
      case 2:
        insertionSort::insertionsort(&mergedList);
        break;
      case 3: {
        auto start = chrono::high_resolution_clock::now();
        radixSort::radixsort(&mergedList, mergedList.getCount());
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> duration = end - start;
        cout << "\nSorting completed in " << duration.count()
             << " milliseconds." << endl;
        break;
      }
      default:
        cout << "\nUnknown sorting algorithm" << endl;
        break;
      }
      cout << "\nSample of joined data (after sorting):" << endl;
      displayCount = 0;
      current = mergedList.getHead();
      while (current != nullptr && displayCount < 5) {
        current->data.print();
        current = current->next;
        displayCount++;
      }
    } else {
      cout << "\nInvalid process choice" << endl;
    }
  } else if (choice == 2) { // Array
    if (processChoice == 1) {
      cout << "\nSorting transaction data..." << endl;
      switch (sortChoice) {
      case 1:
        bubblesort::displaySortedByDate(
            transactionList); // Note: This seems incorrect in original; should
                              // be transArray
        break;
      case 2:
        insertionSort::insertionsort(transArray, transCount);
        break;
      case 3: {
        auto start = chrono::high_resolution_clock::now();
        radixSort::radixsort(transArray, transCount);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> duration = end - start;
        cout << "\nSorting completed in " << duration.count()
             << " milliseconds." << endl;
        break;
      }
      default:
        cout << "\nUnknown sorting algorithm" << endl;
        break;
      }
    } else if (processChoice == 2) {
      mergedData *joinedArray = new mergedData[transCount * reviewCount];
      int joinedSize = 0;
      JoinedData::innerJoinArrays(transArray, transCount, reviewArray,
                                  reviewCount, joinedArray, joinedSize);
      cout << "\nInner join completed. Total records: " << joinedSize << endl;
      cout << "\nSample of joined data (before sorting):" << endl;
      for (int i = 0; i < min(5, joinedSize); i++) {
        joinedArray[i].print();
      }
      cout << "\nSorting joined data by date..." << endl;
      switch (sortChoice) {
      case 1:
        // bubblesort::displaySortedByDate(joinedArray); // Adjust as needed
        break;
      case 2:
        // quickSort::displaySortedByDate(joinedArray);
        break;
      case 3: {
        auto start = chrono::high_resolution_clock::now();
        radixSort::radixsort(joinedArray, joinedSize);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> duration = end - start;
        cout << "\nSorting completed in " << duration.count()
             << " milliseconds." << endl;
        break;
      }
      default:
        cout << "\nUnknown sorting algorithm" << endl;
        break;
      }
      cout << "\nSample of joined data (after sorting):" << endl;
      for (int i = 0; i < min(5, joinedSize); i++) {
        joinedArray[i].print();
      }
      delete[] joinedArray;
    } else if (processChoice == 3) {
      mergedData *joinedArray = new mergedData[transCount * reviewCount];
      int joinedSize = 0;
      JoinedData::leftJoinArrays(transArray, transCount, reviewArray,
                                 reviewCount, joinedArray, joinedSize);
      cout << "\nLeft join completed. Total records: " << joinedSize << endl;
      cout << "\nSample of joined data (before sorting):" << endl;
      for (int i = 0; i < min(5, joinedSize); i++) {
        joinedArray[i].print();
      }
      cout << "\nSorting joined data by date..." << endl;
      switch (sortChoice) {
      case 1:
        // bubblesort::displaySortedByDate(joinedArray); // Adjust as needed
        break;
      case 2:
        // quickSort::displaySortedByDate(joinedArray);
        break;
      case 3: {
        auto start = chrono::high_resolution_clock::now();
        radixSort::radixsort(joinedArray, joinedSize);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> duration = end - start;
        cout << "\nSorting completed in " << duration.count()
             << " milliseconds." << endl;
        break;
      }
      default:
        cout << "\nUnknown sorting algorithm" << endl;
        break;
      }
      cout << "\nSample of joined data (after sorting):" << endl;
      for (int i = 0; i < min(5, joinedSize); i++) {
        joinedArray[i].print();
      }
      delete[] joinedArray;
    } else {
      cout << "\nInvalid process choice" << endl;
    }
  }
}

void filterByCategoryAndPayment(int choice,
                                LinkList<transactions> &transactionList,
                                transactions *transArray, int transCount) {
  cout << "\nChoose a category to filter:" << endl;
  cout << "\t1. Automotive\n\t2. Books\n\t3. Groceries\n\t4. Sports\n\t5. "
          "Toys\n\t6. Beauty\n\t7. Furniture\n\t8. Electronics\n\t9. "
          "Fashion\n\t10. Home Appliances"
       << endl;
  cout << "Category: ";
  int catChoice;
  cin >> catChoice;

  cout << "\nChoose a payment method to filter:" << endl;
  cout << "\t1. Bank Transfer\n\t2. PayPal\n\t3. Debit Card\n\t4. Cash on "
          "Delivery\n\t5. Credit Card"
       << endl;
  cout << "Payment Method: ";
  int paymentChoice;
  cin >> paymentChoice;

  if (choice == 1) {
    linearSearch(catChoice, paymentChoice, transCount, transactionList);
  } else if (choice == 2) {
    linearSearch(catChoice, paymentChoice, transCount, transArray);
  } else {
    cout << "\nInvalid mode choice" << endl;
  }
}

void checkNegativeReviews(int choice, LinkList<reviews> &reviewList,
                          reviews *reviewArray, int reviewCount) {
  if (choice == 1) {
    processOneStarReviews(reviewList);
  } else if (choice == 2) {
    LinkList<reviews> tempReviewList;
    for (int i = 0; i < reviewCount; i++) {
      tempReviewList.addData(reviewArray[i]);
    }
    processOneStarReviews(tempReviewList);
  } else {
    cout << "Invalid mode choice" << endl;
  }
}
