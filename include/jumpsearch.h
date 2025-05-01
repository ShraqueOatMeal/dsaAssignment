#pragma once
#include "transactions.h"
#include "LinkList.h"
using namespace std;

class jumpSearch {
public:
    jumpSearch();
    ~jumpSearch();

    // Array-based search functions
    void searchByProduct(transactions* arr, int size, const string& product);
    void searchByCategory(transactions* arr, int size, const string& category);
    void searchByPaymentMethod(transactions* arr, int size, const string& method);
    void calculateElectronicsCreditPercentage(transactions* arr, int size);

    // Interactive menu (original)
    void searchMenu(transactions* arr, int size); // user input version

    // Auto-menu: array and linked list
    void searchMenu(transactions* arr, int size, int catChoice, int paymentChoice); // ✅ your new array version
    void searchMenu(LinkList<transactions>& list, int catChoice, int paymentChoice); // ✅ your new linked list version
};
