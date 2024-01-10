#include "al/app/al_App.hpp"

int main() {
  al::Vec3d a;
  a.print();
  al::Vec3d b(1);
  b.print();

  al::Vec3d c(0, 1, 0);
  c.print();
  al::Vec<3, double> d(1, 0, 0);
  d.print();

  std::cout << al::dot(c, d) << std::endl;
  std::cout << al::cross(c, d) << std::endl;

  std::cout << al::lerp(c, d, 0.5) << std::endl;
}

// int main() {  MyApp().start(); }