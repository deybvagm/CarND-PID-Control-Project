#include "PID.h"

/**
 * TODO: Complete the PID class. You may add any additional desired functions.
 */

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp_, double Kd_, double Ki_) {
  /**
   * TODO: Initialize PID coefficients (and errors, if needed)
   */
   p.push_back(Kp_);
   p.push_back(Kd_);
   p.push_back(Ki_);

//   dp.push_back(0.000);
   dp.push_back(0.0001);
//   dp.push_back(0.025);
   dp.push_back(0.0001);
//   dp.push_back(0.00025);
   dp.push_back(0.0001);
}

void PID::UpdateError(double cte) {
  /**
   * TODO: Update PID errors based on cte.
   */
   diff_cte = cte - prev_cte;
   int_cte += cte;
   prev_cte = cte;
   total_error = -p[0] * cte - p[1] * diff_cte - p[2] * int_cte;
}

void PID::Twiddle(double cte) {
   if (!initialized){
      current_p = 0;
      best_error = cte;
      p[current_p] = p[current_p] + dp[current_p];
      action = INCREASE_P;
      initialized = true;
   }else{
      if (cte < best_error){
         dp[current_p] = dp[current_p] * 1.1;
         best_error = cte;
         current_p = next_p[current_p];
         p[current_p] = p[current_p] + dp[current_p];
         action = INCREASE_P;
      } else {
         if (action == INCREASE_P){
            p[current_p] = p[current_p] - 2 * dp[current_p];
            action = DECREASE_P;
         } else { //action is decrease
            p[current_p] = p[current_p] + dp[current_p];
            dp[current_p] = dp[current_p] * 0.9;
            current_p = next_p[current_p];
            p[current_p] = p[current_p] + dp[current_p];
            action = INCREASE_P;
         }
      }

   }
}

vector<double>  PID::GetParams(){
    return p;
}

double PID::TotalError() {
  /**
   * TODO: Calculate and return the total error
   */
  return total_error;  // TODO: Add your total error calc here!
}