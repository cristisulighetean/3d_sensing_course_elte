#pragma once
#include <Eigen/Dense>

namespace Geometry {

  using Mat3 = Eigen::Matrix3d;
  using Vec3 = Eigen::Vector3d;

  namespace SO3 {
    // TODO: Exp, Log, boxplus, boxminus, interpolation

    inline
      Mat3 Exp(const Vec3& w) {
      Mat3 w_hat;
      w_hat <<
        0, -w.z(), w.y(),
        w.z(), 0, -w.x(),
        -w.y(), w.x(), 0;
      // Note: e.g. w.cross(some_other_vector) == w_hat * some_other_vector;

      /*const double phi = w.norm(); // L2 norm

      return Mat3::Identity() +
        w_hat / phi * sin(phi) +
        w_hat * w_hat / (phi * phi) * (1 - cos(phi));*/

      const double phi2 = w.squaredNorm();

      if (phi2 > std::numeric_limits<float>::epsilon()) {
        const double phi = std::sqrt(phi2);
        return Mat3::Identity() +
          w_hat / phi * sin(phi) +
          w_hat * w_hat / (phi * phi) * (1 - cos(phi));
      }
      else {
        return Mat3::Identity() + w_hat;
      }
    }

    inline
      Vec3 Log(const Mat3& R) {

      // question: how to improve? (homework) +1.0p
      //const double phi = std::acos((R.trace() - 1) / 2);
      // - atan2(,) for quadrants
      // - around 0 and around 1 num. prec of acos is low (~10e-6 .. 7)
      // - it would be better to have (~10e-12 or higher)

      const Vec3 w = Vec3(
        R(2, 1) - R(1, 2),
        R(0, 2) - R(2, 0),
        R(1, 0) - R(0, 1)
      );
      // how to normalize w?
      // - divide by (2 * sin(phi))
      // - divide by w.norm()

      const double cos_phi = (R.trace() - 1) / 2;
      const double sin_phi = w.norm() / 2.0; // == sin(phi)
      const double phi = std::atan2(sin_phi, cos_phi);

      if (sin_phi > std::numeric_limits<float>::epsilon()) {
        // case 1
        // Vec3 w_normalized = 1 / (2 * sin_phi) * w;
        // return phi * w_normalized;
        return phi / (2 * sin_phi) * w;
      }
      else {
        // case 2
        // when phi~0 and sin_phi~0
        return (1.0 / 2.0) * w;
      }
      // case 3 ?!
      // homework: phi~pi and sin_phi~0 (here we can't use the above case) [+4 points]
    }

    inline
      Vec3 boxminus(const Mat3& X, const Mat3& Y) {
      return Log(X * Y.transpose());
    }

    inline
      Mat3 boxplus(const Mat3& X, const Vec3& u) {
      return Exp(u) * X;
    }

    inline
      Mat3 interpolate(const Mat3& X, const Mat3& Y, const double& t) {
      // t == 0 -> Y
      // t == 1 -> X
      // t \in (0,1) -> .....
      return boxplus(X, t * boxminus(Y, X));
    }

  }

}