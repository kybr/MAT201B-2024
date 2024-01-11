#include "al/app/al_App.hpp"

// how to use a namespace
using namespace al;

void print(Quatd const& q) {
  std::cout
    << '{'
    << q.w << ' '
    << q.x << ' '
    << q.y << ' '
    << q.z << ' '
    << '}';
}

int main() {
  Pose a, b;
  // a is 0,0,0/1,0,0,0
  b.pos(0, 1, 5);
  print(Quatd(b.pos()));
  b.quat(Quatd(b.pos()).normalize());
  // b is 0,1,5/...
  a.print();
  b.print();

  // go to definition to see what Pose::lerp does
  a.lerp(b, 0.01).print();
  a.lerp(b, 0.99).print();
  a.faceToward(b.pos(), 0.5); // just change quaternian
  a.print();

  // quaternians should always be normalized;
  // sometimes you have to manually normalize them
  std::cout << a.quat().mag() << std::endl;
}