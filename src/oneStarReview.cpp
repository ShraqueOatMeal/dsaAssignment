#include "oneStarReview.h"
#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;

const int MAX_WORDS = 1000;
const int MAX_WORD_LENGTH = 50;

void cleanWord(char* word) {
    int len = strlen(word);
    int idx = 0;
    for (int i = 0; i < len; i++) {
        if (isalnum(word[i])) {
            word[idx++] = tolower(word[i]);
        }
    }
    word[idx] = '\0';
}

int findWord(char words[][MAX_WORD_LENGTH], int wordCount, const char* word) {
    for (int i = 0; i < wordCount; i++) {
        if (strcmp(words[i], word) == 0) {
            return i;
        }
    }
    return -1;
}

void sortWordsByFrequency(char words[][MAX_WORD_LENGTH], int freq[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (freq[j] < freq[j + 1]) {
                swap(freq[j], freq[j + 1]);

                char temp[MAX_WORD_LENGTH];
                strcpy(temp, words[j]);
                strcpy(words[j], words[j + 1]);
                strcpy(words[j + 1], temp);
            }
        }
    }
}

void oneStarReview::analyzeTopWords(LinkList<reviews>& reviewList) {
    char words[MAX_WORDS][MAX_WORD_LENGTH];
    int freq[MAX_WORDS] = {0};
    int wordCount = 0;

    Node<reviews>* current = reviewList.getHead();

    while (current != nullptr) {
        if (current->data.rating == 1) {
            char buffer[1000];
            strncpy(buffer, current->data.review.c_str(), 999);
            buffer[999] = '\0'; // Ensure null termination

            char* token = strtok(buffer, " ");
            while (token != nullptr) {
                cleanWord(token);
                if (strlen(token) > 0) {
                    int pos = findWord(words, wordCount, token);
                    if (pos == -1 && wordCount < MAX_WORDS) {
                        strncpy(words[wordCount], token, MAX_WORD_LENGTH - 1);
                        words[wordCount][MAX_WORD_LENGTH - 1] = '\0';
                        freq[wordCount] = 1;
                        wordCount++;
                    } else if (pos != -1) {
                        freq[pos]++;
                    }
                }
                token = strtok(nullptr, " ");
            }
        }
        current = current->next;
    }

    sortWordsByFrequency(words, freq, wordCount);

    cout << "\n==== Top 10 Frequent Words in 1-Star Reviews ====\n";
    int limit = (wordCount < 10) ? wordCount : 10;
    for (int i = 0; i < limit; i++) {
        cout << words[i] << ": " << freq[i] << endl;
    }
}
