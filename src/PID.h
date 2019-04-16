#ifndef PID_H
#define PID_H

#include <string>
#include <vector>
#include <map>

using std::string;
using std::vector;
using std::map;

class PID {
 public:
  /**
   * Constructor
   */
  PID();

  /**
   * Destructor.
   */
  virtual ~PID();

  /**
   * Initialize PID.
   * @param (Kp_, Ki_, Kd_) The initial PID coefficients
   */
  void Init(double Kp_, double Kd_, double Ki_);

  /**
   * Update the PID error variables given cross track error.
   * @param cte The current cross track error
   */
  void UpdateError(double cte);

  /**
   * Calculate the total PID error.
   * @output The total PID error
   */
  double TotalError();

  void Twiddle(double cte);

  vector<double > GetParams();

 private:
  /**
   * PID Errors
   */
  vector<double> dp;

  /**
   * PID Coefficients
   */ 
  vector<double> p;

  double prev_cte = 0;
  double diff_cte;
  double int_cte = 0;

  bool initialized = false;
  double best_error;

  string action;
  int current_p;

  const string INCREASE_P = "increase_p";
  const string DECREASE_P = "decrease_p";

  map<int, int> next_p = {{0, 1}, {1, 2}, {2, 0}};

  double total_error = 0;

};

#endif  // PID_H