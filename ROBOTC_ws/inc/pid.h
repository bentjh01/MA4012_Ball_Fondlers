#ifndef PID_H
#define PID_H

typedef struct {
    double kp;  // Proportional gain
    double ki;  // Integral gain
    double kd;  // Derivative gain

    double setpoint;  // Desired setpoint
    double error_sum; // Accumulated error
    double last_error; // Previous error
} PIDController;

void pid_init(PIDController* pid, double kp, double ki, double kd, double setpoint);
double pid_update(PIDController* pid, double input, double dt);

#endif /* PID_H */
