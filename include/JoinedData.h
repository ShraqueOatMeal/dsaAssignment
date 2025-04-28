#pragma once

#include "LinkList.h"
#include "reviews.h"
#include "transactions.h"
#include <iostream>
using namespace std;

struct mergedData {
  // Transactions Fields
  string custID;
  string prod;
  string cat;
  double price;
  string date;
  string paymentMethod;

  // Reviews Fields
  string prodID;
  int rating;
  string review;

  void print() const {
    cout << custID << " " << prod << " " << cat << " " << price << " " << date
         << " " << paymentMethod << endl;
  }
};

class JoinedData {
public:
  JoinedData();
  ~JoinedData();
  static void innerJoinLists(LinkList<transactions> &transactionList,
                             LinkList<reviews> &reviewList,
                             LinkList<mergedData> &joinedList);
  static void innerJoinArrays(transactions *transArray, int transCount,
                              reviews *reviewArray, int reviewCount,
                              mergedData *mergedArray, int mergedCount);
};
