#include "PID.hpp"

PID::PID(double p, double i, double d) : Kp(p), Ki(i), Kd(d){};

void PID::UpdateError(double cte) noexcept {
  d_error = cte - p_error;
  p_error = cte;
  i_error += cte;
}

double PID::TotalError() noexcept {
  return (-Kp * p_error - Ki * i_error - Kd * d_error);
}