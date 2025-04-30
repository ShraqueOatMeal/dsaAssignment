#include "../include/insertionSort.hpp"
#include "../include/LinkList.h"
#include "../include/transactions.h"
#include "../include/reviews.h"
#include <string>
#include <sstream>
using namespace std;

// Helper function: Convert dd/mm/yyyy to yyyymmdd
int parseDate(const string &date) {
    int day, month, year;
    char delimiter;
    stringstream ss(date);
    ss >> day >> delimiter >> month >> delimiter >> year;
    return year * 10000 + month * 100 + day;
}

bool compareDates(const string &date1, const string &date2){
    int parseDate1 = parseDate(date1);
    int parseDate2 = parseDate(date2);

    return parseDate1 < parseDate2;
}

// Insertion Sort for array
void insertionSort::insertionSortTransactions(transactions *transArray, int size){
    for (int i = 1; i < size; i++){
        transactions key = transArray[i];
        int j = i - 1;

        // Move elements of transArray[0..i-1], that are greater than key,
        // to one position ahead of their current position
        while (j >= 0 && compareDates(transArray[j].date, key.date)){
            transArray[j + 1] = transArray[j];
            j = j - 1;
        }
        transArray[j + 1] = key; // Place the key in its correct position
    }
}