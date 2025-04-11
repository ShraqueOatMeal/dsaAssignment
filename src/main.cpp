#include "LinkList.h"
#include "reviews.h"
#include "transactions.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

void loadTransaction(ifstream &transactionFile,
                     LinkList<transactions> &transactionList);
void loadReview(ifstream &reviewFile, LinkList<reviews> &reviewList);

int main(int argc, char *argv[]) {
  LinkList<reviews> reviewList;
  LinkList<transactions> transactionList;

  ifstream transactionFile("../../data/transactions_cleaned.csv");
  ifstream reviewFile("../../data/reviews_cleaned.csv");

  loadTransaction(transactionFile, transactionList);
  loadReview(reviewFile, reviewList);

  cout << "Display csv data from link list: " << endl;
  reviewList.display();
  transactionList.display();

  return 0;
}

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
