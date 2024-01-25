#include "al/app/al_App.hpp"

int main() {
  al::Vec3d a(0, 1, 0);
  al::Vec<3, double> b(1, 0, 0);

  std::cout << al::dot(a, b) << std::endl;
  std::cout << al::cross(a, b) << std::endl;
  std::cout << al::lerp(a, b, 0.5) << std::endl;

  float t = 0.3333;
  std::cout << a * (1 - t) + b * t << std::endl;
  //std::cout << a * (1 - t) + t * b << std::endl; // does not work

  // * / + - ... these work on vec3f

  al::rotate(a, b, M_PI_4);
  std::cout << a << std::endl;
}
