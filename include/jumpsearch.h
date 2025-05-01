#pragma once
#include "transactions.h"
#include "LinkList.h"
using namespace std;

class jumpSearch {
public:
    jumpSearch();
    ~jumpSearch();

    // Array-based search functions
    static void searchByProduct(transactions* arr, int size, const string& product);
    static void searchByCategory(transactions* arr, int size, const string& category);
    static void searchByPaymentMethod(transactions* arr, int size, const string& method);
    static void calculateElectronicsCreditPercentage(transactions* arr, int size);

    // Interactive menu (original)
    static void searchMenu(transactions* arr, int size); // user input version

    // Auto-menu: array and linked list
    static void searchMenu(transactions* arr, int size, int catChoice, int paymentChoice); // ✅ your new array version
    static void searchMenu(LinkList<transactions>& list, int catChoice, int paymentChoice); // ✅ your new linked list version
};
