#pragma once
#include <Eigen/Dense>

namespace SO2
{
  using Mat2 = Eigen::Matrix2d;
  using Vec2 = Eigen::Vector2d;

  // Action
  inline Vec2 Action(const Mat2& A, const Vec2& b) {
    return A * b;
  }

  // Exp: scalar -> Mat2
  inline Mat2 Exp(const double& phi) {
    //Mat2 R; R << .....
    double
      c = std::cos(phi), // rad in the parameter
      s = std::sin(phi); // rad in the parameter

    return (Mat2() << c, -s, s, c).finished();
  }

  // Log: SO(2) -> scalar 
  inline double Log(const Mat2& R) {
    return std::atan2(
      R(1,0)/*sin phi*/,
      R(0,0)/*cos phi*/); // --> phi
  }

  // log: SO(2) -> Mat2
  inline Mat2 Lie_log(const Mat2& R) {
    double phi = std::atan2(
      R(1, 0)/*sin phi*/,
      R(0, 0)/*cos phi*/); // --> phi

    Mat2 r;
    r <<
      0.0, -phi,
      phi, 0.0;
    return r;
  }
}