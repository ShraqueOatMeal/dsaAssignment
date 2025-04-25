#include "WordFrequency.h"
#include "LinkList.h"
#include "reviews.h"
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

string cleanWord(const string &word) {
  string result;
  for (char c : word) {
    if (isalpha(c)) {
      result += tolower(c);
    }
  }
  return result;
}

int getMaxFrequency(LinkList<WordFrequency> *wordList) {
  Node<WordFrequency> *current = wordList->getHead();
  int max = 0;
  while (current != nullptr) {
    if (current->data.count > max) {
      max = current->data.count;
    }
    current = current->next;
  }
  return max;
}

void countSort(LinkList<WordFrequency> *wordList, int n, int exp) {
  LinkList<WordFrequency> count[10];

  Node<WordFrequency> *current = wordList->getHead();

  while (current != nullptr) {
    int digit = (current->data.count / exp) % 10;
    count[digit].addData(current->data);
    current = current->next;
  }

  wordList->clear();

  for (int i = 0; i < 10; i++) {
    Node<WordFrequency> *countNode = count[i].getHead();
    while (countNode != nullptr) {
      wordList->addData(countNode->data);
      countNode = countNode->next;
    }
  }
}

void radixsort(LinkList<WordFrequency> *wordList, int n) {
  // Find the maximum frequency to know number of digits
  int maxFreq = getMaxFrequency(wordList);

  // Do counting sort for every digit
  for (int exp = 1; maxFreq / exp > 0; exp *= 10) {
    countSort(wordList, n, exp);
  }

  // After sorting, we have ascending order, but we want descending for
  // frequencies So we'll reverse the list
  if (wordList->getHead() == nullptr || wordList->getHead()->next == nullptr) {
    return;
  }

  LinkList<WordFrequency> reversedList;
  Node<WordFrequency> *current = wordList->getHead();

  // Count nodes in the list
  while (current != nullptr) {
    Node<WordFrequency> *newNode = new Node<WordFrequency>(current->data);

    if (reversedList.getHead() == nullptr) {
      reversedList.addData(current->data);
    } else {
      newNode->next = reversedList.getHead();
      reversedList.setHead(newNode);
    }
    current = current->next;
  }

  // Clear original list
  wordList->clear();

  current = reversedList.getHead();
  while (current != nullptr) {
    wordList->addData(current->data);
    current = current->next;
  }
}

void displayTopWords(const LinkList<WordFrequency> &wordList, int n) {
  cout << "Top " << n << " most frequent words in 1-star reviews:" << endl;
  cout << "----------------------------------------------" << endl;

  Node<WordFrequency> *current = wordList.getHead();
  int count = 0;

  while (current != nullptr && count < n) {
    cout << count + 1 << ". " << current->data.word << " (appears "
         << current->data.count << " times)" << endl;
    current = current->next;
    count++;
  }

  cout << "----------------------------------------------" << endl;
}

void processOneStarReviews(LinkList<reviews> &reviewList) {
  LinkList<WordFrequency> wordFrequencyList;
  Node<reviews> *current = reviewList.getHead();

  cout << "\nAnalyzing words in 1-star reviews...\n" << endl;

  int wordCount = 0;

  // Iterate through all reviews
  while (current != nullptr) {
    // Filter reviews with rating = 1
    if (current->data.rating == 1) {
      string reviewText = current->data.review;
      istringstream iss(reviewText);
      string word;

      // Extract words from the review
      while (iss >> word) {
        // Remove punctuation and convert to lowercase
        word = cleanWord(word);

        if (word.empty() || word.length() < 3) {
          // Skip empty words or very short words (like "a", "an", "the", etc.)
          continue;
        }

        // Check if word already exists in the list
        bool found = false;
        Node<WordFrequency> *wordNode = wordFrequencyList.getHead();

        while (wordNode != nullptr) {
          if (wordNode->data.word == word) {
            // Word found, increment count
            wordNode->data.count++;
            found = true;
            break;
          }
          wordNode = wordNode->next;
        }

        // If word not found, add it to the list
        if (!found) {
          WordFrequency newWord(word);
          wordFrequencyList.addData(newWord);
          wordCount++;
        }
      }
    }
    current = current->next;
  }

  radixsort(&wordFrequencyList, wordCount);

  displayTopWords(wordFrequencyList, 10);
}
