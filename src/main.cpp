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

int rowsNum(ifstream &file);

// System will run in here
int main(int argc, char *argv[]) {
  LinkList<reviews> reviewList;
  LinkList<transactions> transactionList;

  ifstream transactionFile("../../data/transactions_cleaned.csv");
  ifstream reviewFile("../../data/reviews_cleaned.csv");

  // loadTransaction(transactionFile, transactionList);
  // loadReview(reviewFile, reviewList);

  // cout << "Display csv data from link list: " << endl;
  // reviewList.display();
  // transactionList.display();

  int transCount = rowsNum(transactionFile);
  int reviewCount = rowsNum(reviewFile);

  transactions *transArray = new transactions[transCount];
  reviews *reviewArray = new reviews[reviewCount];

  loadTransaction(transactionFile, transArray, transCount);
  loadReview(reviewFile, reviewArray, reviewCount);

  // cout << "Display csv data from array: " << endl;
  // displayTransactionArr(transArray, transCount);
  // displayReviewsArray(reviewArray, reviewCount);

  // radixSort::radixsort(transArray, transCount);
  // displayTransactionArr(transArray, transCount);

  radixSort::radixsort(reviewArray, reviewCount);
  displayReviewsArray(reviewArray, reviewCount);

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
    t.paymentMethod = paymentMethod;

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
    t.paymentMethod = paymentMethod;

    transArray[index] = t;
    index++;
  }
}

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

void displayReviewsArray(reviews *reviewArray, int size) {
  cout << "Reviews (Array):" << endl;
  for (int i = 0; i < size; i++) {
    reviewArray[i].print();
  }
}

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
