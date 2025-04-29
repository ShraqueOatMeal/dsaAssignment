#pragma once
#include "transactions.h"

class jumpSearch {
public:
    jumpSearch();
    ~jumpSearch();

    static void searchByProduct(transactions* arr, int size, const string& product);
    static void searchByCategory(transactions* arr, int size, const string& category);
    static void searchByPaymentMethod(transactions* arr, int size, const string& method);
    static void calculateElectronicsCreditPercentage(transactions* arr, int size);
    static void searchMenu(transactions* arr, int size);
};
