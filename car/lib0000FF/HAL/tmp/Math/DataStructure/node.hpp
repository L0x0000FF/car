#ifndef NODE_H
#define NODE_H

template <class T>
class Node {
 public:
  T data;
  Node* next;
  Node* prev;
  
  Node(){
    this->next = NULL;
    this->prev = NULL;
  }

  Node(T data){
    this->data = data;
    this->next = NULL;
    this->prev = NULL;
  }
};

#endif
