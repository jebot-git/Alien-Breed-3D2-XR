#pragma once
#include "render.hpp"
#include <cmath>
#include <openxr/openxr.h>
namespace ab3d2 {
inline Matrix multiply(const Matrix &a, const Matrix &b) {
  Matrix out{};
  for (int c = 0; c < 4; c++)
    for (int r = 0; r < 4; r++)
      for (int k = 0; k < 4; k++)
        out[c * 4 + r] += a[k * 4 + r] * b[c * 4 + k];
  return out;
}
inline Matrix rotationY(float a) {
  float c = std::cos(a), s = std::sin(a);
  return {c, 0, -s, 0, 0, 1, 0, 0, s, 0, c, 0, 0, 0, 0, 1};
}
inline Matrix translation(float x, float y, float z) {
  auto m = Identity;
  m[12] = x;
  m[13] = y;
  m[14] = z;
  return m;
}
inline Matrix poseMatrix(const XrPosef &pose) {
  auto q = pose.orientation;
  float x = q.x, y = q.y, z = q.z, w = q.w;
  return {1 - 2 * (y * y + z * z), 2 * (x * y + w * z),
          2 * (x * z - w * y),     0,
          2 * (x * y - w * z),     1 - 2 * (x * x + z * z),
          2 * (y * z + w * x),     0,
          2 * (x * z + w * y),     2 * (y * z - w * x),
          1 - 2 * (x * x + y * y), 0,
          pose.position.x,         pose.position.y,
          pose.position.z,         1};
}
inline Matrix inverseRigid(const Matrix &m) {
  Matrix out = Identity;
  for (int c = 0; c < 3; c++)
    for (int r = 0; r < 3; r++)
      out[c * 4 + r] = m[r * 4 + c];
  for (int r = 0; r < 3; r++)
    out[12 + r] = -(out[r] * m[12] + out[4 + r] * m[13] + out[8 + r] * m[14]);
  return out;
}
inline Matrix projection(const XrFovf &f, float near = .04f, float far = 400) {
  float l = std::tan(f.angleLeft), r = std::tan(f.angleRight),
        u = std::tan(f.angleUp), d = std::tan(f.angleDown);
  Matrix out{};
  out[0] = 2 / (r - l);
  out[5] = 2 / (u - d);
  out[8] = (r + l) / (r - l);
  out[9] = (u + d) / (u - d);
  out[10] = -(far + near) / (far - near);
  out[11] = -1;
  out[14] = -2 * far * near / (far - near);
  return out;
}
inline Matrix perspective(float aspect, float fov = 75) {
  float u = std::tan(fov * 3.14159265358979323846f / 360);
  XrFovf f{std::atan(-u * aspect), std::atan(u * aspect), std::atan(u),
           std::atan(-u)};
  return projection(f);
}
} // namespace ab3d2
