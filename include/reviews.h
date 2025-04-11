#pragma once
#include <iostream>
using namespace std;
struct reviews;
void printReview(const reviews &r);

struct reviews {
  string prodID;
  string custID;
  int rating;
  string review;

  void print() const {
    cout << prodID << " " << custID << " " << rating << " " << review << endl;
  };
};
