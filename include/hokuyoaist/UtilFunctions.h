#ifndef _UTILFUNCTIONS_H_
#define _UTILFUNCTIONS_H_

#include <cmath>

namespace util{

static inline float normalize_angle_pos(float angle)
{
  return fmod(fmod(angle, 2.0f*M_PI) + 2.0f*M_PI, 2.0f*M_PI);
}

static inline float normalize_angle(float angle)
{
  float a = normalize_angle_pos(angle);
  if (a > M_PI){
    a -= 2.0f*M_PI;
  }
  return a;
}

static inline float sqr(float val)
{
  return val*val;
}

static inline int sign(int x)
{
  return x > 0 ? 1 : -1;
}

template<typename T>
static T toDeg(const T radVal)
{
  return radVal * static_cast<T>(180.0 / M_PI);
}

template<typename T>
static T toRad(const T degVal)
{
  return degVal * static_cast<T>(M_PI / 180.0);
}

static bool poseDifferenceLargerThan(const Eigen::Vector3f& pose1, const Eigen::Vector3f& pose2, float distanceDiffThresh, float angleDiffThresh)
{
  //check distance
  if ( ( (pose1.head<2>() - pose2.head<2>()).norm() ) > distanceDiffThresh){
    return true;
  }

  float angleDiff = (pose1.z() - pose2.z());

  if (angleDiff > M_PI) {
    angleDiff -= M_PI * 2.0f;
  } else if (angleDiff < -M_PI) {
    angleDiff += M_PI * 2.0f;
  }

  if (abs(angleDiff) > angleDiffThresh){
    return true;
  }
  return false;
}

}

#endif
