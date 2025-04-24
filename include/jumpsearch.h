#pragma once
#include "LinkList.h"
#include "transactions.h"

class jumpSearch {
public:
  jumpSearch();
  ~jumpSearch();
  static void searchByProduct(LinkList<transactions> &list,
                              const string &product);
  static void searchByCategory(LinkList<transactions> &list,
                               const string &category);
  static void searchByPaymentMethod(LinkList<transactions> &list,
                                    const string &paymentMethod);
  static void searchMenu(LinkList<transactions> &list);
};
