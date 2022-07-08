#ifndef PID_HPP
#define PID_HPP


class PID {
private:
  float kp;
  float ki;
  float kd;
  float integralLimit; //integral limit = 0 -> no limit
  float outputLimit;
  float integral;
  float error[3];
public:
  float ref;
  float fbd;
  float output;
  PID();
  PID(float kp,float ki,float kd,float intergralLimt,float outputLimit);
  void setParam();
  void resetIntegral();
  void calc();
};


#endif //PID_HPP
