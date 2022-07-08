#include "topic.h"
#include "pub_sub.h"

#include <string.h>

Topic::Topic(const char* info) { strcpy(this->info, info); }

Topic::~Topic() {}

void Topic::update(void* args) {
  for (uint8_t i = 0; i < sub_list.getLength(); i++) {
    if(sub_list[i]->wakeupCallback != NULL)sub_list[i]->wakeupCallback(args);
  }
}

void Topic::reg(Publisher* pub) { pub_list.push_back(pub); }

void Topic::reg(Subscriber* sub) { sub_list.push_back(sub); }
