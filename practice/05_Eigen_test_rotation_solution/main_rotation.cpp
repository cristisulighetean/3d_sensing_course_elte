#include <iostream>
#include "SO3.hpp"

using namespace Geometry;
using namespace std;

int main()
{
  /*cout << SO3::Log(Mat3::Identity()) << endl;

  cout << 
    SO3::Exp(SO3::Log(Mat3::Identity()))
    << endl;*/

  srand(time(0));

  auto quat_0 = Eigen::Quaterniond::UnitRandom();
  auto quat_1 = Eigen::Quaterniond::UnitRandom();
  auto R_0 = quat_0.toRotationMatrix();// Mat3::Identity();
  auto R_1 = quat_1.toRotationMatrix();

  cout << "source matrix: R_0" << endl << R_0 << endl;
  cout << "target matrix: R_1" << endl << R_1 << endl << endl;

  for (int i : {0, 1, 2, 3, 4}) {
    double t = i / 4.0;

    auto R = SO3::interpolate(R_0, R_1, t);

    cout << R << endl;
    Vec3 w = SO3::Log(R);
    cout
      << "t: " << t << endl
      << "angle: " << w.norm() << endl
      << "axis: " << w.normalized().transpose() << endl << endl;
  }
  
  return 0;
}