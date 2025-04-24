#pragma once
#include "LinkList.h"
#include "transactions.h"

void searchByProduct(LinkList<transactions>& list, const string& product);
void searchByCategory(LinkList<transactions>& list, const string& category);
void searchByPaymentMethod(LinkList<transactions>& list, const string& paymentMethod);
void searchMenu(LinkList<transactions>& list);
