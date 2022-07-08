#ifndef PID_H
#define PID_H

#ifdef __cplusplus
extern "C"{
#endif

typedef struct Pid_t {
  enum type_e { POSITION_PID, INCREMENT_PID } type;
  float Kp;
  float Ki;
  float Kd;
  float ref;  // reference
  float fdb;  // feedback
  float output;
  float output_max;  // absolute value
  float error_max;
  float error[3];
  float error_sum;
} PID;

void PID_init(PID *pid, float kp, float ki, float kd, int outputMax,
              int errorMax);
void PID_calc(PID *pid);

#ifdef __cplusplus
}
#endif

#endif
