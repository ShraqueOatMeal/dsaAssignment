#pragma once
#include "LinkList.h"
#include "transactions.h"
using namespace std;

class jumpSearch {
public:
  jumpSearch();
  ~jumpSearch();

  // Interactive menu (original)
  static void searchMenu(transactions *arr, int size); // user input version

  // Auto-menu: array and linked list
  static void searchMenu(transactions *arr, int size, int catChoice,
                         int paymentChoice); // ✅ your new array version
  static void searchMenu(LinkList<transactions> &list, int catChoice,
                         int paymentChoice); // ✅ your new linked list version
};
