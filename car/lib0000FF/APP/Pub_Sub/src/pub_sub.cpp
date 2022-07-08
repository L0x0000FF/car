#include "pub_sub.h"

#include <string.h>
#include <vector.hpp>

Vector<Topic*> topics;

Publisher::Publisher(const char* topic) {
  data = NULL;
  uint8_t i;
  for (i = 0; i < topics.getLength(); i++) {
    if (!strcmp(topic, topics[i]->info)) {
      this->topic = topics[i];
      topics[i]->reg(this);
      break;
    }
  }
  if (i == topics.getLength()) {
    Topic* tmp = new Topic(topic);
    this->topic = tmp;
    tmp->reg(this);
    topics.push_back(tmp);
  }
}

Publisher ::~Publisher() {}

void Publisher::publish(void* args) { this->topic->update(args); }

Subscriber::Subscriber(const char* topic, void wakeupCallback(void* args)) {
  data = NULL;
  this->wakeupCallback = wakeupCallback;
  uint8_t i;
  for (i = 0; i < topics.getLength(); i++) {
    if (!strcmp(topic, topics[i]->info)) {
      this->topic = topics[i];
      topics[i]->reg(this);
      break;
    }
  }
  if (i == topics.getLength()) {
    Topic* tmp = new Topic(topic);
    this->topic = tmp;
    tmp->reg(this);
    topics.push_back(tmp);
  }
}

Subscriber ::~Subscriber() {}
