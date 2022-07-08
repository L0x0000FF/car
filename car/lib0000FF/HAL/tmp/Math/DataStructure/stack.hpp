#ifndef STACK_H
#define STACK_H

#include "node.hpp"

template <class T>
class Stack{
private:
  Node<T>* top;
  Node<T>* bottom;
  size_t length;
public:
  Stack(){
    this->top = nullptr;
    this->bottom = nullptr;
    this->length = 0;
  }

  ~Stack(){

  }

  void push(T& data){
    Node<T>* tmp = new Node<T>;
    tmp->data = data;
    if (length == 0) {
      this->top = tmp;
      this->bottom = tmp;
      tmp->prev = nullptr;
      tmp->next = nullptr;
      this->length++;
    } else {
      this->bottom->next = tmp;
      tmp->prev = this->end;
      tmp->next = nullptr;
      this->bottom = tmp;
      this->length++;
    }
  }

  void push(T data){
    Node<T>* tmp = new Node<T>;
    tmp->data = data;
    if (length == 0) {
      this->top = tmp;
      this->bottom = tmp;
      tmp->prev = nullptr;
      tmp->next = nullptr;
      this->length++;
    } else {
      this->bottom->next = tmp;
      tmp->prev = this->bottom;
      tmp->next = nullptr;
      this->bottom = tmp;
      this->length++;
    }
  }

  T pop(){
    if (this->bottom == nullptr)
      throw "Empty stack.\n";
    else {
      T tmp = this->bottom->data;
      if(this->length != 1){
        this->bottom = this->bottom->prev;
        if(this->bottom != nullptr)delete this->bottom->next;
        this->bottom->next = nullptr;
      }
      else{
        delete this->bottom;
        this->top = nullptr;
        this->bottom = nullptr;
      }
      this->length--;
      return tmp;
    }
  }

  T& getTop(){
    if (this->top == nullptr)
      throw "Empty stack.\n";
    else
      return this->top->data;
  }

  T& getBottom(){
    if (this->bottom == nullptr)
      throw "Empty stack.\n";
    else
      return this->bottom->data;
  }

};

#endif
