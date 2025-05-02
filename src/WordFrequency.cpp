#include "WordFrequency.h"
#include "LinkList.h"
// #include "insertionSort.hpp"
#include "reviews.h"
#include <chrono>
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int jumpSearch(WordFrequency arr[], int wordCount, const std::string &target);

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
  auto searchStart = chrono::high_resolution_clock::now();
  auto searchEnd = chrono::high_resolution_clock::now();

  while (current != nullptr) {
    if (current->data.rating == 1) {
      string reviewText = current->data.review;
      istringstream iss(reviewText);
      string word;

      // Extract words
      while (iss >> word) {
        word = cleanWord(word);
        if (word.empty() || word.length() < 3)
          continue;

        // Check if word already exists
        bool found = false;

        searchStart = chrono::high_resolution_clock::now();
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
          // TODO: binary search
        } else if (searchChoice == 3) {
          int stepSize = sqrt(wordCount);
          int steps = 0;
          Node<WordFrequency> *cur = wordFrequencyList.getHead();
          Node<WordFrequency> *prev = nullptr;

          while (cur != nullptr && cur->next != nullptr &&
                 cur->data.word < word && steps < wordCount) {
            prev = cur;
            for (int i = 0; i < stepSize && cur->next != nullptr; i++) {
              cur = cur->next;
              steps++;
            }
          }

          Node<WordFrequency> *scan =
              (prev != nullptr) ? prev : wordFrequencyList.getHead();
          while (scan != nullptr && scan != cur->next) {
            if (scan->data.word == word) {
              scan->data.count++;
              found = true;
              break;
            }
            scan = scan->next;
          }
        }
        searchEnd = chrono::high_resolution_clock::now();

        // Insert if not found
        if (!found) {
          WordFrequency newWord(word);
          Node<WordFrequency> *temp = wordFrequencyList.getHead();
          Node<WordFrequency> *prevInsert = nullptr;

          while (temp != nullptr && temp->data.word < word) {
            prevInsert = temp;
            temp = temp->next;
          }

          Node<WordFrequency> *newNode = new Node<WordFrequency>(newWord);
          if (prevInsert == nullptr) {
            newNode->next = wordFrequencyList.getHead();
            wordFrequencyList.setHead(newNode);
          } else {
            newNode->next = prevInsert->next;
            prevInsert->next = newNode;
          }

          wordCount++;
        }
      }
    }

    current = current->next;
  }

  // Sorting logic
  auto start = chrono::high_resolution_clock::now();
  if (sortChoice == 1) {
    // Bubble sort by frequency (descending)
    bool swapped;
    Node<WordFrequency> *ptr1;
    Node<WordFrequency> *lptr = nullptr;

    if (wordFrequencyList.getHead() != nullptr) {
      do {
        swapped = false;
        ptr1 = wordFrequencyList.getHead();

        while (ptr1->next != lptr) {
          if (ptr1->data.count < ptr1->next->data.count) {
            swap(ptr1->data, ptr1->next->data);
            swapped = true;
          }
          ptr1 = ptr1->next;
        }
        lptr = ptr1;
      } while (swapped);
    }
  } else if (sortChoice == 2) {
    // TODO: insertion sort
  } else if (sortChoice == 3) {
    radixsort(&wordFrequencyList, wordCount);
  }
  auto end = chrono::high_resolution_clock::now();

  chrono::duration<double, milli> searchDuration = searchEnd - searchStart;
  chrono::duration<double, milli> duration = end - start;
  cout << "\nSearch completed in " << searchDuration.count()
       << " milliseconds.\n";
  cout << "\nSorting completed in " << duration.count() << " milliseconds.\n";
  cout << "Time Complexity of ";
  if (sortChoice == 1)
    cout << "Bubble Sort: O(n^2)\n";
  else if (sortChoice == 2)
    cout << "Insertion Sort: O(n^2)\n";
  else if (sortChoice == 3)
    cout << "Radix Sort: O(n*d)\n";
  cout << "Estimated Space Complexity: O(n)\n";

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
  auto searchStart = chrono::high_resolution_clock::now();
  auto searchEnd = chrono::high_resolution_clock::now();

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
        searchStart = chrono::high_resolution_clock::now();
        if (searchChoice == 1) {
          for (int j = 0; j < wordCount; j++) {
            if (wordFrequencyArray[j].word == word) {
              wordFrequencyArray[j].count++;
              found = true;
              break;
            }
          }
        } else if (searchChoice == 2) {
          // TODO: binary search
        } else if (searchChoice == 3) {
          int pos = jumpSearch(wordFrequencyArray, wordCount, word);
          if (pos != -1) {
            wordFrequencyArray[pos].count++;
            found = true;
          }
        }
        searchEnd = chrono::high_resolution_clock::now();

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
    for (int i = 0; i < wordCount - 1; i++) {
      for (int j = 0; j < wordCount - i - 1; j++) {
        if (wordFrequencyArray[j].count < wordFrequencyArray[j + 1].count) {
          // Swap both word and frequency
          swap(wordFrequencyArray[j], wordFrequencyArray[j + 1]);
        }
      }
    }
    displayTopWordsArray(wordFrequencyArray, wordCount, 10); // remove afrter
  }
  if (sortChoice == 2) {
    // TODO: insertion sort

  } else if (sortChoice == 3) {
    radixsort(wordFrequencyArray, wordCount);    // Sorts in ascending order
    reverseArray(wordFrequencyArray, wordCount); // Reverses to descending order
  }
  auto end = chrono::high_resolution_clock::now();
  chrono::duration<double, milli> searchDuration = searchEnd - searchStart;
  chrono::duration<double, milli> duration = end - start;

  cout << "\nSearch completed in " << searchDuration.count()
       << " milliseconds.\n";
  cout << "\nSorting completed in " << duration.count() << " milliseconds.\n";
  cout << "Estimated Time Complexity of ";
  if (sortChoice == 1)
    cout << "Bubble Sort: O(n^2)\n";
  else if (sortChoice == 2)
    cout << "Insertion Sort: O(n^2)\n";
  else if (sortChoice == 3)
    cout << "Radix Sort: O(n*d)\n";
  cout << "Estimated Space Complexity: O(n)\n";
}

int jumpSearch(WordFrequency arr[], int wordCount, const string &target) {
  int step = sqrt(wordCount);
  int prev = 0;

  while (prev < wordCount && arr[min(step, wordCount) - 1].word < target) {
    prev = step;
    step += sqrt(wordCount);
    if (prev >= wordCount)
      return -1;
  }

  for (int i = prev; i < min(step, wordCount); i++) {
    if (arr[i].word == target)
      return i;
  }

  return -1;
}

void insertSorted(WordFrequency arr[], int &wordCount, const string &word) {
  int i = wordCount - 1;
  while (i >= 0 && arr[i].word > word) {
    arr[i + 1] = arr[i];
    i--;
  }
  arr[i + 1].word = word;
  arr[i + 1].count = 1;
  wordCount++;
}
