#include <iostream>
#include <Eigen/Dense>

int main()
{
  /*
  using Mat3 = Eigen::Matrix<double, 3, 3>;
  using Mat34 = Eigen::Matrix<double, 3, 4>;
  // " Mat3 == Eigen::Matrix3d "
  using Vec3 = Eigen::Vector3d;

  Mat3 A;
  // A(row,col); row, col <<< 0,1,2
  //A = Mat3::Zero();
  A = Mat3::Identity();
  //std::cout << A << std::endl;

  Vec3 b;
  b << 
    1.0,
    2.0, 
    3.0;

  //std::cout << A * b << std::endl;
  // notes:
  // A + B
  // b + c

  // Mat3 B = A * b; // incompatible matrix sizes
  // Vec3 c = b * b;
  // Vec3 c = b * A; // incompatible matrix sizes
  
  // don't do that:
  //   Vec3 c = b.transpose() * A; 
  //   b.transpose() * A ~~~~~ A.transpose() * b
  //   != A * b

  // Solving Equations

  // y = B * x
  // x = ?
  Vec3 y { 1, 2, 3 };
  Mat3 B = Mat3::Random();
  std::cout << "B:\n" << B << std::endl;
  std::cout << "y:\n" << y << std::endl;

  std::cout << "x := B.inverse() * y\n" <<
    B.inverse() * y << std::endl;

  auto fullPixLU = B.fullPivLu();
  std::cout << "x := B.fullPivLu().solve(y)\n" <<
    fullPixLU.solve(y) << std::endl;

  // [U, S, V] = svd(B)
  std::cout << "x := B.jacobiSvd().solve(y)\n" <<
    B.jacobiSvd(Eigen::ComputeFullU | Eigen::ComputeFullV)
    .solve(y) << std::endl;*/

  // task 1:
  // - create a 2x2 rotation matrix, 
  // - parameterized by an angle phi
  // then:
  // - rotate a vector
  // - validate that it is indeed rotated by "phi"

  double phi = 34; // degrees!
  Eigen::Matrix2d R;
  
  const double deg2rad = 3.141593 / 180; // M_PI
  double phi_rad = phi * deg2rad;
  R <<
    cos(phi_rad), -sin(phi_rad),
    sin(phi_rad), cos(phi_rad);

  using Vec2 = Eigen::Vector2d;
  Vec2 whatever = Vec2::Random();
  Vec2 rotated_whatever = R * whatever;
  double dot_product = whatever.dot(rotated_whatever);
  dot_product /= whatever.norm();
  dot_product /= rotated_whatever.norm();

  std::cout 
    << "the angle between whatever and whatever_rotated is:\n" 
    << std::acos(dot_product) / deg2rad << std::endl;

  // task 2:
  // - 3x3 rotation matrix around X
  // - rotate Vec3{1, 0, 0} ... WHAT HAPPENS?!
  // - rotate Vec3{0, 1, 0} ... WHAT HAPPENS?!
  // - rotate Vec3{0, 0, 1} ... WHAT HAPPENS?!

  return 0;
}