#include "LinkList.h"
#include "radixSort.h"
#include "reviews.h"
#include "transactions.h"
#include <fstream>
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

// System will run in here
int main(int argc, char *argv[]) {
  LinkList<reviews> reviewList;
  LinkList<transactions> transactionList;

  ifstream transactionFile("../../data/transactions_cleaned.csv");
  ifstream reviewFile("../../data/reviews_cleaned.csv");

  // loadReview(reviewFile, reviewList);

  // cout << "Display csv data from link list: " << endl;
  // reviewList.display();
  // transactionList.display();

  int transCount = rowsNum(transactionFile);
  int reviewCount = rowsNum(reviewFile);

  transactions *transArray = new transactions[transCount];
  reviews *reviewArray = new reviews[reviewCount];

  loadTransaction(transactionFile, transactionList);
  loadTransaction(transactionFile, transArray, transCount);
  loadReview(reviewFile, reviewArray, reviewCount);

  // cout << "Display csv data from array: " << endl;
  // displayTransactionArr(transArray, transCount);
  // displayReviewsArray(reviewArray, reviewCount);

  // sort array using radix sort
  // radixSort::radixsort(transArray, transCount);
  // displayTransactionArr(transArray, transCount);

  // sort link list using radix sort
  radixSort::radixsort(&transactionList, transCount);
  transactionList.display();

  // sort review array using count sort, because radix sort is unnecessary
  // radixSort::countSort(reviewArray, reviewCount);
  // displayReviewsArray(reviewArray, reviewCount);

  // filter transactions based on the category and payment method
  // int catChoice;
  // int paymentChoice;
  // cout << "Choose a category to filter: " << endl;
  // cout << "\t1. Automotive\n\t2. Books\n\t3. Groceries\n\t4. Sports\n\t5. "
  //         "Toys\n\t6. Beauty\n\t7. Furniture\n\t8. Electronics\n\t9. "
  //         "Fashion\n\t10. Home Appliances"
  //      << endl;
  // cout << "Category: ";
  // cin >> catChoice;
  //
  // cout << "Choose a payment method to filter: " << endl;
  // cout << "\t1. Bank Transfer\n\t2. PayPal\n\t3. Debit Card\n\t4. Cash on "
  //         "Delivery\n\t5. "
  //         "Credit Card"
  //      << endl;
  // cout << "Payment Method: ";
  // cin >> paymentChoice;

  // filter transactions array based on the category and payment method
  // linearSearch(catChoice, paymentChoice, transCount, transArray);

  // filter transactions link list based on the category and payment method
  // linearSearch(catChoice, paymentChoice, transCount, transactionList);
  cout << endl;

  return 0;
}

// Methods

// load link list
void loadTransaction(ifstream &transactionFile,
                     LinkList<transactions> &transactionList) {

  string line;

  // Skip Header
  getline(transactionFile, line);

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

  // Skip Header
  getline(transactionFile, line);

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

  // Skip Header
  getline(reviewFile, line);

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
}

// load array
void loadReview(ifstream &reviewFile, reviews *reviewArray, int size) {
  string line;

  // Skip Header
  getline(reviewFile, line);

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
