#include "pid.h"
#include <string.h>
#include <math.h>

void PID_init(PID *pid,float kp,float ki,float kd,int outputMax,int errorMax){
    memset(pid,0,sizeof(PID));
    pid->Kp = kp;
    pid->Ki = ki;   
    pid->Kd = kd;
    pid->output_max = outputMax;
    pid->error_max = errorMax;
    pid->type = INCREMENT_PID;  //default
}

void PID_calc(PID *pid){
    pid->error[2] = pid->error[1];
    pid->error[1] = pid->error[0];
    pid->error[0] = pid->fdb - pid->ref;
    pid->error_sum = pid->error[0] + pid->error[1] + pid->error[2];

    if (pid->type == INCREMENT_PID){
        if(fabs(pid->error_sum) > pid->error_max){
            pid->error_sum = (pid->error_sum / pid->error_sum) * pid->error_max;
        }
    }
    pid->output = pid->Kp * pid->error[0] + pid->Ki * pid->error_sum + pid->Kd * (pid->error[0] - pid->error[1]);
    if (pid->output > pid->output_max) pid->output = pid->output_max;
    else if (pid->output < -pid->output_max) pid->output = -pid->output_max;
}
