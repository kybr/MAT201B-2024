#include "al/app/al_App.hpp"
#include <iostream>

using namespace al;
using namespace std;

void print(RGB& c) {
  cout
    << '['
    << c.r << ' ' << c.g << ' ' << c.b
    << ']'
    << endl;

}
int main() {
  RGB a(1, 0, 0);
  HSV b(1, 1, 1);
  Lab c(1, 1, 1);

  HSV hsv = a;
  cout << hsv.h << endl;
  cout << hsv.s << endl;
  cout << hsv.v << endl;

  Lab lab = b;
  cout << lab.l << endl;
  cout << lab.a << endl;
  cout << lab.b << endl;

  RGB rgb = c;
  cout << rgb.r << endl;
  cout << rgb.g << endl;
  cout << rgb.b << endl;

  Color d = lab;
  cout << d.r << endl;
  cout << d.g << endl;
  cout << d.b << endl;

}
