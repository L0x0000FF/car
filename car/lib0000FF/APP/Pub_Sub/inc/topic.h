#ifndef TOPIC_H
#define TOPIC_H

#include "vector.hpp"

class Publisher;
class Subscriber;

class Topic {
 private:
  Vector<Publisher*> pub_list;
  Vector<Subscriber*> sub_list;

 public:
  char info[5];
  Topic(const char* info);
  ~Topic();
  void update(void* args);
  void reg(Publisher* pub);
  void reg(Subscriber* sub);
};


#endif  // TOPIC_H
