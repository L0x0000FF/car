#ifndef QUEUE_H
#define QUEUE_H

#include <stdint.h>
#include "node.hpp"

template <class T>
class Queue {
 private:
  Node<T>* start;
  Node<T>* end;
  size_t length;

 public:
  Queue() {
    this->start = NULL;
    this->end = NULL;
    this->length = 0;
  }

  ~Queue() {
    Node<T>* tmp = this->end;
    while (tmp != NULL) {
      tmp = tmp->prev;
      if(tmp != NULL)delete tmp->next;
    }
  }

  size_t getLength() { return this->length; }

  void add(T& data) {
    Node<T>* tmp = new Node<T>;
    tmp->data = data;
    if (length == 0) {
      this->start = tmp;
      this->end = tmp;
      tmp->prev = NULL;
      tmp->start = NULL;
      this->length++;
    } else {
      this->end->next = tmp;
      tmp->prev = this->end;
      this->end = tmp;
      this->length++;
    }
  }

  void add(T data) {
    Node<T>* tmp = new Node<T>;
    tmp->data = data;
    if (length == 0) {
      this->start = tmp;
      this->end = tmp;
      tmp->prev = NULL;
      tmp->next = NULL;
      this->length++;
    } else {
      this->end->next = tmp;
      tmp->prev = this->end;
      tmp->next = NULL;
      this->end = tmp;
      this->length++;
    }
  }

  T pop() {
      T tmp = this->start->data;
      if(this->length != 1){
        this->start = this->start->next;
        if(this->start != NULL)delete this->start->prev;
        this->start->prev = NULL;
      }
      else{
        delete this->start;
        this->start = NULL;
        this->end = NULL;
      }
      this->length--;
      return tmp;
  }

  T& head() {
    return this->start->data;
  }

  T& tail() {
    return this->end->data;
  }
};

#endif
