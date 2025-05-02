#include "WordFrequency.h"
#include "LinkList.h"
#include "insertionSort.hpp"
#include "binarySearch.hpp"
// #include "oneStarReview.h"
#include "reviews.h"
#include <chrono>
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

// Link List
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

void processOneStarReviews(LinkList<reviews> &reviewList, int sortChoice,
                           int searchChoice) {
  LinkList<WordFrequency> wordFrequencyList;
  Node<reviews> *current = reviewList.getHead();

  cout << "\nAnalyzing words in 1-star reviews...\n" << endl;

  int wordCount = 0;

  while (current != nullptr) {
    if (current->data.rating == 1) {
      string reviewText = current->data.review;
      istringstream iss(reviewText);
      string word;

      // Extract words
      while (iss >> word) {
        // Remove punctuation and convert to lowercase
        word = cleanWord(word);

        if (word.empty() || word.length() < 3) {
          // Skip empty words or very short words (like "a", "an", etc.)
          continue;
        }

        // Check if word already exists in the list
        bool found = false;
        if (searchChoice == 1) {
          Node<WordFrequency> *wordNode = wordFrequencyList.getHead();

          while (wordNode != nullptr) {
            if (wordNode->data.word == word) {
              wordNode->data.count++;
              found = true;
              break;
            }
            wordNode = wordNode->next;
          }
        } else if (searchChoice == 2) {
          binarySearch::calculateBadReviewsCommonWords(reviewList, 1);
        } else if (searchChoice == 3) {
          // TODO: jump search
          // oneStarReview::analyzeTopWords(reviewList);
        }

        if (!found) {
          WordFrequency newWord(word);
          wordFrequencyList.addData(newWord);
          wordCount++;
        }
      }
    }
    current = current->next;
  }

  auto start = chrono::high_resolution_clock::now();
  if (sortChoice == 1) {
    // TODO: bubble sort
  } else if (sortChoice == 2) {
    insertionSort::insertionsort(&wordFrequencyList);
  } else if (sortChoice == 3) {
    radixsort(&wordFrequencyList, wordCount);
  }
  auto end = chrono::high_resolution_clock::now();
  chrono::duration<double, milli> duration = end - start;
  cout << "\nSorting completed in " << duration.count() << " milliseconds.\n";
  cout << "Estimated Time Complexity of Radix Sort: O(n*d) \n";
  cout << "Estimated space used of Radix Sort: O(n) \n";

  displayTopWords(wordFrequencyList, 10);
}

// Array
int getMaxFrequency(WordFrequency *arr, int n) {
  int max = 0;
  for (int i = 0; i < n; i++) {
    if (arr[i].count > max) {
      max = arr[i].count;
    }
  }
  return max;
}

void countSort(WordFrequency *arr, int n, int exp) {
  WordFrequency *output = new WordFrequency[n];
  int count[10] = {0};

  // Count occurrences of each digit
  for (int i = 0; i < n; i++) {
    int digit = (arr[i].count / exp) % 10;
    count[digit]++;
  }

  // Compute cumulative counts
  for (int i = 1; i < 10; i++) {
    count[i] += count[i - 1];
  }

  // Build the output array (stable sort)
  for (int i = n - 1; i >= 0; i--) {
    int digit = (arr[i].count / exp) % 10;
    output[count[digit] - 1] = arr[i];
    count[digit]--;
  }

  // Copy back to original array
  for (int i = 0; i < n; i++) {
    arr[i] = output[i];
  }

  delete[] output;
}

// Radix sort for the array (sorts in ascending order)
void radixsort(WordFrequency *arr, int n) {
  int maxFreq = getMaxFrequency(arr, n);
  for (int exp = 1; maxFreq / exp > 0; exp *= 10) {
    countSort(arr, n, exp);
  }
}

// Reverse the array to convert ascending to descending order
void reverseArray(WordFrequency *arr, int n) {
  for (int i = 0; i < n / 2; i++) {
    WordFrequency temp = arr[i];
    arr[i] = arr[n - 1 - i];
    arr[n - 1 - i] = temp;
  }
}

// Display the top n words from the sorted array
void displayTopWordsArray(WordFrequency *wordArray, int wordCount, int n) {
  cout << "Top " << n << " most frequent words in 1-star reviews:" << endl;
  cout << "----------------------------------------------" << endl;
  for (int i = 0; i < n && i < wordCount; i++) {
    cout << i + 1 << ". " << wordArray[i].word << " (appears "
         << wordArray[i].count << " times)" << endl;
  }
  cout << "----------------------------------------------" << endl;
}

// Array version of processOneStarReviews
void processOneStarReviews(reviews *reviewArray, int reviewCount,
                           int sortChoice, int searchChoice) {
  const int MAX_WORDS = 10000; // Maximum number of unique words
  WordFrequency wordFrequencyArray[MAX_WORDS];
  int wordCount = 0;

  cout << "\nAnalyzing words in 1-star reviews...\n" << endl;

  // Process each review in the array
  for (int i = 0; i < reviewCount; i++) {
    if (reviewArray[i].rating == 1) {
      string reviewText = reviewArray[i].review;
      istringstream iss(reviewText);
      string word;

      // Extract and process each word
      while (iss >> word) {
        word = cleanWord(word);
        if (word.empty() || word.length() < 3) {
          continue; // Skip empty or short words
        }

        // Check if word exists in the array
        bool found = false;
        if (searchChoice == 1) {
          for (int j = 0; j < wordCount; j++) {
            if (wordFrequencyArray[j].word == word) {
              wordFrequencyArray[j].count++;
              found = true;
              break;
            }
          }
        } else if (searchChoice == 2) {
          binarySearch::calculateBadReviewsCommonWords(reviewArray, reviewCount);
        } else if (searchChoice == 3) {
          // TODO: jump search
          // oneStarReview::analyzeTopWords(reviewArray, reviewCount);
        }

        // Add new word if not found and space is available
        if (!found && wordCount < MAX_WORDS) {
          wordFrequencyArray[wordCount].word = word;
          wordFrequencyArray[wordCount].count = 1;
          wordCount++;
        }
      }
    }
  }

  // Sort the word frequency array
  auto start = chrono::high_resolution_clock::now();
  if (sortChoice == 1) {
    // TODO: bubble sort
  }
  if (sortChoice == 2) {
    insertionSort::insertionsort(wordFrequencyArray, wordCount);
  } else if (sortChoice == 3) {
    radixsort(wordFrequencyArray, wordCount);    // Sorts in ascending order
    reverseArray(wordFrequencyArray, wordCount); // Reverses to descending order
  }
  auto end = chrono::high_resolution_clock::now();
  chrono::duration<double, milli> duration = end - start;

  // Output sorting performance
  cout << "\nSorting completed in " << duration.count() << " milliseconds.\n";
  cout << "Estimated Time Complexity of Radix Sort: O(n*d) \n";
  cout << "Estimated space used of Radix Sort: O(n) \n";
  displayTopWordsArray(wordFrequencyArray, wordCount, 10);
}
