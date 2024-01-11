#include "al/app/al_App.hpp"

// making a function
void print(al::Quatd const& q) {
  std::cout
    << '{'
    << q.w << ' '
    << q.x << ' '
    << q.y << ' '
    << q.z << ' '
    << '}'
    << std::endl;
}

int main() {
  al::Vec3d a(1, 0, 0);
  al::Vec3d b(0, 1, 0);
  // quat that rotates from a to b
  al::Quatd p = al::Quatd::getRotationTo(a, b);
  print(p);

  std::cout << a << std::endl;
  std::cout << b << std::endl;
  // execute a rotation on a given vector
  std::cout << p.rotate(a) << std::endl;

  // see also
  // p.toCoordinateFrame(...)
  // p.toAxisAngle(...)
  // p.toEuler(...)

  {
    // quat that represents a rotation from identity to point in a given direction
    al::Quatd a(al::Vec3d(1, 0, 0));
    al::Quatd b(al::Vec3d(0, 1, 0));
    // we ignore quaternion normalization because the vectors are normal
    print(a);
    print(b);
    // using auto
    auto c = a.slerp(b, 0.5);
    print(c);
    std::cout
      << c.x << ' '
      << c.y << ' '
      << c.z << ' '
      << std::endl;
  }
}

