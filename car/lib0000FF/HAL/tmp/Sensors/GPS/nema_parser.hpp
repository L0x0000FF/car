#ifndef NEMA_PARSER_HPP
#define NEMA_PARSER_HPP

#include "string"

typedef struct {

}NEMAData;

class NEMAParser {
private:
  NEMAData data;
public:
  NEMAParser();
  ~NEMAParser();
  void parse(std::string str);
  NEMAData getData();
};


#endif //NEMA_PARSER_HPP
