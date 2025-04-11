#pragma once
#include <iostream>
using namespace std;

struct transactions;
void printReview(const transactions &t);

struct transactions {
  string custID;
  string prod;
  string cat;
  double price;
  string date;
  string paymentMethod;

  void print() const {
    cout << custID << " " << prod << " " << cat << " " << price << " " << date
         << " " << paymentMethod << endl;
  }
};
