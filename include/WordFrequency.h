#pragma once
#include "LinkList.h"
#include "reviews.h"
#include <string>

using namespace std;

struct WordFrequency {
  string word;
  int count;

  WordFrequency() : word(""), count(0) {}
  WordFrequency(const string &w) : word(w), count(1) {}
};

int getMaxFrequency(LinkList<WordFrequency> *wordList);
void countSort(LinkList<WordFrequency> *wordList, int n, int exp);
void radixsort(LinkList<WordFrequency> *wordList, int n);
string cleanWord(const string &word);
void displayTopWords(const LinkList<WordFrequency> &wordList, int n);
void processOneStarReviews(LinkList<reviews> &reviewList);
