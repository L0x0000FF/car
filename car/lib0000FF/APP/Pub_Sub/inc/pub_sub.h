#ifndef PUB_SUB_H
#define PUB_SUB_H

#include "topic.h"

typedef enum{
  SUB_IDLE = 0,
  SUB_AWAKE
}SubscriberStatus;

class Publisher {
 private:
  Topic* topic;

 public:
  void* data;
  Publisher(const char* topic);
  ~Publisher();
  void publish(void* args);
};

class Subscriber {
 private:
  Topic* topic;

 public:
  void* data;
  void (*wakeupCallback)(void* args);
  Subscriber(const char* topic, void(wakeupCallback)(void* args) = NULL);
  ~Subscriber();
};

#endif
