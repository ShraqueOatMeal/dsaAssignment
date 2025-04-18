#pragma once

#include <iostream>
using namespace std;

template <typename T>

struct Node {
  T data;
  Node *next;

  Node(T val) : data(val), next(nullptr) {}
};

struct reviews;

struct transactions;

template <typename T> class LinkList {
private:
  Node<T> *head;
  Node<T> *tail;
  int size;

public:
  LinkList() : head(nullptr), tail(nullptr), size(0){};
  ~LinkList();

  void display();
  void addData(T data);
};

template <typename T> LinkList<T>::~LinkList() {}

template <typename T> void LinkList<T>::display() {
  Node<T> *current = head;
  while (current) {
    current->data.print();
    current = current->next;
  }
}

template <typename T> void LinkList<T>::addData(T data) {
  Node<T> *newNode = new Node<T>(data);
  if (!head)
    head = tail = newNode;
  else {
    tail->next = newNode;
    tail = newNode;
  }
  size++;
}
