#include "PID.h"
#include <iostream>

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double p, double i, double d) {

  Kp = p;
  Ki = i;
  Kd = d;

  i_error = 0;
  cte_last = 0;
}

void PID::UpdateError(double cte) {
  p_error = cte;
  i_error += cte;
  d_error = cte - cte_last;
  
  cte_last = cte;
}


double PID::TotalError() {
	double total_error = Kp * p_error + Ki * i_error + Kd * d_error;
	//std::cout << "Kp: " << Kp << "Ki: " << Ki << "Kd: " << Kd <<std::endl;
	//std::cout << "p_error: " << p_error << "i_error: " << i_error << "d_error: " << d_error <<std::endl;
	//std::cout << "total_error: " << total_error <<std::endl;
	return total_error;
}

