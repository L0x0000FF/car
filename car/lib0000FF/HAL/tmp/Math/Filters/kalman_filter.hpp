#ifndef KALMAN_FILTER_HPP
#define KALMAN_FILTER_HPP

#include "vector"
#include "Math/Matrix/matrix.hpp"

class KalmanFilter {
private:
  Matrix A;
  Matrix B;
  Matrix H;
  Matrix P;
  Matrix Q;
  Matrix R;
  Matrix K;
  Matrix X;
public:
  std::vector<float> Z;
  std::vector<float> U;
  KalmanFilter();
  void update();
  std::vector<float> getOutput;
};


#endif //KALMAN_FILTER_HPP
