#pragma once
#include "JoinedData.h"
using namespace std;

struct ReviewNode {
    string reviewText;
    int frequency;
    ReviewNode *next;

    ReviewNode(string text) : reviewText(text), frequency(1), next(nullptr) {}
};

class binarySearch {
public:
    static void calculateElectronicsCreditPercentage(LinkList<transactions> &arr);
    static void calculateBadReviewsCommonSentences(LinkList<reviews> &arr);
    
    static void calculateElectronicsCreditPercentage(transactions *arr, int size);
    static void calculateBadReviewsCommonSentences(reviews *arr, int size);
  
};