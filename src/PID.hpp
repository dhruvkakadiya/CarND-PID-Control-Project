#ifndef PID_HPP
#define PID_HPP

class PID {
 public:
  /**
   * PID Constructor
   * @param (p, i, d) The initial PID coefficients
   */
  PID(double p, double i, double d);

  /**
   * Destructor.
   */
  ~PID() = default;

  /**
   * Update the PID error variables given cross track error.
   * @param cte The current cross track error
   */
  void UpdateError(double cte) noexcept;

  /**
   * Calculate the total PID error.
   * @output The total PID error
   */
  [[nodiscard]] double TotalError() noexcept;

 private:
  /**
   * PID Errors
   */
  double p_error{0};
  double i_error{0};
  double d_error{0};

  /**
   * PID Coefficients
   */
  double Kp{0};
  double Ki{0};
  double Kd{0};
};

#endif  // PID_HPP