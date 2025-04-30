#include "LLquickSort.hpp"

LLquickSort::LLquickSort() {}
LLquickSort::~LLquickSort() {}

void LLquickSort::quickSort(Node<transactions> *&head, Node<transactions> *&tail) {
    // Implement Quick Sort logic for linked lists of transactions
}

void LLquickSort::quickSort(Node<reviews> *&head, Node<reviews> *&tail) {
    // Implement Quick Sort logic for linked lists of reviews
}

void LLquickSort::swap(Node<transactions> *a, Node<transactions> *b) {
    transactions temp = a->data;
    a->data = b->data;
    b->data = temp;
}

void LLquickSort::swap(Node<reviews> *a, Node<reviews> *b) {
    reviews temp = a->data;
    a->data = b->data;
    b->data = temp;
}